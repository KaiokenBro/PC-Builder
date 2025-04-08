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
