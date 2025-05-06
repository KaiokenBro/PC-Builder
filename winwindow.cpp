#include "winwindow.h"
#include <QMouseEvent>
#include <QTimer>
#include "ui_winwindow.h"

WinWindow::WinWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::WinWindow),
    scaleFactor(100),
    world(b2Vec2(0.0f, -10.0f))
{
    ui->setupUi(this);
    QImage image(":/images/finishedPC.PNG");
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    // 2 meters in Box2D to pixels in window
    float width = 2.0f * scaleFactor;
    float height = 2.0f * scaleFactor;
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->resize(width, height);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    float groundBoxHalfWidth = this->width() / scaleFactor;
    // Top of the ground is at (x, 0)
    groundBox.SetAsBox(groundBoxHalfWidth * 100, 10.0f);
    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(2, 10);
    body = world.CreateBody(&bodyDef);
    body->SetAwake(true);
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    // Override the default friction.
    fixtureDef.friction = 0.3f;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // Left wall
    float wallHeightInMeters = this->height() / scaleFactor * 100;
    b2BodyDef leftWallDef;
    leftWallDef.position.Set(-110.0f, 0.0f);
    b2Body* leftWall = world.CreateBody(&leftWallDef);
    b2PolygonShape leftWallShape;
    leftWallShape.SetAsBox(109.0f, wallHeightInMeters);
    leftWall->CreateFixture(&leftWallShape, 0.0f);

    // Right wall
    b2BodyDef rightWallDef;
    rightWallDef.position.Set(groundBoxHalfWidth + 19.0f, 0.0f);
    b2Body* rightWall = world.CreateBody(&rightWallDef);
    b2PolygonShape rightWallShape;
    rightWallShape.SetAsBox(11.0f, wallHeightInMeters);
    rightWall->CreateFixture(&rightWallShape, 0.0f);

    QTimer* timer = new QTimer(this);
    ui->imageLabel->installEventFilter(this);

    connect(timer,
            &QTimer::timeout,
            this,
            &WinWindow::updateWorld
    );

    // 60 FPS
    timer->start(1000 / 60);
}

WinWindow::~WinWindow()
{
    delete ui;
}

void WinWindow::updateWorld()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world.Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = body->GetPosition();

    // Convert Box2D meters to window pixels using scaleFactor
    translateMove(ui->imageLabel, position.x, position.y);
}

void WinWindow::translateMove(QLabel* object, float x, float y)
{
    float windowHeight = this->height();
    float translatedX = x * scaleFactor;
    float translatedY = windowHeight - (y * 2.0f * scaleFactor);
    object->move(translatedX, translatedY);
}

bool WinWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->imageLabel) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = (QMouseEvent *) event;
            if (mouseEvent->button() == Qt::LeftButton) {
                dragging = true;
                dragOffset = mouseEvent->pos();
                return true;
            }
        } else if (event->type() == QEvent::MouseMove && dragging) {
            body->SetAwake(false);
            QMouseEvent* mouseEvent = (QMouseEvent *) event;
            QPoint newPosition = ui->imageLabel->pos() + (mouseEvent->pos() - dragOffset);
            updateBox2D(newPosition);
            return true;
        } else if (event->type() == QEvent::MouseButtonRelease) {
            dragging = false;
            body->SetAwake(true);
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void WinWindow::updateBox2D(QPoint newPosition)
{
    float windowHeight = this->height();
    float translatedY = (windowHeight - newPosition.y()) / (2.0f * scaleFactor);
    float translatedX = newPosition.x() / scaleFactor;
    b2Vec2 newPositionBox2D(translatedX, translatedY);
    body->SetTransform(newPositionBox2D, body->GetAngle());
}
