
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Gr Det **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions related to Detection Parameters
 * (Also Number of Beams)
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/comhw.h"

#define RATIO_WARNING_BG    1 / 2


///////////// FUNCTIONS /////////////

void MainWindow::updateAngleBoxVisibility()
{
    int i_ind;
    for (i_ind = 0 ; i_ind < MAX_NBEAMS ; i_ind++)
    {
        Z0_ComboBox[i_ind]->setEnabled(0);
        angleDoubleSpinBox[i_ind]->setEnabled(0);
        angleDoubleSpinBox[i_ind]->setVisible(0);
        angleLabel[i_ind]->setVisible(0);
        ui->XMin_Label->setVisible(0);
        ui->XMax_Label->setVisible(0);
        ui->angleMinDoubleSpinBox->setVisible(0);
        ui->angleMaxDoubleSpinBox->setVisible(0);
    }
    if (ui->nBeamsXComboBox->currentIndex() == MAX_NBEAMS)
    {
        ui->XMin_Label->setVisible(1);
        ui->XMax_Label->setVisible(1);
        ui->angleMinDoubleSpinBox->setVisible(1);
        ui->angleMaxDoubleSpinBox->setVisible(1);
    }
    else
    {
        for (i_ind = 0 ; i_ind < MAX_NBEAMS ; i_ind++)
        {
            angleDoubleSpinBox[i_ind]->setVisible(1);
            angleLabel[i_ind]->setVisible(1);
        }
        for (i_ind = 0 ; i_ind < ui->nBeamsXComboBox->currentIndex() + 1 ; i_ind++)
        {
            Z0_ComboBox[i_ind]->setEnabled(1);
            angleDoubleSpinBox[i_ind]->setEnabled(1);
        }
    }
}

/*
 * ========================
 * Detection Assistant
 * ========================
 */
void MainWindow::autoSetDet()
{
    int detOK = 0, actualDetLevel = 0, saveDetLevel = 0, saveSpeed = 0;
    int initialDetLevel, initialSpeed, initialSelectivity;

    int factorDet = 1;
    int maxDetLevel = 127;

    // Save Parameters in case of cancellation
    initialDetLevel = ui->detLevelSlider->value() - 1;
    initialSpeed = 128 - ui->detSpeedSlider->value();
    initialSelectivity = 128 - ui->detSelectivitySlider->value();

    if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
    {
        factorDet = 5;
        maxDetLevel = 4095;
        initialDetLevel = ui->detLevelSlider->value();
    }

    // First: Detect only the background.
    // Calibration may not work properly with parasitic lights...
    // Stop laser emission.
    pauseFunc();
    if ((QMessageBox::information(this, tr("Start calibration"), tr("Start your laser and place the KB2D at the desired position.\n"
                                                        "The FPS value should be previously selected to match the FPS rate of your laser frame.\n\n"
                                                        "Then click on OK.\n"
                                                        "The calibration process may take a few seconds. "
                                                        "It may take a bit longer when the laser is projected on uneven surfaces.\n"
                                                        "A message will be displayed when the KB2D is ready for the next step.\n\n"
                                                        "The calibration process may not work properly if parasitic lights (light spots, lamps) are present.\n\n"
                                                        "During the process, the following parameters will be adjusted:\n"
                                                        "- Detection threshold\n"
                                                        "- Detection speed\n"
                                                        "- Speed selectivity\n\n"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
    {
        // Set det threshold to minimum.
        actualDetLevel = 0 + factorDet;
        if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
        {
            kbDev.sendCom(MIDI_DET + (actualDetLevel & 0x7F));
            if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel & 0x7F))
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_1_C);
            kbDev.sendCom(MIDI_DETH + (actualDetLevel >> 7));
            if (kbDev.checkFeedback(Check_DetLevelH) != (actualDetLevel >> 7))
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_1b_C);
        }
        else
        {
            kbDev.sendCom(MIDI_DET + actualDetLevel);
            if (kbDev.checkFeedback(Check_DetLevel) != actualDetLevel)
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_1c_C);
        }

        // Set Detection Speed and Speed Selectivity to large values. Set Angle deviation to 25.
        kbDev.sendCom(MIDI_MINPOS + 3);
        if (kbDev.checkFeedback(Check_MinPos) != 3)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_2_C);
        kbDev.sendCom(MIDI_MAXPOS + 127);
        if (kbDev.checkFeedback(Check_MultPos) != 127)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_3_C);
        kbDev.sendCom(MIDI_HALFDELTA + 25);
        if (kbDev.checkFeedback(Check_HalfDelta) != 25)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_4_C);


        ui->statusBar->showMessage(tr("Calibration in process... Background detection level"), 0);
        // Start laser emission, set detection thresholf slightly above the actual background level and check that there is no more detection (make a loop).

        cancelValue = 0;

        ui->portsGroup->setDisabled(1);
        for (int _loci = 0; _loci < Group_NumTotal; _loci++)
            groupList[_loci]->setDisabled(1);
        setDetActionsVisibility(0);

        startFunc();

