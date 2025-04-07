#ifndef LEARNINGWINDOW_H
#define LEARNINGWINDOW_H

#include "testwindow.h"

#include <QMainWindow>

namespace Ui { class LearningWindow; }

class LearningWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit LearningWindow(TestWindow* testWindow, QWidget* parent = nullptr);
    ~LearningWindow();

private:

    Ui::LearningWindow* ui;
    TestWindow* testWindow;

private slots:

    void onTestButtonClicked();

signals:



};

#endif // LEARNINGWINDOW_H
