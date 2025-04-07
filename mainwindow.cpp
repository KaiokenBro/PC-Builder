#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "learningwindow.h"

// CONSTRUCTOR
MainWindow::MainWindow(LearningWindow* learningWindow, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->learningWindow = learningWindow;

    // When startButton clicked, open learningWindow
    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onStartButtonClicked
    );

}

// DESTRUCTOR
MainWindow::~MainWindow() {
    delete ui;
}

// SLOT
void MainWindow::onStartButtonClicked() {
    this->hide();
    learningWindow->show();
}
