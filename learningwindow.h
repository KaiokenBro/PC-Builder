#ifndef LEARNINGWINDOW_H
#define LEARNINGWINDOW_H

#include <QMainWindow>

namespace Ui { class LearningWindow; }

class LearningWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit LearningWindow(QWidget *parent = nullptr);
    ~LearningWindow();

private:

    Ui::LearningWindow *ui;

};

#endif // LEARNINGWINDOW_H
