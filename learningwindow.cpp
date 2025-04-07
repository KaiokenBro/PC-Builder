#include "learningwindow.h"
#include "ui_learningwindow.h"

// CONSTRUCTOR
LearningWindow::LearningWindow(TestWindow* testWindow, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::LearningWindow)
{
    ui->setupUi(this);
    this->testWindow = testWindow;

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
