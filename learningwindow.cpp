#include "learningwindow.h"
#include "ui_learningwindow.h"

// CONSTRUCTOR
LearningWindow::LearningWindow(TestWindow* testWindow, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::LearningWindow)
{
    ui->setupUi(this);
    this->testWindow = testWindow;

    // PC Case Image
    QPixmap casePixmap(":/images/case.png");
    ui->caseLabel->setPixmap(casePixmap);
    ui->caseLabel->setScaledContents(true);

    // Motherboard Image
    QPixmap motherboardPixmap(":/images/motherboard.png");
    ui->motherboardLabel->setPixmap(motherboardPixmap);
    ui->motherboardLabel->setScaledContents(true);

    // Graphics Card Image
    QPixmap gpuPixmap(":/images/gpu.png");
    ui->gpuLabel->setPixmap(gpuPixmap);
    ui->gpuLabel->setScaledContents(true);

    // CPU Image
    QPixmap cpuPixmap(":/images/cpu.png");
    ui->cpuLabel->setPixmap(cpuPixmap);
    ui->cpuLabel->setScaledContents(true);

    // Memory Image
    QPixmap memoryPixmap(":/images/memory.png");
    ui->memoryLabel->setPixmap(memoryPixmap);
    ui->memoryLabel->setScaledContents(true);

    // Ram Image
    QPixmap ramPixmap(":/images/ram.png");
    ui->ramLabel->setPixmap(ramPixmap);
    ui->ramLabel->setScaledContents(true);

    // When testButton clicked, open testWindow
    connect(ui->testButton,
            &QPushButton::clicked,
            this,
            &LearningWindow::onTestButtonClicked
    );

}

// DESTRUCTOR
LearningWindow::~LearningWindow() {
    delete ui;
}

// SLOT
void LearningWindow::onTestButtonClicked() {
    this->hide();
    testWindow->show();
}
