
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Gr Angles **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions related to Angles Selection
 * - Also Learn One Angle
 * - Also Angles Calibration
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/comhw.h"


void MainWindow::updateAngleBoxVisibility()
{
    // Hide all
    ui->anglesWidget->setVisible(0);

    for (int i_ind = 0 ; i_ind < MAX_NBEAMS ; i_ind++)
    {
        for (int _j = 0 ; _j < Ports_Num ; _j++)
        {
            if (Z0_ComboBox[_j][i_ind])
                Z0_ComboBox[_j][i_ind]->setVisible(0);
            if (LabelZ0Combo[_j][i_ind])
                LabelZ0Combo[_j][i_ind]->setVisible(0);
            if (enableButton[_j][i_ind])
                enableButton[_j][i_ind]->setVisible(0);
            if (assignButton[_j][i_ind])
                assignButton[_j][i_ind]->setVisible(0);
        }
        angleDoubleSpinBox[i_ind]->setVisible(0);
        angleLearn[i_ind]->setVisible(0);
    }

    ui->anglesWidget->setVisible(1);

    for (int i_ind = 0 ; i_ind < ui->nBeamsXComboBox->currentIndex() + 1 ; i_ind++)
    {
        for (int _j = 0 ; _j < Ports_Num ; _j++)
        {
            if (Z0_ComboBox[_j][i_ind])
                Z0_ComboBox[_j][i_ind]->setVisible(1);
            if (LabelZ0Combo[_j][i_ind])
                LabelZ0Combo[_j][i_ind]->setVisible(1);
            if (enableButton[_j][i_ind])
                enableButton[_j][i_ind]->setVisible(1);
            if (assignButton[_j][i_ind])
                assignButton[_j][i_ind]->setVisible(1);
        }
        angleDoubleSpinBox[i_ind]->setVisible(1);
        angleLearn[i_ind]->setVisible(1);
    }
}

void MainWindow::multiAngleSpinBox_editing(int nIndex)
{
    if (!kbDev.isConnected())
        return;
    int angleLDeploy[3] = {MIDI_ANGLEXL0};
    int angleHDeploy[3] = {MIDI_ANGLEXH0};
    if (angleDoubleSpinBox[nIndex]->value() != angleSaveValue[nIndex])
    {
        angleSaveValue[nIndex] = angleDoubleSpinBox[nIndex]->value();
        char test1 = ((int)floor(angleDoubleSpinBox[nIndex]->value() * 10) & 0x7F);
        char test2 = (((int)floor((angleDoubleSpinBox[nIndex]->value() * 10) / 128)) + 63);
        kbDev.sendCom(angleLDeploy[0], angleLDeploy[1] + nIndex, angleLDeploy[2] + test1);
        kbDev.sendCom(angleHDeploy[0], angleHDeploy[1] + nIndex, angleHDeploy[2] + test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX0 + nIndex)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH0 + nIndex)))
            SendError(this, tr("No Feedback / Error on Feedback received."), GrAngles_SpinBoxMulti);
    }
}

/*
 * ==============================
 * learnOneAngle
 * ==============================
 */
