#ifndef TESTCHECKER_H
#define TESTCHECKER_H

/**
 * @file testchecker.h
 *
 * @brief Header file for the TestChecker class.
 *
 * The TestChecker class is responsible for verifying the correctness of
 * component placement in the TestWindow. It tracks the current step in
 * the assembly sequence and emits feedback signals based on user input.
 *
 * @date 04/22/2025
 */

#include <QObject>
#include <QPoint>

/**
 * @class TestChecker
 *
 * @brief Validates user input during the PC assembly testing phase.
 *
 * This class keeps track of the current assembly step and determines whether
 * a dropped component was placed correctly. It provides feedback to the
 * TestWindow using signals.
 */
class TestChecker : public QObject {
    Q_OBJECT

private:

    /**
     * @brief Tracks the current step in the component assembly process.
     */
    int step;

public:

    /**
     * @brief Constructor for TestChecker.
     */
    TestChecker();

public slots:

    /**
     * @brief Validates the position and identity of the dropped part.
     * @param part Name of the component being placed.
     * @param location Position where the component was dropped.
     */
    void checkPlacement(QString part, QPoint location);

    /**
     * @brief Returns the current assembly step.
     * @return int Current step number.
     */
    int sendCurrentStep();

signals:

    /**
     * @brief Emitted after validating a part placement.
     * @param correctness Whether the placement was correct.
     * @param reason Explanation for incorrect placement.
     * @param part Name of the part being placed.
     * @param location Final location of the placed part.
     */
    void sendAnswer(bool correctness, QString reason, QString part, QPoint location);

};

#endif // TESTCHECKER_H
