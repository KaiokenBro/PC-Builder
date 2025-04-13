#ifndef TESTCHECKER_H
#define TESTCHECKER_H

#include <QObject>
#include <QPoint>

class TestChecker : public QObject
{
    Q_OBJECT
public:
    TestChecker();

signals:
    void sendAnswer(bool correctness, QString reason, QString part);

public slots:
    void checkPlacement(int step, QString part, QPoint location);

};

#endif // TESTCHECKER_H
