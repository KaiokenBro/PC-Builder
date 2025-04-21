/**
 * @file main.cpp
 *
 * @brief Entry point for the PC Builder educational application.
 *
 * Initializes the QApplication and the primary windows used in the program:
 * - MainWindow: The initial welcome screen.
 * - LearningWindow: Educational screen that explains PC components.
 * - TestWindow: Interactive screen for testing component assembly.
 *
 * The program starts by creating and linking the necessary windows
 * and then displays the MainWindow to the user.
 *
 * Team Members:
 * - Victor Valdez Landa
 * - Harrison Doppelt
 * - Charlie Jones
 * - Sam Garcia
 * - Richard Nghiem
 * - Nicholas Cicalese
 *
 * GitHub Usernames:
 * - KaiokenBro
 * - hdoppelt
 * - charlesj24240
 * - ncicalese
 * - SamuelFGarcia4
 * - Urichng
 *
 * Repository:
 * - https://github.com/UofU-CS3505/cs3505-assignment9-ncicalese.git
 *
 * @date 04/22/2025
 */

#include "mainwindow.h"
#include "learningwindow.h"
#include "testwindow.h"

#include <QApplication>

/**
 * @brief Main entry point for the application.
 *
 * Sets up the application and displays the main window.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Application exit status.
 */
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    TestWindow testWindow(nullptr);
    LearningWindow learningWindow(&testWindow);
    testWindow.setLearningWindow(&learningWindow);
    MainWindow mainWindow(&learningWindow);
    mainWindow.show();
    return a.exec();
}
