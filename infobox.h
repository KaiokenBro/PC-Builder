#ifndef INFOBOX_H
#define INFOBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class InfoBox : public QDialog {
    Q_OBJECT

public:

    explicit InfoBox(const QString& title, const QString& text, QWidget* parent = nullptr);

private:

    QLabel* titleLabel;
    QLabel* contentLabel;
    QPushButton* closeButton;

public slots:

    void handleCloseClicked();

};

#endif // INFOBOX_H
