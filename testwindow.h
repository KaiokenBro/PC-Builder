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
    QList<QString> dontMove;
    int step;

public slots:

    void receiveAnswer(bool correctness, QString reason, QString part);

private slots:

    QPoint snapLocation(QPoint cursor);
    void mousePressEvent(QMouseEvent* event);
    void dropEvent(QDropEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);

signals:

    void checkAnswer(int step, QString part, QPoint location);

};

#endif // TESTWINDOW_H
