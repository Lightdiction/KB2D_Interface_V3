
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
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/comhw.h"

#define RATIO_WARNING_BG    1 / 2
#define MAX_DET_LEVEL       4095


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

    // Save Parameters in case of cancellation
    initialSpeed = ui->minTimeSlider->value() - 1;
    initialSelectivity = ui->maxTimeSlider->value() - 1;

    factorDet = 5;
    initialDetLevel = ui->detLevelSlider->value();

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
        kbDev.sendCom(MIDI_DET + (actualDetLevel & 0x7F));
        if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel & 0x7F))
            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_1_C);
        kbDev.sendCom(MIDI_DETH + (actualDetLevel >> 7));
        if (kbDev.checkFeedback(Check_DetLevelH) != (actualDetLevel >> 7))
            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_1b_C);

        // Set Detection Speed and Speed Selectivity to large values. Set Angle deviation to 25.
        kbDev.sendCom(MIDI_MINPOS + 0);
        if (kbDev.checkFeedback(Check_MinPos) != 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_2_C);
        kbDev.sendCom(MIDI_MAXPOS + 63);
        if (kbDev.checkFeedback(Check_MultPos) != 63)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_3_C);
        /*kbDev.sendCom(MIDI_HALFDELTA + 25);
        if (kbDev.checkFeedback(Check_HalfDelta) != 25)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_4_C);*/


        ui->statusBar->showMessage(tr("Calibration in process... Background detection level"), 0);
        // Start laser emission, set detection thresholf slightly above the actual background level and check that there is no more detection (make a loop).

        cancelValue = 0;

        saveCurrentDisplayAndDisable();
        setDetActionsVisibility(0);

        startFunc();

        ui->actionStopCal->setVisible(1);
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(0);

        while ((detOK == 0) && (cancelValue == 0))
        {
            kbDev.sendCom(MIDI_LEARNONE + 0x7C);

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
                        if (actualDetLevel > MAX_DET_LEVEL)
                        {
                            actualDetLevel = MAX_DET_LEVEL;
                            detOK = 1;          // We already reached the maximum level.
                        }
                        kbDev.sendCom(MIDI_DET + (actualDetLevel & 0x7F));
                        if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel & 0x7F))
                            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_5_C);
                        kbDev.sendCom(MIDI_DETH + (actualDetLevel >> 7));
                        if (kbDev.checkFeedback(Check_DetLevelH) != (actualDetLevel >> 7))
                            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_5b_C);
                    }
                }
                // Background has been detected - power has been returned on param(2)
                if (harpIn.getParam(0) == 0x90)
                {
                    //harpIn.setParam(2, (unsigned int)(4 * (harpIn.getParam(2) + (harpIn.getParam(1) << 7))) / 3);
                    int tempResult = (4 * ((int)harpIn.getParam(2) + (((int)harpIn.getParam(1)) << 7))) / 3;

                    if (tempResult > actualDetLevel)    // Since the value returned by param 3 is an average, it can be less than the actual detection threshold needed to avoid detections.
                        actualDetLevel = tempResult;
                    else
                        actualDetLevel += (2 * factorDet);        // For this reason actual detection level can only increase.

                    if (actualDetLevel > MAX_DET_LEVEL)
                        actualDetLevel = MAX_DET_LEVEL;

                    kbDev.sendCom(MIDI_DET + (actualDetLevel & 0x7F));
                    if (kbDev.checkFeedback(Check_DetLevel) != (actualDetLevel & 0x7F))
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_6_C);
                    kbDev.sendCom(MIDI_DETH + (actualDetLevel >> 7));
                    if (kbDev.checkFeedback(Check_DetLevelH) != (actualDetLevel >> 7))
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_6b_C);

                    if (actualDetLevel == MAX_DET_LEVEL)
                        SendError(this, tr("The background level is too high.\n\n"
                                        "To avoid this, reduce the power of your laser or choose an environment with a higher or darker ceiling / background.\n"
                                        "The background shall have a low reflectance"), GrDet_AutoSet_1, tr("Background is high = 4095"));
                    if (actualDetLevel == MAX_DET_LEVEL)
                        detOK = 1;          // We already reached the maximum level
                }
            }
        }
        pauseFunc();

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

        //detOK = 0;

        ui->statusBar->showMessage(tr("Waiting for interaction..."), 0);
        kbDev.sendCom(MIDI_LEARNONE + 0x7C);
        startFunc();

        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(0);
        kbDev.waitForFeedback(1);

        while (kbDev.isWaitingFb() && (cancelValue == 0))
            QCoreApplication::processEvents();

        // first detection has been validated...
        if ((harpIn.getParam(0) == 0x80) && (harpIn.getParam(1) == 0x0) && (harpIn.getParam(2) == 0x0))
        {
            ui->statusBar->showMessage(tr("Interaction detected, calibration in process"), 0);
            kbDev.waitForFeedback(1);
            // Now wait for detection value to be sent
            QElapsedTimer calMaxTim;
            calMaxTim.start();
            while (kbDev.isWaitingFb() && (cancelValue == 0))
            {
                QCoreApplication::processEvents();
                if (calMaxTim.elapsed() > 5000)
                {
                    SendError(this, tr("The calibration process is abnormally long.\nThis may happen if the detection is saturated."
                                       "Please restart the detection calibration"), GrDet_AutoSet_2);
                    cancelValue = 1;
                }
            }

            if (harpIn.getParam(0) == 0x90)        // Detection process is done, power level has been measured.
            {
                actualDetLevel = ((int)harpIn.getParam(2) + (((int)harpIn.getParam(1)) << 7));
                if (actualDetLevel > (MAX_DET_LEVEL * 9 / 10))
                    SendError(this, tr("The Detection threshold is very high, try reducing the amplification, the laser power, interact at a further distance or with a darker"
                                       " object if possible, in order to reduce the signal detected"), GrDet_AutoSet_2a);
            }
            else if (cancelValue == 0)
            {
                cancelValue = 1;
                SendError(this, tr("Something unexpected happened, please restart the detection calibration"), GrDet_AutoSet_3);
            }
        }
        else
        {
            cancelValue = 1;
            SendError(this, tr("Something unexpected happened, please restart the detection calibration"), GrDet_AutoSet_4);
        }

        ///// NOW SET THE SPEED
        ui->statusBar->showMessage(tr("Calibration in process... Speed..."), 0);

        if (actualDetLevel <= saveDetLevel)
        {
            if (cancelValue == 0)
                SendError(this, tr("Background calibration is not correct, please restart the detection calibration"), GrDet_AutoSet_5);
        }
        else if((actualDetLevel * RATIO_WARNING_BG) < saveDetLevel)
        {
            // If the signal level is close to the background level (30%), display a warning. If it cannot detect, display an error.
            // Else, adapt the detection level to half the signal level.
            kbDev.sendCom(MIDI_DET + (saveDetLevel & 0x7F));
            if (kbDev.checkFeedback(Check_DetLevel) != (saveDetLevel & 0x7F))
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_10_C);
            kbDev.sendCom(MIDI_DETH + (saveDetLevel >> 7));
            if (kbDev.checkFeedback(Check_DetLevelH) != (saveDetLevel >> 7))
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_10b_C);

            // Then, adapt the Speed.
            detOK = 0;
            saveSpeed = 1;
            while ((detOK == 0) && (cancelValue == 0))
            {
                kbDev.sendCom(MIDI_LEARNONE + 0x7C);
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
                            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_11_C);
                    }
                }
                if ((harpIn.getParam(0) == 0x80) && (harpIn.getParam(1) == 0x0) && (harpIn.getParam(2) == 0x0))     // first detection has been validated...
                {
                    saveSpeed += 1;
                    if (saveSpeed > 31)
                    {
                        saveSpeed = 31;
                        detOK = 1;
                    }
                    kbDev.sendCom(MIDI_MINPOS + saveSpeed);
                    if (kbDev.checkFeedback(Check_MinPos) != saveSpeed)
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_12_C);
                }
            }
            pauseFunc();

            ui->actionStart->setVisible(0);
            ui->actionPause->setVisible(0);
            SendError(this, tr("The difference between the subject and the background is low. This may result in difficulties to detect or in false detections.\n"
                            "Try to use a darker background or to set a higher distance between the subject and the background."), \
                            GrDet_AutoSet_6, tr("Signal Level: ") + QString::number(actualDetLevel) + tr(", BG Level: ") + QString::number(saveDetLevel));
        }
        else
        {
            pauseFunc();
            qSleep(300);    // Ensure the detection stopped
            startFunc();

            kbDev.sendCom(MIDI_DET + ((actualDetLevel * RATIO_WARNING_BG) & 0x7F));
            if (kbDev.checkFeedback(Check_DetLevel) != ((actualDetLevel * RATIO_WARNING_BG) & 0x7F))
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_13_C);
            kbDev.sendCom(MIDI_DETH + ((actualDetLevel * RATIO_WARNING_BG) >> 7));
            if (kbDev.checkFeedback(Check_DetLevelH) != ((actualDetLevel * RATIO_WARNING_BG) >> 7))
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_13b_C);

            // Then, adapt the Speed.
            detOK = 0;
            saveSpeed = 1;
            while ((detOK == 0) && (cancelValue == 0))
            {
                kbDev.sendCom(MIDI_LEARNONE + 0x7C);
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
                            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_14_C);
                    }
                }
                if ((harpIn.getParam(0) == 0x80) && (harpIn.getParam(1) == 0x0) && (harpIn.getParam(2) == 0x0))     // first detection has been validated...
                {
                    saveSpeed += 1;
                    if (saveSpeed > 31)
                    {
                        saveSpeed = 31;
                        detOK = 1;
                    }
                    kbDev.sendCom(MIDI_MINPOS + saveSpeed);
                    if (kbDev.checkFeedback(Check_MinPos) != saveSpeed)
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_15_C);
                }
            }
        }
        pauseFunc();

        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(0);
        if (saveSpeed < 3)
        {
            kbDev.sendCom(MIDI_MAXPOS + 5);
            if (kbDev.checkFeedback(Check_MultPos) != 5)
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_16_C);
        }
        else
        {
            kbDev.sendCom(MIDI_MAXPOS + (saveSpeed * 4 / 3));
            if (kbDev.checkFeedback(Check_MultPos) != (saveSpeed * 4 / 3))
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_17_C);
        }

        // Calibration aborted
        if (cancelValue == 1)   // Reset Det Level, Speed and Speed Selectivity to previous levels
        {
            kbDev.sendCom(MIDI_DET + (initialDetLevel & 0x7F));
            if (kbDev.checkFeedback(Check_DetLevel) != (initialDetLevel & 0x7F))
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_18_C);
            kbDev.sendCom(MIDI_DETH + (initialDetLevel >> 7));
            if (kbDev.checkFeedback(Check_DetLevelH) != (initialDetLevel >> 7))
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_18b_C);

            kbDev.sendCom(MIDI_MINPOS + initialSpeed);
            if (kbDev.checkFeedback(Check_MinPos) != initialSpeed)
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_19_C);
            kbDev.sendCom(MIDI_MAXPOS + initialSelectivity);
            if (kbDev.checkFeedback(Check_MultPos) != initialSelectivity)
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_AutoSet_20_C);
            ui->statusBar->showMessage(tr("Calibration aborted"), 5000);
        }
        else // System is now ready, update the display on the interface.
            QMessageBox::information(this, tr("Autoset detection parameters"), tr("Detection parameters are now set"));

        updateAll(0);
        kbDev.sendCom(MIDI_LEARNONE + 0x7A);  // Reset to normal mode (quit calibration)
        startFunc();

        ui->actionStopCal->setVisible(0);
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(1);
        restoreDisplay();
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

