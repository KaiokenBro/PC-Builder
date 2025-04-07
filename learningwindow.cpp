#include "learningwindow.h"
#include "ui_learningwindow.h"

LearningWindow::LearningWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::LearningWindow)
{
    ui->setupUi(this);
}

LearningWindow::~LearningWindow() {
    delete ui;
}