#ifndef NO_MORE_BUTTONS
        ui->stopCalButton->setHidden(0);
        ui->startButton->setHidden(1);
        ui->pauseButton->setHidden(1);
#endif
        ui->actionStopCal->setVisible(1);
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(0);

        while ((detOK == 0) && (cancelValue == 0))
        {
            if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
                kbDev.sendCom(MIDI_LEARNONE + 0x7C);
            else
                kbDev.sendCom(MIDI_LEARNONE + 0x7D);

            QElapsedTimer timer;
            timer.start();
            // The system is calibrated with the help of the first confirmation (after 0.1 second) and fine tuning with the second calibration (after 2,2 seconds for instance).
            // Open a warning window if the level of the background is higher than 0x3F (lower laser power).
            kbDev.waitForFeedback(1);
            while (kbDev.isWaitingFb() && (cancelValue == 0))   // Check if we have a detection at lower lovel.
            {
                QCoreApplication::processEvents();
                if (timer.elapsed() > 500)
                {
                    // No background detection...
                    harpIn.setParam(0,0);
                    harpIn.setParam(1,0);
                    harpIn.setParam(2,0);
                    kbDev.waitForFeedback(0);   // End the loop
                    detOK = 1;  // No more detection - det level is OK
                }
            }

            // Background has been detected... (Averaging has started, it takes minimum 2 seconds).
            if ((harpIn.getParam(0) == 0x80) && (harpIn.getParam(1) == 0x0) && (harpIn.getParam(2) == 0x0))
            {
                timer.restart();
                kbDev.waitForFeedback(1);
                while (kbDev.isWaitingFb() && (cancelValue == 0))
                {
                    QCoreApplication::processEvents();

                    // If the detection is perfect, 0x90 feedback is received after 2s. We take 3s ta have a small margin (bad detection = almost good threshold).
                    if (timer.elapsed() > 3000)
                    {
                        // No background detection...
                        harpIn.setParam(0,0);
                        harpIn.setParam(1,0);
                        harpIn.setParam(2,0);
                        kbDev.waitForFeedback(0);    // End the loop
                        actualDetLevel += (2 * factorDet);    // Increase very slightly, and now the background is set
                        if (actualDetLevel > maxDetLevel)
                        {
                            actualDetLevel = maxDetLevel;
                            detOK = 1;          // We already reached the maximum level.
                        }
                        if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
                        {
                            kbDev.sendCom(MIDI_DET + (actualDetLevel & 0x7F));
                            if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel & 0x7F))
                                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_5_C);
                            kbDev.sendCom(MIDI_DETH + (actualDetLevel >> 7));
                            if (kbDev.checkFeedback(Check_DetLevelH) != (actualDetLevel >> 7))
                                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_5b_C);
                        }
                        else
                        {
                            kbDev.sendCom(MIDI_DET + actualDetLevel);
                            if (kbDev.checkFeedback(Check_DetLevel) != actualDetLevel)
                                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_5c_C);
                        }
                    }
                }
                // Background has been detected - power has been returned on param(2)
                if (harpIn.getParam(0) == 0x90)
                {
                    //harpIn.setParam(2, (unsigned int)(4 * (harpIn.getParam(2) + (harpIn.getParam(1) << 7))) / 3);
                    int tempResult = (4 * (harpIn.getParam(2) + (harpIn.getParam(1) << 7))) / 3;

                    if (tempResult > actualDetLevel)    // Since the value returned by param 3 is an average, it can be less than the actual detection threshold needed to avoid detections.
                        actualDetLevel = tempResult;
                    else
                        actualDetLevel += (2 * factorDet);        // For this reason actual detection level can only increase.

                    if (actualDetLevel > maxDetLevel)
                        actualDetLevel = maxDetLevel;

                    if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
                    {
                        kbDev.sendCom(MIDI_DET + (actualDetLevel & 0x7F));
                        if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel & 0x7F))
                            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_6_C);
                        kbDev.sendCom(MIDI_DETH + (actualDetLevel >> 7));
                        if (kbDev.checkFeedback(Check_DetLevelH) != (actualDetLevel >> 7))
                            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_6b_C);
                    }
                    else
                    {
                        kbDev.sendCom(MIDI_DET + actualDetLevel);
                        if (kbDev.checkFeedback(Check_DetLevel) != actualDetLevel)
                            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_6c_C);
                    }

                    if (actualDetLevel == maxDetLevel)
                        SendError(this, tr("The background level is high, it may cause decrease of accuracy or detection error.\n\n"
                                        "To avoid this, reduce the power of your laser or choose an environment with a higher or darker ceiling / background.\n"
                                        "The background shall have a low reflectance"), GrDet_AutoSet_1, tr("Background is high = 127"));
                    if (actualDetLevel == maxDetLevel)
                        detOK = 1;          // We already reached the maximum level
                }
            }
        }
        pauseFunc();
