/**
 * @file learningwindow.cpp
 *
 * @brief Implementation of the LearningWindow class.
 *
 * This file contains the implementation of the LearningWindow class,
 * which provides an educational UI for learning about PC components.
 * It includes interactive animations for assembling PC parts,
 * toggling between full and step-by-step assembly modes, and
 * displaying information popups about each component.
 *
 * The window also supports transitioning into a TestWindow,
 * where users can practice assembling a PC based on what they learned.
 *
 * @date 04/22/2025
 */

#include "learningwindow.h"
#include "ui_learningwindow.h"
#include "infobox.h"

LearningWindow::LearningWindow(TestWindow* testWindow, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::LearningWindow),
    isAssembled(false)
{
    ui->setupUi(this);
    this->testWindow = testWindow;
    stepByStepToggled = false;
    ui->stepByStepLabel->setVisible(false);

    // Install event handler for mouseclicks on part labels.
    ui->caseLabel->installEventFilter(this);
    ui->memoryLabel->installEventFilter(this);
    ui->motherboardLabel->installEventFilter(this);
    ui->gpuLabel->installEventFilter(this);
    ui->cpuLabel->installEventFilter(this);
    ui->ramLabel->installEventFilter(this);

    // Store the original positions and sizes of the labels.
    originalPosSizes["case"] = qMakePair(ui->caseLabel->pos(), ui->caseLabel->size());
    originalPosSizes["memory"] = qMakePair( ui->memoryLabel->pos(), ui->memoryLabel->size());
    originalPosSizes["motherboard"] = qMakePair( ui->motherboardLabel->pos(), ui->motherboardLabel->size());
    originalPosSizes["gpu"] = qMakePair( ui->gpuLabel->pos(), ui->gpuLabel->size());
    originalPosSizes["cpu"] = qMakePair( ui->cpuLabel->pos(), ui->cpuLabel->size());
    originalPosSizes["ram"] = qMakePair( ui->ramLabel->pos(), ui->ramLabel->size());

    // PC Case Image
    QPixmap casePixmap(":/images/case.png");
    ui->caseLabel->setPixmap(casePixmap);
    ui->caseLabel->setScaledContents(true);
    ui->caseLabel->setToolTip("Computer Case");

    // // Motherboard Image
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

    connect(ui->testButton,
            &QPushButton::clicked,
            this,
            &LearningWindow::onTestButtonClicked
    );

    connect(ui->assembleButton,
            &QPushButton::clicked,
            this,
            &LearningWindow::assemblePC
    );

    connect(ui->stepByStepButton,
            &QPushButton::clicked,
            this,
            &LearningWindow::toggleStepByStep
    );

    connect(ui->nextButton,
            &QPushButton::clicked,
            this,
            &LearningWindow::nextStep
    );

    connect(ui->previousButton,
            &QPushButton::clicked,
            this,
            &LearningWindow::previousStep
    );

}

LearningWindow::~LearningWindow() {
    delete ui;
}

void LearningWindow::onTestButtonClicked() {
    this->hide();
    testWindow->show();
}

void LearningWindow::showInfo(const QString& title, const QString& text) {
    InfoBox* dialog = new InfoBox(title, text, this);
    dialog->exec();
    delete dialog;
}

// SLOT
void LearningWindow::assemblePC() {

    // Set the position and size for the parts.
    if (!isAssembled) {
        animatePart(ui->gpuLabel, QPoint(175, 200), QSize(200, 220));
        animatePart(ui->cpuLabel, QPoint(290, 125), QSize(80, 80));
        animatePart(ui->ramLabel, QPoint(397, 100), QSize(15, 130));
        animatePart(ui->memoryLabel, QPoint(230, 200), QSize(105, 50));
        animatePart(ui->motherboardLabel, QPoint(175, 75), QSize(300, 300));
        animatePart(ui->caseLabel, QPoint(0, 0), QSize(800, 500));
        isAssembled = true;
    }

    // Revert the position and size for the parts.
    else {
        animatePart(ui->gpuLabel, originalPosSizes["gpu"].first, originalPosSizes["gpu"].second);
        animatePart(ui->cpuLabel, originalPosSizes["cpu"].first, originalPosSizes["cpu"].second);
        animatePart(ui->ramLabel, originalPosSizes["ram"].first, originalPosSizes["ram"].second);
        animatePart(ui->memoryLabel, originalPosSizes["memory"].first, originalPosSizes["memory"].second);
        animatePart(ui->motherboardLabel, originalPosSizes["motherboard"].first, originalPosSizes["motherboard"].second);
        animatePart(ui->caseLabel, originalPosSizes["case"].first, originalPosSizes["case"].second);
        isAssembled = false;
    }

    // Move the buttons to the front so the parts do not overlap.
    ui->assembleButton->raise();
    ui->testButton->raise();
}

