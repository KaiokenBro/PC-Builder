#ifndef TESTCHECKER_H
#define TESTCHECKER_H

#include <QObject>
#include <QPoint>

class TestChecker : public QObject {
    Q_OBJECT

private:
    int step;
public:

    TestChecker();

public slots:

    void checkPlacement(QString part, QPoint location);
    int sendCurrentStep();

signals:

    void sendAnswer(bool correctness, QString reason, QString part, QPoint location);

};

#endif // TESTCHECKER_H