#ifndef NO_MORE_BUTTONS
        ui->startButton->setHidden(1);
        ui->pauseButton->setHidden(1);
#endif
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(0);
        saveDetLevel = actualDetLevel;

        QMessageBox::information(this, tr("Background calibrated"), tr("Background detection level = ") + QString::number(saveDetLevel) + \
                                                                tr("\n\nAfter pressing OK, interact with a beam at the desired height, then wait for the end of calibration confirmation.\n\n"
                                                                "This may take a few seconds. Do not change or remove the interaction while the calibration is running."));

        //////////////////////////////////////////////////////////////////////////
        // Ask to the user to interact with one beam (center beam for instance) //
        ///////////// Now finish calibrating the detection threshold /////////////
        //////////////////////////////////////////////////////////////////////////

        detOK = 0;

        ui->statusBar->showMessage(tr("Calibration in process... Detection level of interaction"), 0);
        if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
            kbDev.sendCom(MIDI_LEARNONE + 0x7C);
        else
            kbDev.sendCom(MIDI_LEARNONE + 0x7D);
        startFunc();
#ifndef NO_MORE_BUTTONS
        ui->startButton->setHidden(1);
        ui->pauseButton->setHidden(1);
#endif
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(0);
        kbDev.waitForFeedback(1);
        while (kbDev.isWaitingFb() && (cancelValue == 0))
        {
            QCoreApplication::processEvents();
        }
        while ((detOK == 0) && (cancelValue == 0))
        {
            if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
                kbDev.sendCom(MIDI_LEARNONE + 0x7C);
            else
                kbDev.sendCom(MIDI_LEARNONE + 0x7D);
            QElapsedTimer timer;
            timer.start();
            kbDev.waitForFeedback(1);
            while (kbDev.isWaitingFb() && (cancelValue == 0))
            {
                QCoreApplication::processEvents();
                if (timer.elapsed() > 500)
                {
                    // No background detection...
                    harpIn.setParam(0,0);
                    harpIn.setParam(1,0);
                    harpIn.setParam(2,0);
                    kbDev.waitForFeedback(0);    // End the loop
                    detOK = 1;  // No more detection - det level is calibrated for the Hand detection
                }
            }
            if ((harpIn.getParam(0) == 0x80) && (harpIn.getParam(1) == 0x0) && (harpIn.getParam(2) == 0x0))     // first detection has been validated...
            {
                timer.restart();
                kbDev.waitForFeedback(1);
                while (kbDev.isWaitingFb() && (cancelValue == 0))
                {
                    QCoreApplication::processEvents();
                    if (timer.elapsed() > 3000)      // Level is almost good, but not yet...
                    {
                        // No background detection...
                        harpIn.setParam(0,0);
                        harpIn.setParam(1,0);
                        harpIn.setParam(2,0);
                        kbDev.waitForFeedback(0);    // End the loop
                        actualDetLevel += (2 * factorDet);    // Increase very slightly, until the first detection do not happen again.
                        if (actualDetLevel > maxDetLevel)
                        {
                            actualDetLevel = maxDetLevel;
                            detOK = 1;          // We already reached the maximum level
                        }
                        if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
                        {
                            kbDev.sendCom(MIDI_DET + (actualDetLevel & 0x7F));
                            if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel & 0x7F))
                                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_7_C);
                            kbDev.sendCom(MIDI_DETH + (actualDetLevel >> 7));
                            if (kbDev.checkFeedback(Check_DetLevelH) != (actualDetLevel >> 7))
                                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_7b_C);
                        }
                        else
                        {
                            kbDev.sendCom(MIDI_DET + actualDetLevel);
                            if (kbDev.checkFeedback(Check_DetLevel) != actualDetLevel)
                                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_7c_C);
                        }
                    }
                }
                if (harpIn.getParam(0) == 0x90)        // Detection process is done, power level has been measured.
                {
                    if (actualDetLevel < (harpIn.getParam(2) + (harpIn.getParam(1) << 7)) + (3 * factorDet))
                        actualDetLevel = (harpIn.getParam(2) + (harpIn.getParam(1) << 7)) + (3 * factorDet);
                    else
                        actualDetLevel += (2 * factorDet);
                    if (actualDetLevel >= maxDetLevel)
                    {
                        actualDetLevel = maxDetLevel;
                        detOK = 1;          // We already reached the maximum level
                    }
                    if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
                    {
                        kbDev.sendCom(MIDI_DET + (actualDetLevel & 0x7F));
                        if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel & 0x7F))
                            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_8_C);
                        kbDev.sendCom(MIDI_DETH + (actualDetLevel >> 7));
                        if (kbDev.checkFeedback(Check_DetLevelH) != (actualDetLevel >> 7))
                            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_8b_C);
                    }
                    else
                    {
                        kbDev.sendCom(MIDI_DET + actualDetLevel);
                        if (kbDev.checkFeedback(Check_DetLevel) != actualDetLevel)
                            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_8c_C);
                    }
                }
            }
        }
        ui->statusBar->showMessage(tr("Calibration in process... Speed..."), 0);

        if (actualDetLevel == saveDetLevel)
        {
            if (cancelValue == 0)
                SendError(this, tr("The KB2D cannot detect interactions with the subject.\nThe background may be too close or too reflective compared to the object."), GrDet_AutoSet_9_C);
        }
        else if((actualDetLevel * RATIO_WARNING_BG) < saveDetLevel)
        {
            // If the signal level is close to the background level (30%), display a warning. If it cannot detect, display an error.
            // Else, adapt the detection level to half the signal level.
            if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
            {
                kbDev.sendCom(MIDI_DET + (saveDetLevel & 0x7F));
                if (kbDev.checkFeedback(Check_DetLevel) != (saveDetLevel & 0x7F))
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_10_C);
                kbDev.sendCom(MIDI_DETH + (saveDetLevel >> 7));
                if (kbDev.checkFeedback(Check_DetLevelH) != (saveDetLevel >> 7))
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_10b_C);
            }
            else
            {
                kbDev.sendCom(MIDI_DET + saveDetLevel);
                if (kbDev.checkFeedback(Check_DetLevel) != saveDetLevel)
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_10c_C);
            }
            // Then, adapt the Speed.
            detOK = 0;
            saveSpeed = 3;
            while ((detOK == 0) && (cancelValue == 0))
            {
                if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
                    kbDev.sendCom(MIDI_LEARNONE + 0x7C);
                else
                    kbDev.sendCom(MIDI_LEARNONE + 0x7D);
                QElapsedTimer timer;
                timer.start();
                kbDev.waitForFeedback(1);
                while (kbDev.isWaitingFb() && (cancelValue == 0))
                {
                    QCoreApplication::processEvents();
                    if (timer.elapsed() > 200)
                    {
                        // No background detection...
                        harpIn.setParam(0,0);
                        harpIn.setParam(1,0);
                        harpIn.setParam(2,0);
                        kbDev.waitForFeedback(0);    // End the loop
                        detOK = 1;  // No more detection - det level is calibrated for the Hand detection

                        saveSpeed /= 3;
                        kbDev.sendCom(MIDI_MINPOS + saveSpeed);
                        if (kbDev.checkFeedback(Check_MinPos) != saveSpeed)
                            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_11_C);
                    }
                }
                if ((harpIn.getParam(0) == 0x80) && (harpIn.getParam(1) == 0x0) && (harpIn.getParam(2) == 0x0))     // first detection has been validated...
                {
                    saveSpeed += 2;
                    if (saveSpeed > 127)
                    {
                        saveSpeed = 127;
                        detOK = 1;
                    }
                    kbDev.sendCom(MIDI_MINPOS + saveSpeed);
                    if (kbDev.checkFeedback(Check_MinPos) != saveSpeed)
                        SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_12_C);
                }
            }
            pauseFunc();
