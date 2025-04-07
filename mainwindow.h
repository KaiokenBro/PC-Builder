#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "learningwindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    MainWindow(LearningWindow* learningWindow, QWidget* parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow* ui;
    LearningWindow* learningWindow;

private slots:

    void onStartButtonClicked();

signals:



};

#endif // MAINWINDOW_H
