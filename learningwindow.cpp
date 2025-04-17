#include "learningwindow.h"
#include "ui_learningwindow.h"
#include "infobox.h"

// CONSTRUCTOR
LearningWindow::LearningWindow(TestWindow* testWindow, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::LearningWindow),
    isAssembled(false)
{
    ui->setupUi(this);
    this->testWindow = testWindow;
    stepByStepToggled = false;

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

    // When testButton clicked, open testWindow
    connect(ui->testButton,
            &QPushButton::clicked,
            this,
            &LearningWindow::onTestButtonClicked
    );

    // When assembleButton clicked assemble PC parts.
    connect(ui->assembleButton,
            &QPushButton::clicked,
            this,
            &LearningWindow::assemblePC
    );

    // Enable/Disable Step by Step button
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

// DESTRUCTOR
LearningWindow::~LearningWindow() {
    delete ui;
}

// SLOT
void LearningWindow::onTestButtonClicked() {
    this->hide();
    testWindow->show();
}

// SLOT
void LearningWindow::showInfo(const QString& title, const QString& text) {

    // Create info box with the clicked parts information and open box.
    InfoBox* dialog = new InfoBox(title, text, this);
    dialog->exec();

    // Close when done.
    delete dialog;
}

// SLOT
void LearningWindow::assemblePC() {

    if (!isAssembled) {
        // Set the position and size for the parts.
        animatePart(ui->gpuLabel, QPoint(175, 250), QSize(300, 300));
        animatePart(ui->cpuLabel, QPoint(290, 125), QSize(80, 80));
        animatePart(ui->ramLabel, QPoint(397, 100), QSize(15, 130));
        animatePart(ui->memoryLabel, QPoint(230, 300), QSize(105, 50));
        animatePart(ui->motherboardLabel, QPoint(175, 75), QSize(300, 300));
        animatePart(ui->caseLabel, QPoint(0, 0), QSize(800, 500));
        isAssembled = true;
    }

    else {
        // Revert the position and size for the parts.
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
        //Return PC parts to their original positions
        ui->nextButton->setEnabled(false);
        ui->previousButton->setEnabled(false);
        ui->assembleButton->setEnabled(true);
        stepByStepToggled = false;

        //Revert the position and size for all of the parts.
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

        //Set up PC components for step by step animation
        animatePart(ui->caseLabel, QPoint(50, 100), QSize(700, 400));
        animatePart(ui->motherboardLabel, QPoint(50, 10), QSize(151, 151));
        animatePart(ui->cpuLabel, QPoint(300, 10), QSize(121, 121));
        animatePart(ui->gpuLabel, QPoint(630, 10), QSize(161, 151));
        animatePart(ui->memoryLabel, QPoint(650, 220), QSize(141, 81));
        animatePart(ui->ramLabel, QPoint(700, 300), QSize(15, 130));
    }
}

// SLOT
void LearningWindow::nextStep() {

    // Move Motherboard into place, Enable previousButton if first step
    if (currentStep == 0) {
        ui->previousButton->setEnabled(true);

        // Save the previous motherboard position
        previousPosSizes["motherboard"] = qMakePair( ui->motherboardLabel->pos(), ui->motherboardLabel->size());

        // Put the Motherboard into place
        animatePart(ui->motherboardLabel, QPoint(215, 150), QSize(245, 245));

        // Maybe display text saying "First, install the motherboard in the PC case"?
    }
    // Move CPU into place
    else if (currentStep == 1){

        // Save the previous CPU position
        previousPosSizes["cpu"] = qMakePair( ui->cpuLabel->pos(), ui->cpuLabel->size());

        animatePart(ui->cpuLabel, QPoint(305, 190), QSize(75, 75));
    }
    // Move GPU into place
    else if (currentStep == 2) {

        // Save the previous GPU position
        previousPosSizes["gpu"] = qMakePair( ui->gpuLabel->pos(), ui->gpuLabel->size());


        animatePart(ui->gpuLabel, QPoint(190, 285), QSize(280, 280));
    }
    // Move RAM into place
    else if (currentStep == 3) {

        // Save the previous RAM position
        previousPosSizes["ram"] = qMakePair( ui->ramLabel->pos(), ui->ramLabel->size());

        animatePart(ui->ramLabel, QPoint(395, 170), QSize(15, 105));
    }
    // Move Memory into place
    else if (currentStep == 4) {

        originalPosSizes["memory"] = qMakePair( ui->memoryLabel->pos(), ui->memoryLabel->size());

        animatePart(ui->memoryLabel, QPoint(250, 335), QSize(95, 45));
    }

    currentStep++;

    // Animate based off of currentStep

    if (currentStep == 5) {
        ui->nextButton->setEnabled(false);
    }
}

// SLOT
void LearningWindow::previousStep() {

    if (currentStep == 1) {
        ui->previousButton->setEnabled(false);
        animatePart(ui->motherboardLabel, previousPosSizes["motherboard"].first, previousPosSizes["motherboard"].second);
    }

    else if (currentStep == 2) {

        animatePart(ui->cpuLabel, previousPosSizes["cpu"].first, previousPosSizes["cpu"].second);
    }

    else if (currentStep == 3) {
        animatePart(ui->gpuLabel, previousPosSizes["gpu"].first, previousPosSizes["gpu"].second);
    }

    else if(currentStep == 4) {
    // ????????
        animatePart(ui->ramLabel, previousPosSizes["ram"].first, previousPosSizes["ram"].second);
    }

    else if (currentStep == 5) {
        animatePart(ui->memoryLabel, originalPosSizes["memory"].first, originalPosSizes["memory"].second);
        ui->nextButton->setEnabled(true);
    }

    currentStep--;

    // Return to previous step based off of current step
}

// METHOD
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

// METHOD
bool LearningWindow::eventFilter(QObject* watched, QEvent* event) {

    if (event->type() == QEvent::MouseButtonPress) {

        if (watched == ui->gpuLabel) {
            showInfo("GPU", "This is often called the graphics card, this handles graphics and visual output. "
                            "It connects to the motherboard via a PCIe slot.");
            return true;
        }

        else if (watched == ui->cpuLabel) {
            showInfo("CPU", "The ""brain"" of the computer, this handles all the instructions, "
                            "this plugs into the motherboard’s CPU socket.");
            return true;
        }

        else if (watched == ui->ramLabel) {
            showInfo("RAM", "This is the RAM, this acts as temporary memory for active data and programs. "
                            "This is installed into the motherboard’s RAM slots.");
            return true;
        }

        else if (watched == ui->memoryLabel) {
            showInfo("Memory", "This is the memory of the computer, fast storage device for files and the operating system."
                               " It plugs into the motherboard’s M.2 slot.");
            return true;
        }

        else if (watched == ui->caseLabel) {
            showInfo("Case", "This is the case that puts all the pieces together");
            return true;
        }

        else if (watched == ui->motherboardLabel) {
            showInfo("Motherboard", "The main circuit board that connects all components, this houses slots and ports for the CPU, RAM, GPU, and storage.");
            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}
