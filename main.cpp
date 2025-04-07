#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LearningWindow learningWindow;
    MainWindow mainWindow(&learningWindow);

    mainWindow.show();
    return a.exec();
}
