#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "learningwindow.h"

// To convert meters to pixels you have to divide by 50.0f for positions.

// CONSTRUCTOR
MainWindow::MainWindow(LearningWindow* learningWindow, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->learningWindow = learningWindow;

    // Calls method to set up the background image.
    showBackground();

    // Create a QGraphicsScene for our animation
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 1000);

    // Make the scene background transparent so text is readable during animation.
    scene->setBackgroundBrush(Qt::NoBrush);
    ui->graphicsView->setStyleSheet("background: transparent; border: none;");
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Construct a world object, which will hold and simulate the rigid bodies.
    world = new b2World(b2Vec2(0.0f, 9.8f));

    // Define the ground body, used for floor creation
    {
        b2BodyDef groundDef;

        // Define the floor for the object to fall to.
        groundDef.position.Set(400.0f / 50.0f, 370.0f / 50.0f);
        b2Body* groundBody = world->CreateBody(&groundDef);

        // Define the ground box shape.
        b2PolygonShape groundBox;
        groundBox.SetAsBox(400.0f / 50.0f, 10.0f / 50.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);
    }

    // Make the icon item to be used for animation (Our App logo).
    pcIconItem = new QGraphicsPixmapItem(QPixmap(":/images/PC Builder Pic.png"));

    // Scale the icon to 35% of its original size to fit
    pcIconItem->setScale(0.35);

    // Position the icon high so it falls to the defined floor above.
    pcIconItem->setPos(140, -400);
    pcIconItem->setTransformOriginPoint(pcIconItem->boundingRect().center());
    scene->addItem(pcIconItem);

    // Create the dynamic bodies
    {
        QRectF r = pcIconItem->boundingRect();
        float cx = (pcIconItem->pos().x() + r.width() / 2) / 50.0f;
        float cy = (pcIconItem->pos().y() + r.height() / 2) / 50.0f;

        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(cx, cy);
        pcIconBody = world->CreateBody(&bodyDef);

        b2PolygonShape boxShape;
        boxShape.SetAsBox( (r.width() / 2) / 50.0f, (r.height() / 2) / 50.0f );

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;

        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.density = 1.0f;

        // Override the default friction.
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.6f;

        // Add the shape to the body.
        pcIconBody->CreateFixture(&fixtureDef);
    }

    // Start the animtion timer
    connect(&animationTimer,
            &QTimer::timeout,
            this,
            &MainWindow::frameAnimation
    );

    // When startButton clicked, open learningWindow
    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onStartButtonClicked
    );

    animationTimer.start(16);

}

// DESTRUCTOR
MainWindow::~MainWindow() {
    delete world;
    delete ui;
}

// SLOT
void MainWindow::onStartButtonClicked() {
    this->hide();
    learningWindow->show();
}

// SLOT
void MainWindow::frameAnimation() {

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    const float timeStep = 1.0f / 60.0f;
    const int velocityIterations = 6;
    const int positionIterations = 2;

    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world->Step(timeStep, velocityIterations, positionIterations);

    // Update the icon item's position from its body.
    b2Vec2 position = pcIconBody->GetPosition();
    float angle = pcIconBody->GetAngle();
    QRectF r = pcIconItem->boundingRect();

    float xPix = (position.x * 50.0f) - r.width()/2;
    float yPix = (position.y * 50.0f) - r.height()/2;
    pcIconItem->setPos(xPix, yPix);
    pcIconItem->setRotation(angle * 180.0f / b2_pi);
}

// METHOD
void MainWindow::showBackground(){
    // Create a QLabel to display the background.
    QLabel* backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());

    // Create a QMovie object and load the GIF.
    QMovie* movie = new QMovie(":/gif/matrix.gif");
    backgroundLabel->setMovie(movie);

    // Show background and send to back of the label.
    movie->start();
    backgroundLabel->lower();
}