#ifndef NO_MORE_BUTTONS
            ui->startButton->setHidden(1);
            ui->pauseButton->setHidden(1);
#endif
            ui->actionStart->setVisible(0);
            ui->actionPause->setVisible(0);
            SendError(this, tr("The difference between the subject and the background is low. This may result in difficulties to detect or in false detections.\n"
                            "Try to use a darker background or to set a higher distance between the subject and the background."), \
                            GrDet_AutoSet_2, tr("Signal Level: ") + QString::number(actualDetLevel) + tr(", BG Level: ") + QString::number(saveDetLevel));
        }
        else
        {
            if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
            {
                kbDev.sendCom(MIDI_DET + ((actualDetLevel * RATIO_WARNING_BG) & 0x7F));
                if (kbDev.checkFeedback(Check_DetLevel) != ((actualDetLevel * RATIO_WARNING_BG) & 0x7F))
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_13_C);
                kbDev.sendCom(MIDI_DETH + ((actualDetLevel * RATIO_WARNING_BG) >> 7));
                if (kbDev.checkFeedback(Check_DetLevelH) != ((actualDetLevel * RATIO_WARNING_BG) >> 7))
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_13b_C);
            }
            else
            {
                kbDev.sendCom(MIDI_DET + (actualDetLevel * RATIO_WARNING_BG));
                if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel * RATIO_WARNING_BG))
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_13c_C);
            }

            // Then, adapt the Speed.
            detOK = 0;
            saveSpeed = 3;
            while ((detOK == 0) && (cancelValue == 0))
            {
                if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
                    kbDev.sendCom(MIDI_LEARNONE + 0x7C);
                else
                    kbDev.sendCom(MIDI_LEARNONE + 0x7D);
                QElapsedTimer timer;
                timer.start();
                kbDev.waitForFeedback(1);
                while (kbDev.isWaitingFb() && (cancelValue == 0))
                {
                    QCoreApplication::processEvents();
                    if (timer.elapsed() > 200)
                    {
                        // No background detection...
                        harpIn.setParam(0,0);
                        harpIn.setParam(1,0);
                        harpIn.setParam(2,0);
                        kbDev.waitForFeedback(0);    // End the loop
                        detOK = 1;  // No more detection - det level is calibrated for the Hand detection

                        saveSpeed /= 3;
                        kbDev.sendCom(MIDI_MINPOS + saveSpeed);
                        if (kbDev.checkFeedback(Check_MinPos) != saveSpeed)
                            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_14_C);
                    }
                }
                if ((harpIn.getParam(0) == 0x80) && (harpIn.getParam(1) == 0x0) && (harpIn.getParam(2) == 0x0))     // first detection has been validated...
                {
                    saveSpeed += 2;
                    if (saveSpeed > 127)
                    {
                        saveSpeed = 127;
                        detOK = 1;
                    }
                    kbDev.sendCom(MIDI_MINPOS + saveSpeed);
                    if (kbDev.checkFeedback(Check_MinPos) != saveSpeed)
                        SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_15_C);
                }
            }
        }
        pauseFunc();
