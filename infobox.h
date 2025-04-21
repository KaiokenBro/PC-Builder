#ifndef INFOBOX_H
#define INFOBOX_H

/**
 * @file infobox.h
 *
 * @brief Header file for the InfoBox class.
 *
 * The InfoBox class provides a simple dialog window that displays
 * a message with a title and a close button. It is used throughout
 * the application to provide users with information or feedback
 * during the learning and testing phases.
 *
 * @date 04/22/2025
 */

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

/**
 * @class InfoBox
 *
 * @brief Displays a modal popup with a title, message, and close button.
 *
 * The InfoBox class is used to display contextual information, feedback,
 * or instructions in a clean and readable format. It appears in both the
 * LearningWindow and TestWindow to support user understanding.
 */
class InfoBox : public QDialog {
    Q_OBJECT

public:

    /**
     * @brief Constructor for InfoBox.
     * @param title The title displayed at the top of the dialog.
     * @param text The content message shown below the title.
     * @param parent Optional parent widget.
     */
    explicit InfoBox(const QString& title, const QString& text, QWidget* parent = nullptr);

private:

    /**
     * @brief Label to display the title of the info box.
     */
    QLabel* titleLabel;

    /**
     * @brief Label to display the content message of the info box.
     */
    QLabel* contentLabel;

    /**
     * @brief Button that closes the info box when clicked.
     */
    QPushButton* closeButton;

public slots:

    /**
     * @brief Closes the dialog when the close button is clicked.
     */
    void handleCloseClicked();

};

#endif // INFOBOX_H