void MainWindow::on_autosetButton_clicked()
{
    autoSetDet();
}


///////////////////////////
///////// SPIN BOX ////////
///////////////////////////

void MainWindow::on_FPSspinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->FPSSlider->setValue(ui->FPSspinBox->value());
}

void MainWindow::on_detLevelspinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->detLevelSlider->setValue(ui->detLevelspinBox->value());
}

void MainWindow::on_minTimeSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->minTimeSlider->setValue(ui->minTimeSpinBox->value());
}

void MainWindow::on_maxTimeSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->maxTimeSlider->setValue(ui->maxTimeSpinBox->value());
}

void MainWindow::on_releaseSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->releaseSlider->setValue(ui->releaseSpinBox->value());
}

/*
 * ===================
 * Hardware Gain
 * ===================
 */
void MainWindow::on_hardAmpComboBox_currentIndexChanged(int index)
{
    if (!updateInProgress)
    {
        kbDev.sendCom(MIDI_GAIN + (char)index);
        if (kbDev.checkFeedback(Check_Gain) != index)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_HardAmp_C);
    }
}

/////////////////////////////////////
////////////// SLIDER ///////////////
/////////////////////////////////////


void MainWindow::on_FPSSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_FPS + (char)(value - 50));
    int result = kbDev.checkFeedback(Check_FPS);
    if (result < 0)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_FPSSlider);
    else
    {
        ui->FPSspinBox->setValue(result + 50);
        ui->FPSSlider->setValue(result + 50);
    }
}

