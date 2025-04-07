#include "testwindow.h"
#include "ui_testwindow.h"

// CONSTRUCTOR
TestWindow::TestWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
}

// DESTRUCTOR
TestWindow::~TestWindow() {
    delete ui;
}
