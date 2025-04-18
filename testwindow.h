#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMimeData>
#include <QMainWindow>
#include <QDropEvent>
#include <QMoveEvent>
#include <QDragMoveEvent>
#include <QDrag>
#include <QPoint>
#include <QMediaPlayer>
#include <QAudioOutput>

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

    /**
     * @brief Media player for the Good! sound effect.
     */
    QMediaPlayer* goodAudio;

    /**
     * @brief Media player for the Bad! sound effect.
     */
    QMediaPlayer* badAudio;

    /**
     * @brief Media player for the Win! sound effect.
     */
    QMediaPlayer* winAudio;

    /**
     * @brief Audio output for the Win! sound effect.
     */
    QAudioOutput* winAudioOutput;

    /**
     * @brief Audio output for the Good! sound effect.
     */
    QAudioOutput* goodAudioOutput;

    /**
     * @brief Audio output for the Bad! sound effect.
     */
    QAudioOutput* badAudioOutput;

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