// SLOT
void LearningWindow::toggleStepByStep() {

    if (stepByStepToggled) {

        // Return PC parts to their original positions
        ui->nextButton->setEnabled(false);
        ui->previousButton->setEnabled(false);
        ui->assembleButton->setEnabled(true);
        stepByStepToggled = false;
        ui->stepByStepLabel->setVisible(false);

        // Revert the position and size for all of the parts.
        animatePart(ui->gpuLabel, originalPosSizes["gpu"].first, originalPosSizes["gpu"].second);
        animatePart(ui->cpuLabel, originalPosSizes["cpu"].first, originalPosSizes["cpu"].second);
        animatePart(ui->ramLabel, originalPosSizes["ram"].first, originalPosSizes["ram"].second);
        animatePart(ui->memoryLabel, originalPosSizes["memory"].first, originalPosSizes["memory"].second);
        animatePart(ui->motherboardLabel, originalPosSizes["motherboard"].first, originalPosSizes["motherboard"].second);
        animatePart(ui->caseLabel, originalPosSizes["case"].first, originalPosSizes["case"].second);
    }

    else {

        ui->nextButton->setEnabled(true);
        ui->assembleButton->setEnabled(false);
        currentStep = 0;
        stepByStepToggled = true;
        ui->stepByStepLabel->setText("Click the arrow buttons to go to the next or previous step.");
        ui->stepByStepLabel->setVisible(true);

        //Set up PC components for step by step animation
        animatePart(ui->caseLabel, QPoint(50, 100), QSize(700, 400));
        animatePart(ui->motherboardLabel, QPoint(50, 10), QSize(151, 151));
        animatePart(ui->cpuLabel, QPoint(300, 10), QSize(121, 121));
        animatePart(ui->gpuLabel, QPoint(630, 10), QSize(161, 151));
        animatePart(ui->memoryLabel, QPoint(650, 220), QSize(141, 81));
        animatePart(ui->ramLabel, QPoint(700, 300), QSize(15, 130));
    }
}

void LearningWindow::nextStep() {

    // Move Motherboard into place, Enable previousButton if first step
    if (currentStep == 0) {
        ui->previousButton->setEnabled(true);
        previousPosSizes["motherboard"] = qMakePair( ui->motherboardLabel->pos(), ui->motherboardLabel->size());
        animatePart(ui->motherboardLabel, QPoint(215, 150), QSize(245, 245));
        ui->stepByStepLabel->setText("First, screw the motherboard into the case.");
    }

    // Move CPU into place
    else if (currentStep == 1) {
        previousPosSizes["cpu"] = qMakePair( ui->cpuLabel->pos(), ui->cpuLabel->size());
        animatePart(ui->cpuLabel, QPoint(305, 190), QSize(75, 75));
        ui->stepByStepLabel->setText("Next, gently install the CPU into the motherboard.");
    }

    // Move GPU into place
    else if (currentStep == 2) {
        previousPosSizes["gpu"] = qMakePair( ui->gpuLabel->pos(), ui->gpuLabel->size());
        animatePart(ui->gpuLabel, QPoint(220, 265), QSize(160, 160));
        ui->stepByStepLabel->setText("Then, carefully push the GPU into the GPU slot below the CPU until you hear a click.");
    }

    // Move RAM into place
    else if (currentStep == 3) {
        previousPosSizes["ram"] = qMakePair( ui->ramLabel->pos(), ui->ramLabel->size());
        animatePart(ui->ramLabel, QPoint(395, 170), QSize(15, 105));
        ui->stepByStepLabel->setText("Then, carefully push the RAM into the RAM slots next to the CPU until you hear a click.");
    }

    // Move Memory into place
    else if (currentStep == 4) {
        originalPosSizes["memory"] = qMakePair( ui->memoryLabel->pos(), ui->memoryLabel->size());
        animatePart(ui->memoryLabel, QPoint(260, 255), QSize(80, 40));
        ui->stepByStepLabel->setText("Finally, install the SSD above the GPU slot.");
        ui->nextButton->setEnabled(false);
    }

    currentStep++;
}

