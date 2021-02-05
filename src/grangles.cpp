
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





void MainWindow::on_angleMinDoubleSpinBox_editingFinished()
{
    if (ui->angleMinDoubleSpinBox->value() != angleSaveMin)
    {
        angleSaveMin = ui->angleMinDoubleSpinBox->value();
        char test1 = ((int)floor(ui->angleMinDoubleSpinBox->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleMinDoubleSpinBox->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGMINX + (char)test1);
        kbDev.sendCom(MIDI_ANGMINXH + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_AngleMinX)) || (test2 != kbDev.checkFeedback(Check_AngleMinXH)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBoxMin_C);
    }
}

void MainWindow::on_angleMaxDoubleSpinBox_editingFinished()
{
    if (ui->angleMaxDoubleSpinBox->value() != angleSaveMax)
    {
        angleSaveMax = ui->angleMaxDoubleSpinBox->value();
        char test1 = ((int)floor(ui->angleMaxDoubleSpinBox->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleMaxDoubleSpinBox->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGMAXX + (char)test1);
        kbDev.sendCom(MIDI_ANGMAXXH + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_AngleMaxX)) || (test2 != kbDev.checkFeedback(Check_AngleMaxXH)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBoxMax_C);
    }
}


void MainWindow::on_angleDoubleSpinBox_1_editingFinished()
{
    if (angleDoubleSpinBox[0]->value() != angleSaveValue[0])
    {
        angleSaveValue[0] = angleDoubleSpinBox[0]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_1->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_1->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL0 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH0 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX0)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH0)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox1_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_2_editingFinished()
{
    if (angleDoubleSpinBox[1]->value() != angleSaveValue[1])
    {
        angleSaveValue[1] = angleDoubleSpinBox[1]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_2->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_2->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL1 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH1 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX1)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH1)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox2_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_3_editingFinished()
{
    if (angleDoubleSpinBox[2]->value() != angleSaveValue[2])
    {
        angleSaveValue[2] = angleDoubleSpinBox[2]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_3->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_3->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL2 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH2 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX2)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH2)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox3_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_4_editingFinished()
{
    if (angleDoubleSpinBox[3]->value() != angleSaveValue[3])
    {
        angleSaveValue[3] = angleDoubleSpinBox[3]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_4->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_4->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL3 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH3 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX3)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH3)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox4_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_5_editingFinished()
{
    if (angleDoubleSpinBox[4]->value() != angleSaveValue[4])
    {
        angleSaveValue[4] = angleDoubleSpinBox[4]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_5->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_5->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL4 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH4 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX4)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH4)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox5_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_6_editingFinished()
{
    if (angleDoubleSpinBox[5]->value() != angleSaveValue[5])
    {
        angleSaveValue[5] = angleDoubleSpinBox[5]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_6->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_6->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL5 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH5 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX5)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH5)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox6_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_7_editingFinished()
{
    if (angleDoubleSpinBox[6]->value() != angleSaveValue[6])
    {
        angleSaveValue[6] = angleDoubleSpinBox[6]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_7->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_7->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL6 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH6 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX6)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH6)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox7_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_8_editingFinished()
{
    if (angleDoubleSpinBox[7]->value() != angleSaveValue[7])
    {
        angleSaveValue[7] = angleDoubleSpinBox[7]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_8->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_8->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL7 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH7 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX7)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH7)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox8_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_9_editingFinished()
{
    if (angleDoubleSpinBox[8]->value() != angleSaveValue[8])
    {
        angleSaveValue[8] = angleDoubleSpinBox[8]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_9->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_9->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL8 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH8 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX8)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH8)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox9_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_10_editingFinished()
{
    if (angleDoubleSpinBox[9]->value() != angleSaveValue[9])
    {
        angleSaveValue[9] = angleDoubleSpinBox[9]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_10->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_10->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL9 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH9 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX9)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH9)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox10_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_11_editingFinished()
{
    if (angleDoubleSpinBox[10]->value() != angleSaveValue[10])
    {
        angleSaveValue[10] = angleDoubleSpinBox[10]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_11->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_11->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL10 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH10 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX10)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH10)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox11_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_12_editingFinished()
{
    if (angleDoubleSpinBox[11]->value() != angleSaveValue[11])
    {
        angleSaveValue[11] = angleDoubleSpinBox[11]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_12->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_12->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL11 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH11 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX11)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH11)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox12_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_13_editingFinished()
{
    if (angleDoubleSpinBox[12]->value() != angleSaveValue[12])
    {
        angleSaveValue[12] = angleDoubleSpinBox[12]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_13->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_13->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL12 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH12 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX12)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH12)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox13_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_14_editingFinished()
{
    if (angleDoubleSpinBox[13]->value() != angleSaveValue[13])
    {
        angleSaveValue[13] = angleDoubleSpinBox[13]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_14->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_14->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL13 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH13 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX13)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH13)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox14_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_15_editingFinished()
{
    if (angleDoubleSpinBox[14]->value() != angleSaveValue[14])
    {
        angleSaveValue[14] = angleDoubleSpinBox[14]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_15->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_15->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL14 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH14 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX14)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH14)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox15_C);
    }
}