#ifndef NO_MORE_BUTTONS
        ui->startButton->setHidden(1);
        ui->pauseButton->setHidden(1);
#endif
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(0);
        if ((saveSpeed * 5 / 4) > 127)
        {
            kbDev.sendCom(MIDI_MAXPOS + 0);
            if (kbDev.checkFeedback(Check_MultPos) != 0)
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_16_C);
        }
        else
        {
            kbDev.sendCom(MIDI_MAXPOS + 127 - (saveSpeed * 5 / 4));
            if (kbDev.checkFeedback(Check_MultPos) != 127 - (saveSpeed * 5 / 4))
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_17_C);
        }

        // Calibration aborted
        if (cancelValue == 1)   // Reset Det Level, Speed and Speed Selectivity to previous levels
        {
            if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
            {
                kbDev.sendCom(MIDI_DET + (initialDetLevel & 0x7F));
                if (kbDev.checkFeedback(Check_DetLevel) != (initialDetLevel & 0x7F))
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_18_C);
                kbDev.sendCom(MIDI_DETH + (initialDetLevel >> 7));
                if (kbDev.checkFeedback(Check_DetLevelH) != (initialDetLevel >> 7))
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_18b_C);
            }
            else
            {
                kbDev.sendCom(MIDI_DET + initialDetLevel);
                if (kbDev.checkFeedback(Check_DetLevel) != initialDetLevel)
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_18c_C);
            }

            kbDev.sendCom(MIDI_MINPOS + initialSpeed);
            if (kbDev.checkFeedback(Check_MinPos) != initialSpeed)
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_19_C);
            kbDev.sendCom(MIDI_MAXPOS + initialSelectivity);
            if (kbDev.checkFeedback(Check_MultPos) != initialSelectivity)
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AutoSet_20_C);
            ui->statusBar->showMessage(tr("Calibration aborted"), 5000);
        }
        else // System is now ready, update the display on the interface.
            QMessageBox::information(this, tr("Autoset detection parameters"), tr("Detection parameters are now set"));

        updateAll(0);
        if ((kbDev.getID(SUBVERSION) >= 36) || (kbDev.getID(VERSION) > 6))
            kbDev.sendCom(MIDI_LEARNONE + 0x7A);  // Reset to normal mode (quit calibration)
        startFunc();

