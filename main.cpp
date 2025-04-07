#include "mainwindow.h"
#include "learningwindow.h"
#include "testwindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    TestWindow testWindow;
    LearningWindow learningWindow(&testWindow);
    MainWindow mainWindow(&learningWindow);

    mainWindow.show();
    return a.exec();
}