void MainWindow::on_detLevelSlider_valueChanged(int value)
{
    static bool isBusy = false;
    if (!isBusy)
    {
        isBusy = true;
        kbDev.sendCom(MIDI_DET + (value & 0x7F));
        int result = kbDev.checkFeedback(Check_DetLevel);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_DetLevelSlider);
        else
        {
            kbDev.sendCom(MIDI_DETH + (value >> 7));
            int result2 = kbDev.checkFeedback(Check_DetLevelH);
            if (result2 < 0)
                SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_DetLevelSlider_2);
            else
            {
                ui->detLevelspinBox->setValue(result + (result2 << 7));
                ui->detLevelSlider->setValue(result + (result2 << 7));
            }
        }
        isBusy = false;
    }
}

void MainWindow::on_minTimeSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_MINPOS + (char)(value - 1));
    int result = kbDev.checkFeedback(Check_MinPos);
    if (result < 0)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_DetSpeedSlider);
    else
    {
        ui->minTimeSpinBox->setValue(result + 1);
        ui->minTimeSlider->setValue(result + 1);
    }
}

void MainWindow::on_maxTimeSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_MAXPOS + (char)(value - 1));
    int result = kbDev.checkFeedback(Check_MultPos);
    if (result < 0)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_DetSelectivitySlider);
    else
    {
        ui->maxTimeSpinBox->setValue(result + 1);
        ui->maxTimeSlider->setValue(result + 1);
    }
}

void MainWindow::on_releaseSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_RELEASE + (char)(value));
    int result = kbDev.checkFeedback(Check_Release);
    if (result < 0)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrDet_ReleaseSlider);
    else
    {
        ui->releaseSpinBox->setValue(result);
        ui->releaseSlider->setValue(result);
    }
}