#ifndef NO_MORE_BUTTONS
        ui->stopCalButton->setHidden(1);
        ui->startButton->setHidden(1);
        ui->pauseButton->setHidden(0);
#endif
        ui->actionStopCal->setVisible(0);
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(1);
        ui->portsGroup->setEnabled(1);
        for (int _loci = 0; _loci < Group_NumTotal; _loci++)
            groupList[_loci]->setEnabled(1);
        setDetActionsVisibility(1);

        if (cancelValue == 1)
            ui->statusBar->showMessage(tr("Calibration aborted"), 5000);
        else
            ui->statusBar->showMessage(tr("Calibration done!"), 5000);
    }
}


////////////// BUTTONS //////////////

void MainWindow::on_thresholdButton_clicked()
{
}

void MainWindow::on_stopCalButton_clicked()
{
    cancelValue = 1;
    kbDev.waitForFeedback(0);
}

void MainWindow::on_autosetButton_clicked()
{
    autoSetDet();
}



///////////////////////////
///////// SPIN BOX ////////
///////////////////////////

void MainWindow::on_FPSspinBox_editingFinished()
{
    ui->FPSSlider->setValue(ui->FPSspinBox->value());
}

void MainWindow::on_detLevelspinBox_editingFinished()
{
    ui->detLevelSlider->setValue(ui->detLevelspinBox->value());
}

void MainWindow::on_detSpeedspinBox_editingFinished()
{
    ui->detSpeedSlider->setValue(ui->detSpeedspinBox->value());
}

void MainWindow::on_detSelectivityspinBox_editingFinished()
{
    ui->detSelectivitySlider->setValue(ui->detSelectivityspinBox->value());
}

void MainWindow::on_accuracySpinBox_editingFinished()
{
    ui->accuracySlider->setValue(ui->accuracySpinBox->value());
}

void MainWindow::on_releaseSpinBox_editingFinished()
{
    ui->releaseSlider->setValue(ui->releaseSpinBox->value());
}

