#include "infobox.h"

InfoBox::InfoBox(const QString& title, const QString& text, QWidget* parent)
    : QDialog(parent)
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
    layout->addWidget(contentLabel);

    // Create the close botton.
    closeButton = new QPushButton("Close", this);
    closeButton->setStyleSheet("background-color: #4CAF50; font-size: 16px; border: none; padding: 10px;");
    layout->addWidget(closeButton);

    // When the closeButton is clicked, close the dialog box.
    connect(closeButton,
            &QPushButton::clicked,
            this,
            &InfoBox::handleCloseClicked);
}

// Closes the dialog box.
void InfoBox::handleCloseClicked() {
    accept();
}

