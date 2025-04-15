#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "learningwindow.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <Box2D/Box2D.h>

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

    // Box2D scenes and icon
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pcIconItem;

    // Box2D physics variables
    b2World* world;
    b2Body* pcIconBody;

    // Timer for the animation
    QTimer animationTimer;

private slots:

    void onStartButtonClicked();
    void frameAnimation();

};

#endif // MAINWINDOW_H
