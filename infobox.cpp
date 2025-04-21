/**
 * @file infobox.cpp
 *
 * @brief Implementation of the InfoBox class.
 *
 * This class defines the behavior of a simple modal popup dialog
 * that displays a title, informational message, and a close button.
 * It is used throughout the application to communicate important
 * feedback or guidance to the user during the learning and testing process.
 *
 * @date 04/22/2025
 */

#include "infobox.h"

InfoBox::InfoBox(const QString& title, const QString& text, QWidget* parent) :
    QDialog(parent)
{
    setWindowTitle(title);
    setFixedSize(400, 250);

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Create the title label.
    titleLabel = new QLabel(title, this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Create label for the part information.
    contentLabel = new QLabel(text, this);
    contentLabel->setWordWrap(true);
    contentLabel->setStyleSheet("font-size: 16px;");
    contentLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    layout->addWidget(contentLabel);

    // Create the close botton.
    closeButton = new QPushButton("Close", this);
    closeButton->setStyleSheet("background-color: #4CAF50; font-size: 16px; border: none; padding: 10px;");
    layout->addWidget(closeButton);

    connect(closeButton,
            &QPushButton::clicked,
            this,
            &InfoBox::handleCloseClicked
    );

}

void InfoBox::handleCloseClicked() {
    accept();
}
