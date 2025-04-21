#ifndef LEARNINGWINDOW_H
#define LEARNINGWINDOW_H

#include "testwindow.h"

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QMap>

namespace Ui { class LearningWindow; }

class LearningWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit LearningWindow(TestWindow* testWindow, QWidget* parent = nullptr);
    ~LearningWindow();
    bool eventFilter(QObject* watched, QEvent* event) override;
    void animatePart(QWidget* part, const QPoint& endPos, const QSize& endSize);

private:

    Ui::LearningWindow* ui;
    TestWindow* testWindow;
    QMap<QString, QPair<QPoint, QSize>> originalPosSizes;
    QMap<QString, QPair<QPoint, QSize>> previousPosSizes;
    bool stepByStepToggled;
    int currentStep;
    bool isAssembled;

private slots:

    void showInfo(const QString& title, const QString& text);
    void assemblePC();
    void onTestButtonClicked();
    void toggleStepByStep();
    void nextStep();
    void previousStep();

};

#endif // LEARNINGWINDOW_H
