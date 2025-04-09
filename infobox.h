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

public slots:
    void handleCloseClicked();

private:
    QLabel* titleLabel;
    QLabel* contentLabel;
    QPushButton* closeButton;
};

#endif // INFOBOX_H
