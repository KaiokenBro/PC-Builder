#include "testwindow.h"
#include "ui_testwindow.h"
#include "testchecker.h"
#include "infobox.h"

#include <QDebug>

// CONSTRUCTOR
TestWindow::TestWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow),
    lastSize(QSize(0,0)),
    lastName("none"),
    step(1),
    dontMove({"caseLabel", "centralwidget"})
{
    ui->setupUi(this);
    setMouseTracking(true);

    TestChecker *testChecker = new TestChecker();
    connect(this, &TestWindow::checkAnswer, testChecker, &TestChecker::checkPlacement);
    connect(testChecker, &TestChecker::sendAnswer, this, &TestWindow::receiveAnswer);

    // PC Case Image
    QPixmap casePixmap(":/images/case.png");
    ui->caseLabel->setPixmap(casePixmap);
    ui->caseLabel->setScaledContents(true);
    ui->caseLabel->setToolTip("Computer Case");

    // Motherboard Image
    QPixmap motherboardPixmap(":/images/motherboard.png");
    ui->motherboardLabel->setPixmap(motherboardPixmap);
    ui->motherboardLabel->setScaledContents(true);
    ui->motherboardLabel->setToolTip("Motherboard");

    // Graphics Card Image
    QPixmap gpuPixmap(":/images/gpu.png");
    ui->gpuLabel->setPixmap(gpuPixmap);
    ui->gpuLabel->setScaledContents(true);
    ui->gpuLabel->setToolTip("Graphics Processing Unit (GPU)");

    // CPU Image
    QPixmap cpuPixmap(":/images/cpu.png");
    ui->cpuLabel->setPixmap(cpuPixmap);
    ui->cpuLabel->setScaledContents(true);
    ui->cpuLabel->setToolTip("Central Processing Unit (CPU)");

    // Memory Image
    QPixmap memoryPixmap(":/images/memory.png");
    ui->memoryLabel->setPixmap(memoryPixmap);
    ui->memoryLabel->setScaledContents(true);
    ui->memoryLabel->setToolTip("Solid State Drive (SSD)");

    // Ram Image
    QPixmap ramPixmap(":/images/ram.png");
    ui->ramLabel->setPixmap(ramPixmap);
    ui->ramLabel->setScaledContents(true);
    ui->ramLabel->setToolTip("Random Access Memory (RAM)");
}

// DESTRUCTOR
TestWindow::~TestWindow() {
    delete ui;
}

void TestWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void TestWindow::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void TestWindow::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        QPoint cursor = event->position().toPoint();
        QPoint newLocal = snapLocation(cursor);
        newIcon->setPixmap(pixmap);
        newIcon->move(newLocal);
        newIcon->resize(lastSize);
        newIcon->setObjectName(lastName);
        newIcon->setScaledContents(true);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
        emit checkAnswer(step, lastName, newLocal);
    } else {
        event->ignore();
    }
}

void TestWindow::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child || dontMove.contains(child->objectName())){
        return;
    }
    lastSize = child->size();
    lastName = child->objectName();
    QPixmap pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap.scaled(lastSize.width(), lastSize.height()));
    drag->setHotSpot(event->pos() - child->pos());

    child->setPixmap(pixmap);
    child->resize(lastSize);
    child->setScaledContents(true);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}

QPoint TestWindow::snapLocation(QPoint cursor)
{
    // CPU location
    if (315 <= cursor.x() && cursor.x() <= 395 && 295 <= cursor.y() && cursor.y() <= 375){
        return QPoint(315, 295);
    }
    // RAM location
    else if(200 <= cursor.x() && cursor.x() <= 300 && 390 <= cursor.y() && cursor.y() <= 440){
        return QPoint(200,390);
    }
    // Memory location
    else if(65 <= cursor.x() && cursor.x() <= 165 && 290 <= cursor.y() && cursor.y() <= 340){
        return QPoint(65, 290);
    }
    // GPU Location
    else if(200 <= cursor.x() && cursor.x() <= 430 && 560 <= cursor.y() && cursor.y() <= 630){
        return QPoint(180, 440);
    }
    // Motherboard location
    else if(150 <= cursor.x() && cursor.x() <= 450 && 290 <= cursor.y() && cursor.y() <= 590){
        return QPoint(200, 245);
    }
    // No where to snap to drop where it is
    else{
        QPoint newDrop = QPoint(cursor.x() - .5*lastSize.width(), cursor.y() - .5*lastSize.height());
        return newDrop;
    }
}

void TestWindow::receiveAnswer(bool correctness, QString reason, QString part){
    if(step == 5 && correctness){
        dontMove.append(part);
        // Create info box letting you know you made the computer correctly.
        InfoBox* dialog = new InfoBox("Great Job!!", "Enjoy the new PC", this);
        dialog->exec();

        // Close when done.
        delete dialog;
    }
    else if(correctness){
        dontMove.append(part);
        step++;
        // Create info box letting you know you were right.
        InfoBox* dialog = new InfoBox("Correct", "Keep Going!", this);
        dialog->exec();

        // Close when done.
        delete dialog;
    }
    else{
        // Create info box with the reason why you were incorrect.
        InfoBox* dialog = new InfoBox("Incorrect", reason, this);
        dialog->exec();

        // Close when done.
        delete dialog;
    }
}

