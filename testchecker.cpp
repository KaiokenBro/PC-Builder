/**
 * @file testchecker.cpp
 *
 * @brief Implementation of the TestChecker class.
 *
 * This class validates the user's drag-and-drop component placements
 * during the PC assembly test phase in TestWindow. It checks both the
 * part type and position against the current step, and emits a signal
 * containing the results.
 *
 * @date 04/22/2025
 */

#include "testchecker.h"

TestChecker::TestChecker() { step = 1; }

void TestChecker::checkPlacement(QString part, QPoint location)
{
    QString reason = "Correct";
    bool correctness = true;

    if (location.y() < 210 || location.x() > 530) {
        // Don't do anything if they are moving a part around outside the case.
    }

    else {

        switch (step) {

        case 1:

            if (part != "motherboardLabel") {
                correctness = false;
                reason = "Not the right part to install first";
            }

            else if (location != QPoint(200, 245)) {
                correctness = false;
                reason = "Not the right location for the Mother Board!";
            }

            else {
                reason = "Perfectly in place. The mother board is right where it should be.";
            }
            break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:

            if (part == "cpuLabel") {
                if (location != QPoint(315, 295)) {
                    correctness = false;
                    reason = "Not the right location for the CPU!";
                } else {
                    reason = "Great job, the CPU is right where it should be.";
                }
            }

            else if (part == "memoryLabel") {
                if (location != QPoint(260, 370)) {
                    correctness = false;
                    reason = "Not the right location for the memory!";
                } else {
                    reason = "Well done, your computer now has memory.";
                }
            }

            else if (part == "gpuLabel") {
                if (location != QPoint(200, 370)) {
                    correctness = false;
                    reason = "Not the right location for the GPU!";
                } else {
                    reason = "Nice, all your graphics are going to look great now.";
                }
            }

            else if (part == "ramLabel1" || part == "ramLabel2") {
                if (location != QPoint(423, 270) && location != QPoint(443, 270)) {
                    correctness = false;
                    reason = "Not the right location for the RAM!";
                } else {
                    reason = "Way to go, you installed the RAM stick correctly.";
                }
            }

            break;
        }

        if (correctness) {
            step++;
        }

        emit sendAnswer(correctness, reason, part, location);
    }
}

int TestChecker::sendCurrentStep()
{
    return step;
}
