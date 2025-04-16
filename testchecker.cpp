#include "testchecker.h"

TestChecker::TestChecker() {}

void TestChecker::checkPlacement(int step, QString part, QPoint location) {
    QString reason = "Correct";
    bool correctness = true;

    if (location.y() < 210 || location.x() > 530) {
        // Don't do anything if they are moving a part around outside the case.
    }

    else {

        switch(step){

        case 1:

            if (part != "motherboardLabel"){
                correctness = false;
                reason = "Not the right part";
            }

            else if (location != QPoint(200, 245)){
                correctness = false;
                reason = "Not the right location!";
            }

            break;

        case 2:

            if (part != "cpuLabel"){
                correctness = false;
                reason = "Not the right part";
            }

            else if (location != QPoint(315, 295)){
                correctness = false;
                reason = "Not the right location!";
            }

            break;

        case 3:

            if (part != "gpuLabel"){
                correctness = false;
                reason = "Not the right part";
            }

            else if (location != QPoint(180, 440)){
                correctness = false;
                reason = "Not the right location!";
            }

            break;

        case 4:

            if (part != "ramLabel1" && part != "ramLabel2"){
                correctness = false;
                reason = "Not the right part";
            }

            else if (location != QPoint(423, 270) && location != QPoint(443, 270)){
                correctness = false;
                reason = "Not the right location!";
            }

            break;

        case 5:

            if (part != "ramLabel1" && part != "ramLabel2"){
                correctness = false;
                reason = "Not the right part";
            }

            else if (location != QPoint(423, 270) && location != QPoint(443, 270)){
                correctness = false;
                reason = "Not the right location!";
            }

            break;

        case 6:

            if (part != "memoryLabel"){
                correctness = false;
                reason = "Not the right part";
            }

            else if (location != QPoint(260, 470)){
                correctness = false;
                reason = "Not the right location!";
            }

            break;
        }

        emit sendAnswer(correctness, reason, part);
    }
}
