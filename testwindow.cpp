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
    dontMove({"caseLabel", "centralwidget"}),
    step(1)
{
    ui->setupUi(this);
    setMouseTracking(true);

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

    // Ram Images
    QPixmap ramPixmap(":/images/ram.png");
    ui->ramLabel1->setPixmap(ramPixmap);
    ui->ramLabel1->setScaledContents(true);
    ui->ramLabel1->setToolTip("Random Access Memory (RAM)");

    ui->ramLabel2->setPixmap(ramPixmap);
    ui->ramLabel2->setScaledContents(true);
    ui->ramLabel2->setToolTip("Random Access Memory (RAM)");

    TestChecker* testChecker = new TestChecker();

    connect(this,
            &TestWindow::checkAnswer,
            testChecker,
            &TestChecker::checkPlacement
            );

    connect(testChecker,
            &TestChecker::sendAnswer,
            this,
            &TestWindow::receiveAnswer
            );

}

// DESTRUCTOR
TestWindow::~TestWindow() {
    delete ui;
}

// SLOT
void TestWindow::dragEnterEvent(QDragEnterEvent* event) {

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }

        else {
            event->acceptProposedAction();
        }

    }

    else {
        event->ignore();
    }
}

// SLOT
void TestWindow::dragMoveEvent(QDragMoveEvent* event) {

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }

        else {
            event->acceptProposedAction();
        }

    }

    else {
        event->ignore();
    }
}

// SLOT
void TestWindow::dropEvent(QDropEvent* event) {

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel* newIcon = new QLabel(this);
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
        }

        else {
            event->acceptProposedAction();
        }

        emit checkAnswer(step, lastName, newLocal);
    }

    else {
        event->ignore();
    }
}

// SLOT
void TestWindow::mousePressEvent(QMouseEvent* event) {
    QLabel* child = static_cast<QLabel*>(childAt(event->pos()));

    if (!child || dontMove.contains(child->objectName())){
        return;
    }

    lastSize = child->size();
    lastName = child->objectName();
    QPixmap pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData* mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap.scaled(lastSize.width(), lastSize.height()));
    drag->setHotSpot(event->pos() - child->pos());

    child->setPixmap(pixmap);
    child->resize(lastSize);
    child->setScaledContents(true);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    }

    else {
        child->show();
        child->setPixmap(pixmap);
    }
}

// SLOT
QPoint TestWindow::snapLocation(QPoint cursor) {

    // CPU location
    if (315 <= cursor.x() && cursor.x() <= 395 && 295 <= cursor.y() && cursor.y() <= 375){
        return QPoint(315, 295);
    }

    // RAM 1 location
    else if (420 <= cursor.x() && cursor.x() <= 440 && 280 <= cursor.y() && cursor.y() <= 410){
        return QPoint(423, 270);
    }

    // RAM 2 location
    else if (440 <= cursor.x() && cursor.x() <= 460 && 280 <= cursor.y() && cursor.y() <= 410){
        return QPoint(443, 270);
    }

    // Memory location
    else if (260 <= cursor.x() && cursor.x() <= 350 && 470 <= cursor.y() && cursor.y() <= 520){
        return QPoint(260, 470);
    }

    // GPU Location
    else if (200 <= cursor.x() && cursor.x() <= 430 && 560 <= cursor.y() && cursor.y() <= 630){
        return QPoint(180, 440);
    }

    // Motherboard location
    else if (150 <= cursor.x() && cursor.x() <= 450 && 290 <= cursor.y() && cursor.y() <= 590){
        return QPoint(200, 245);
    }

    // No where to snap to drop where it is
    else {
        QPoint newDrop = QPoint(cursor.x() - .5*lastSize.width(), cursor.y() - .5*lastSize.height());
        return newDrop;
    }
}

// SLOT
void TestWindow::receiveAnswer(bool correctness, QString reason, QString part) {

    if (step == 6 && correctness) {
        dontMove.append(part);

        // Create info box letting you know you made the computer correctly.
        InfoBox* dialog = new InfoBox("Great Job!!", "Enjoy the new PC", this);
        dialog->exec();

        // Close when done.
        delete dialog;
    }

    else if (correctness) {
        dontMove.append(part);
        step++;

        // Create info box letting you know you were right.
        InfoBox* dialog = new InfoBox("Correct", "Keep Going!", this);
        dialog->exec();

        // Close when done.
        delete dialog;
    }

    else {

        // Create info box with the reason why you were incorrect.
        InfoBox* dialog = new InfoBox("Incorrect", reason, this);
        dialog->exec();

        // Close when done.
        delete dialog;
    }
}
