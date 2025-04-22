#ifndef WINWINDOW_H
#define WINWINDOW_H

/**
 * @file winwindow.h
 *
 * @brief Header file for the WinWindow class.
 *
 * This window is opened when the user finishes building a complete PC.
 * It serves as a celebration window and it includes a PC image that
 * utilizes some Box2D physics.
 *
 * @date 04/22/2025
 */

#include <QMainWindow>
#include <Box2D/Box2D.h>
#include <QLabel>

namespace Ui {
class WinWindow;
}

class WinWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent Optional parent widget.
     */
    explicit WinWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~WinWindow();

private:
    /**
     * @brief The ui
     */
    Ui::WinWindow *ui;

    /**
     * @brief False if the user is not dragging the body (the PC image);
     * true if the user is dragging the body.
     */
    bool dragging = false;

    /**
     * @brief Helps to calculate the new position of the body when dragging.
     */
    QPoint dragOffset;

    /**
     * @brief Scales Box2D meters to window pixels. For example,
     * a scale factor of 100 means 1 meter in Box2D equals
     * 100 pixels in window coodinates.
     */
    const float scaleFactor;

    /**
     * @brief The world for Box2D
     */
    b2World world;

    /**
     * @brief The dynamic body representing the PC image.
     */
    b2Body* body;

    /**
     * @brief Given a position in Box2D coordnates, move the body in window coordinates.
     * @param object The label to move.
     * @param x The x coordinate in Box2D
     * @param y The y coordinate in Box2D
     */
    void translateMove(QLabel *object, float x, float y);

    /**
     * @brief Handles the dragging and moving of the body.
     * @param watched The object that was interacted with.
     * @param event The event.
     * @return True if event was properly handled; otherwise false.
     */
    bool eventFilter(QObject* watched, QEvent* event) override;

    /**
     * @brief Given a position in window coordinates, update the body's Box2D coordinates.
     * @param newPosition The position in window coordinates.
     */
    void updateBox2D(QPoint newPosition);

public slots:

    /**
     * @brief Instruct the world to perform a single step of simulation (60 Hz)
     */
    void updateWorld();
};

#endif // WINWINDOW_H
