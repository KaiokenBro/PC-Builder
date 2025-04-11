#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QPainter>
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

    Ui::TestWindow *ui;
    QSize lastSize;

private slots:
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    QPoint snapLocation(QPoint cursor);


signals:



};

#endif // TESTWINDOW_H