void MainWindow::learnOneAngle(int beamInd)
{
    if ((beamInd >= 0) && (beamInd <= ui->nBeamsXComboBox->currentIndex()))
    {
        if (kbDev.isWaitingFb())
            cancelValue = 1;
        else
        {
            cancelValue = 0;

            if ((QMessageBox::information(this, tr("Interact with beams n°") + QString::number(beamInd + 1), tr("Interact with the beam n°") + QString::number(beamInd + 1) +
                                          tr(", until it plays the corresponding note."), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
            {
                kbDev.sendCom(MIDI_LEARNONE + beamInd);
                ui->statusBar->showMessage(tr("Waiting for interaction..."), 0);
                angleLearn[beamInd]->setStyleSheet("background-color:#C22;");

                saveCurrentDisplayAndDisable();
                setDetActionsVisibility(0);

                startFunc();

                ui->actionStopCal->setVisible(1);
                ui->actionStart->setVisible(0);
                ui->actionPause->setVisible(0);

                QElapsedTimer timer;
                timer.start();
                kbDev.waitForFeedback(1);
                while ((kbDev.isWaitingFb() || (harpIn.getParam(0) != 0x80)) && (cancelValue == 0))
                {
                    QCoreApplication::processEvents();
                }
                ui->statusBar->showMessage(tr("Maintain the interaction until the calibration is done... - t=") + (QString::number(timer.elapsed())), 0);

                timer.restart();
                kbDev.waitForFeedback(1);
                while ((kbDev.isWaitingFb() || (harpIn.getParam(0) != 0x90)) && (cancelValue == 0))
                {
                    QCoreApplication::processEvents();
                }
                if ((kbDev.getID(SUBVERSION) >= 36) || (kbDev.getID(VERSION) > 6))
                    kbDev.sendCom(MIDI_LEARNONE + 0x7A);  // Reset to normal mode (quit calibration)

                ui->actionStopCal->setVisible(0);
                ui->actionStart->setVisible(0);
                ui->actionPause->setVisible(1);
                restoreDisplay();
                setDetActionsVisibility(1);
                updateAll(0);
                angleLearn[beamInd]->setStyleSheet("");
                if (cancelValue == 1)
                    ui->statusBar->showMessage(tr("Calibration aborted"), 5000);
                else
                {
                    ui->statusBar->showMessage(tr("Calibration done! - t=") + (QString::number(timer.elapsed())), 5000);
                    emit oneAngleCalibrated(beamInd);
                }
            }
        }
    }
    else
        disconnect(this, &MainWindow::oneAngleCalibrated, this, nullptr);
}

void MainWindow::on_enableAngFilterCheckBox_toggled(bool checked)
{
    if (checked)
    {
        kbDev.sendCom(MIDI_ANGFILTER + (char)1);
        if (kbDev.checkFeedback(Check_AngFilter) != 1)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrAngles_AngFilter_1);
    }
    else
    {
        kbDev.sendCom(MIDI_ANGFILTER + (char)0);
        if (kbDev.checkFeedback(Check_AngFilter) != 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrAngles_AngFilter_2);
    }
    ui->accuracySpinBox->setEnabled(checked);
}

/*
 * ==============================
 * calibrateAngles
 * ==============================
 */
void MainWindow::calibrateAngles()
{
    cancelValue = 0;

    QString nBeamsString = QString::number(ui->nBeamsXComboBox->currentIndex() + 1) + ".";

    if ((QMessageBox::information(this, tr("Interact with beams"), tr("Interact with the first beam and last beam"
                                  " (wait for the note on each beam).\n"
                                  "Before starting this calibration, please verify the number of beams.\n"
                                  "\nYou have currently set the number of beams to ") + nBeamsString, \
                                  QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
    {
        kbDev.sendCom(MIDI_LEARNONE + 0x7F);
        ui->statusBar->showMessage(tr("Waiting for interaction..."), 0);
        angleLearn[0]->setStyleSheet("background-color:#C22;");

        saveCurrentDisplayAndDisable();
        setDetActionsVisibility(0);

        startFunc();

        ui->actionStopCal->setVisible(1);
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(0);

        QElapsedTimer timer;
        timer.start();
        kbDev.waitForFeedback(1);
        while ((kbDev.isWaitingFb() || (harpIn.getParam(0) != 0x80)) && (cancelValue == 0))
        {
            QCoreApplication::processEvents();
        }

        ui->statusBar->showMessage(tr("Calibration has begun! Please keep interacting... - t=") + (QString::number(timer.elapsed())), 0);

        timer.restart();
        kbDev.waitForFeedback(1);
        while ((kbDev.isWaitingFb() || (harpIn.getParam(0) != 0x90)) && (cancelValue == 0))
        {
            QCoreApplication::processEvents();
        }
        angleLearn[0]->setStyleSheet("");
        ui->statusBar->showMessage(tr("Calibration of first beam is done, now interact with the last beam! - t=") + (QString::number(timer.elapsed())), 0);

        if (cancelValue == 0)
        {
            pauseFunc();

            ui->actionStopCal->setVisible(1);
            ui->actionStart->setVisible(0);
            ui->actionPause->setVisible(0);
            QMessageBox::information(this, tr("Interact with beams"), tr("Calibration of first beam is done, interact with last beam!"));
            startFunc();

            ui->actionStopCal->setVisible(1);
            ui->actionStart->setVisible(0);
            ui->actionPause->setVisible(0);
        }
        angleLearn[ui->nBeamsXComboBox->currentIndex()]->setStyleSheet("background-color:#C22;");

        timer.restart();
        kbDev.waitForFeedback(1);
        while ((kbDev.isWaitingFb() || (harpIn.getParam(0) != 0x80)) && (cancelValue == 0))
        {
            QCoreApplication::processEvents();
        }

        ui->statusBar->showMessage(tr("Calibration has begun! Please keep interacting... - t=") + (QString::number(timer.elapsed())), 0);

        //timer.restart();
        kbDev.waitForFeedback(1);
        while ((kbDev.isWaitingFb() || (harpIn.getParam(0) != 0x90)) && (cancelValue == 0))
        {
            QCoreApplication::processEvents();
        }
        if ((kbDev.getID(SUBVERSION) >= 36) || (kbDev.getID(VERSION) > 6))
            kbDev.sendCom(0xB0, 0x30, 0x7A);  // Reset to normal mode (quit calibration)

        ui->actionStopCal->setVisible(0);
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(1);
        restoreDisplay();
        setDetActionsVisibility(1);
        updateAll(0);
        angleLearn[ui->nBeamsXComboBox->currentIndex()]->setStyleSheet("");
        if (cancelValue == 1)
            ui->statusBar->showMessage(tr("Calibration aborted"), 5000);
        else
            ui->statusBar->showMessage(tr("Calibration done!"), 5000);
    }
}

void MainWindow::on_accuracySpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    kbDev.sendCom(MIDI_HALFDELTA + (char)(ui->accuracySpinBox->value()));
    int result = kbDev.checkFeedback(Check_HalfDelta);
    if (result < 0)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrAngles_AccuracySlider);
    else
    {
        ui->accuracySpinBox->setValue(result);
    }
}

/*
 * ==============================
 * Set n Beams X
 * (Continuous or discrete)
 * ==============================
 */
void MainWindow::on_nBeamsXComboBox_currentIndexChanged(int index)
{
    if ((index >= 0) && !updateInProgress)
    {
        kbDev.sendCom(MIDI_NBEAMSX + (char)(index + 1));
        if (kbDev.checkFeedback(Check_nBeamsX) != (ui->nBeamsXComboBox->currentIndex() + 1))
            SendError(this, tr("No Feedback / Error on Feedback received."), GrAngles_NBeamsX);
        updateAngleBoxVisibility();
        // Update keyboard
        assignNoteToKey(Ports_Midi1, -1);
        assignNoteToKey(Ports_Midi3, -1);
        assignNoteToKey(Ports_Midi4, -1);
    }
}

/*
 * ==============================
 * Invert X angles / Notes
 * ==============================
 */
void MainWindow::invertX()
{
    kbDev.sendCom(MIDI_INVERTX);
    updateAll(0);
}