void MainWindow::on_angleDoubleSpinBox_16_editingFinished()
{
    if (angleDoubleSpinBox[15]->value() != angleSaveValue[15])
    {
        angleSaveValue[15] = angleDoubleSpinBox[15]->value();
        char test1 = ((int)floor(ui->angleDoubleSpinBox_16->value() * 10) & 0x7F);
        char test2 = (((int)floor((ui->angleDoubleSpinBox_16->value() * 10) / 128)) + 63);
        kbDev.sendCom(MIDI_ANGLEXL15 + (char)test1);
        kbDev.sendCom(MIDI_ANGLEXH15 + (char)test2);
        if ((test1 != kbDev.checkFeedback(Check_BeamAngleListX15)) || (test2 != kbDev.checkFeedback(Check_BeamAngleListXH15)))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrAngles_SpinBox16_C);
    }
}



void MainWindow::on_minMaxCalibrationButton_clicked()
{
    calibrateAngles();
}

void MainWindow::on_learnOneButton_clicked()
{
    learnOneAngle();
}



/*
 * ==============================
 * learnOneAngle
 * ==============================
 */
void MainWindow::learnOneAngle()
{
    bool ok = 0;
    cancelValue = 0;
    int beamToRead = 0;

    if (kbDev.checkFeedback(Check_ContX) == 1)
    {
        beamToRead = QInputDialog::getInt(this, tr("Beam To Read ?"), tr("Interact with the laser at the desired position, until the confirmation window appears.\n\n"
                                                                   "~ Angle to be detected? (0 =Min angle, or 1 = Max angle)"), 0, 0, 1, 1, &ok);
    }
    else
    {
        int _nBeams = kbDev.checkFeedback(Check_nBeamsX);
        beamToRead = QInputDialog::getInt(this, tr("Beam To Read ?"), tr("Interact with the laser at the desired position, until it plays the corresponding note.\n\n"
                                                                   "~ Index of the beam to be detected? (1 to ") + \
                                                                    QString::number(_nBeams) + ")", 1, 1, _nBeams, 1, &ok);
    }
    if (ok)
    {
        kbDev.sendCom(MIDI_LEARNONE + beamToRead - 1);
        ui->statusBar->showMessage(tr("Waiting for interaction..."), 0);

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
        updateAll(0);
        if (cancelValue == 1)
            ui->statusBar->showMessage(tr("Calibration aborted"), 5000);
        else
            ui->statusBar->showMessage(tr("Calibration done! - t=") + (QString::number(timer.elapsed())), 5000);
    }
}

/*
 * ==============================
 * calibrateAngles
 * ==============================
 */
void MainWindow::calibrateAngles()
{
    cancelValue = 0;
    QString nBeamsString;

    if (ui->nBeamsXComboBox->currentIndex() == 16)
        nBeamsString = tr("continuous.");
    else
        nBeamsString = QString::number(ui->nBeamsXComboBox->currentIndex() + 1) + ".";

    if ((QMessageBox::information(this, tr("Interact with beams"), tr("Interact with the first beam and last beam"
                                  " (wait for the note on each beam).\n"
                                  "Before starting this calibration, please verify the number of beams.\n"
                                  "\nYou have currently set the number of beams to ") + nBeamsString, \
                                  QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
    {
        kbDev.sendCom(MIDI_LEARNONE + 0x7F);
        ui->statusBar->showMessage(tr("Waiting for interaction..."), 0);

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
        ui->statusBar->showMessage(tr("Calibration of first beam is done, interact with last beam! - t=") + (QString::number(timer.elapsed())), 0);

        if (cancelValue == 0)
        {
            pauseFunc();
#ifndef NO_MORE_BUTTONS
            ui->stopCalButton->setHidden(0);
            ui->startButton->setHidden(1);
            ui->pauseButton->setHidden(1);
#endif
            ui->actionStopCal->setVisible(1);
            ui->actionStart->setVisible(0);
            ui->actionPause->setVisible(0);
            QMessageBox::information(this, tr("Interact with beams"), tr("Calibration of first beam is done, interact with last beam!"));
            startFunc();
#ifndef NO_MORE_BUTTONS
            ui->stopCalButton->setHidden(0);
            ui->startButton->setHidden(1);
            ui->pauseButton->setHidden(1);
#endif
            ui->actionStopCal->setVisible(1);
            ui->actionStart->setVisible(0);
            ui->actionPause->setVisible(0);
        }

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
        updateAll(0);
        if (cancelValue == 1)
            ui->statusBar->showMessage(tr("Calibration aborted"), 5000);
        else
            ui->statusBar->showMessage(tr("Calibration done!"), 5000);
    }
}

