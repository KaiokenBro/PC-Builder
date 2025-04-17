#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMimeData>
#include <QMainWindow>
#include <QDropEvent>
#include <QMoveEvent>
#include <QDragMoveEvent>
#include <QDrag>
#include <QPoint>

namespace Ui { class TestWindow; }

class TestWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit TestWindow(QWidget* parent = nullptr);
    ~TestWindow();

private:

    Ui::TestWindow* ui;
    QSize lastSize;
    QString lastName;
    QPoint location;
    QList<QString> dontMove;
    bool reset;

public slots:

    void receiveAnswer(bool correctness, QString reason, QString part, QPoint location);

private slots:

    QPoint snapLocation(QPoint cursor);
    void mousePressEvent(QMouseEvent* event);
    void dropEvent(QDropEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);

signals:

    void checkAnswer(QString part, QPoint location);
    int getCurrentStep();

};

#endif // TESTWINDOW_H