/*
 * ==============================
 * Set n Beams X
 * (Continuous or discrete)
 * ==============================
 */
void MainWindow::on_nBeamsXComboBox_currentIndexChanged(int index)
{
    if (index >= 0)
    {
        if (index < MAX_NBEAMS)
        {
            ui->accuracySpinBox->setEnabled(1);
            ui->accuracySlider->setEnabled(1);
            ui->learnOneButton->setEnabled(1);
            kbDev.sendCom(MIDI_NBEAMSX + (char)(index + 1));
            if (kbDev.checkFeedback(Check_nBeamsX) != (ui->nBeamsXComboBox->currentIndex() + 1))
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_NBeamsX_C);
        }
        else
        {
            ui->accuracySpinBox->setEnabled(0);
            ui->accuracySlider->setEnabled(0);
            ui->learnOneButton->setEnabled(0);
            kbDev.sendCom(MIDI_NBEAMSX + (char)(127));  // ContX = 1
            if (kbDev.checkFeedback(Check_ContX) != 1)
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_NBeamsX_2_C);
        }
        updateAngleBoxVisibility();
    }
}

/*
 * ===================
 * Hardware Gain
 * ===================
 */
void MainWindow::on_hardAmpComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_GAIN + (char)index);
    if (kbDev.checkFeedback(Check_Gain) != index)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_HardAmp_C);
}

/////////////////////////////////////
////////////// SLIDER ///////////////
/////////////////////////////////////


void MainWindow::on_FPSSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_FPS + (char)(value - 50));
    int result = kbDev.checkFeedback(Check_FPS);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_FPSSlider_C);
    else
    {
        ui->FPSspinBox->setValue(result + 50);
        ui->FPSSlider->setValue(result + 50);
    }
}

void MainWindow::on_detLevelSlider_valueChanged(int value)
{
    static bool isBusy = false;
    if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
    {
        if (!isBusy)
        {
            isBusy = true;
            kbDev.sendCom(MIDI_DET + (value & 0x7F));
            int result = kbDev.checkFeedback(Check_DetLevel);
            if (result < 0)
                SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_DetLevelSlider_C);
            else
            {
                kbDev.sendCom(MIDI_DETH + (value >> 7));
                int result2 = kbDev.checkFeedback(Check_DetLevelH);
                if (result2 < 0)
                    SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_DetLevelSlider_2_C);
                else
                {
                    ui->detLevelspinBox->setValue(result + (result2 << 7));
                    ui->detLevelSlider->setValue(result + (result2 << 7));
                }
            }
            isBusy = false;
        }
    }
    else
    {
        kbDev.sendCom(MIDI_DET + (char)(value - 1));
        int result = kbDev.checkFeedback(Check_DetLevel);
        if (result < 0)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_DetLevelSlider_3_C);
        else
        {
            ui->detLevelspinBox->setValue(result + 1);
            ui->detLevelSlider->setValue(result + 1);
        }
    }
}

void MainWindow::on_detSpeedSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_MINPOS + (char)(128 - value));
    int result = kbDev.checkFeedback(Check_MinPos);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_DetSpeedSlider_C);
    else
    {
        ui->detSpeedspinBox->setValue(128 - result);
        ui->detSpeedSlider->setValue(128 - result);
    }
}

void MainWindow::on_detSelectivitySlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_MAXPOS + (char)(128 - value));
    int result = kbDev.checkFeedback(Check_MultPos);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_DetSelectivitySlider_C);
    else
    {
        ui->detSelectivityspinBox->setValue(128 - result);
        ui->detSelectivitySlider->setValue(128 - result);
    }
}

void MainWindow::on_accuracySlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_HALFDELTA + (char)(value));
    int result = kbDev.checkFeedback(Check_HalfDelta);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_AccuracySlider_C);
    else
    {
        ui->accuracySpinBox->setValue(result);
        ui->accuracySlider->setValue(result);
    }
}

void MainWindow::on_releaseSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_RELEASE + (char)(value));
    int result = kbDev.checkFeedback(Check_Release);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrDet_ReleaseSlider_C);
    else
    {
        ui->releaseSpinBox->setValue(result);
        ui->releaseSlider->setValue(result);
    }
}