void LearningWindow::previousStep() {

    if (currentStep == 1) {
        ui->previousButton->setEnabled(false);
        animatePart(ui->motherboardLabel, previousPosSizes["motherboard"].first, previousPosSizes["motherboard"].second);
        ui->stepByStepLabel->setText("Click the arrow buttons to go to the next or previous step.");
    }

    else if (currentStep == 2) {
        animatePart(ui->cpuLabel, previousPosSizes["cpu"].first, previousPosSizes["cpu"].second);
        ui->stepByStepLabel->setText("First, screw the motherboard into the case.");
    }

    else if (currentStep == 3) {
        animatePart(ui->gpuLabel, previousPosSizes["gpu"].first, previousPosSizes["gpu"].second);
        ui->stepByStepLabel->setText("Next, gently install the CPU into the motherboard.");
    }

    else if(currentStep == 4) {
        animatePart(ui->ramLabel, previousPosSizes["ram"].first, previousPosSizes["ram"].second);
        ui->stepByStepLabel->setText("Then, carefully push the GPU into the GPU slot below the CPU until you hear a click.");
    }

    else if (currentStep == 5) {
        animatePart(ui->memoryLabel, originalPosSizes["memory"].first, originalPosSizes["memory"].second);
        ui->nextButton->setEnabled(true);
        ui->stepByStepLabel->setText("Then, carefully push the RAM into the RAM slots next to the CPU until you hear a click.");
    }

    currentStep--;
}

void LearningWindow::animatePart(QWidget* part, const QPoint& endPos, const QSize& endSize) {

    // Set up postioning animation.
    QPropertyAnimation* posAnim = new QPropertyAnimation(part, "pos");
    posAnim->setDuration(3000);
    posAnim->setEndValue(endPos);

    // Set up sizing animation.
    QPropertyAnimation* sizeAnim = new QPropertyAnimation(part, "size");
    sizeAnim->setDuration(3000);
    sizeAnim->setStartValue(part->size());
    sizeAnim->setEndValue(endSize);

    // Start the animations.
    posAnim->start(QAbstractAnimation::DeleteWhenStopped);
    sizeAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

bool LearningWindow::eventFilter(QObject* watched, QEvent* event) {

    if (event->type() == QEvent::MouseButtonPress) {

        if (watched == ui->gpuLabel) {
            showInfo("Graphics Processing Unit", "The GPU is responsible for displaying images, video, and animations on your screen. "
                        "\n\nIt handles complex visual calculations and connects to the motherboard using PCIe slots.");
            return true;
        }

        else if (watched == ui->cpuLabel) {
            showInfo("Central Processing Unit", "The CPU is the \"brain\" of the computer. It processes all the instructions and calculations needed to run programs. "
                        "\n\nThis connects to the motherboard’s CPU socket.");
            return true;
        }

        else if (watched == ui->ramLabel) {
            showInfo("Random Access Memory", "RAM temporarily stores data that the CPU uses while the computer is on. "
                        "\n\nIt allows programs to run smoothly and is installed into the motherboard’s RAM slots.");
            return true;
        }

        else if (watched == ui->memoryLabel) {
            showInfo("M.2 Solid State Drive", "This is a high-speed memory storage device that holds your files, programs, and operating system. "
                        "\n\nIt plugs directly into the motherboard’s M.2 slot for faster performance.");
            return true;
        }

        else if (watched == ui->caseLabel) {
            showInfo("Computer Case", "The case is the protective enclosure that houses all components of the PC. "
                        "\n\nIt provides structure, airflow, and protection for the internal hardware.");
            return true;
        }

        else if (watched == ui->motherboardLabel) {
            showInfo("Motherboard", "The motherboard is the main circuit board that connects all the computer's components. "
                        "\n\nIt provides slots and sockets for the CPU, RAM, GPU, storage, and more, allowing them to communicate.");

            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}
