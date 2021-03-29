
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Gr Height **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions related to the Height Mode
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/comhw.h"


///////////////////////////
///////// SPIN BOX ////////
///////////////////////////


void MainWindow::on_smoothZSpinBox_editingFinished()
{
    ui->smoothZSlider->setValue(ui->smoothZSpinBox->value());
}

void MainWindow::on_filterZSpinBox_editingFinished()
{
    ui->filterZSlider->setValue(ui->filterZSpinBox->value());
}

void MainWindow::on_ampZSpinBox_editingFinished()
{
    ui->ampZSlider->setValue(ui->ampZSpinBox->value());
}

void MainWindow::on_stabZSpinBox_editingFinished()
{
    ui->stabZSlider->setValue(ui->stabZSpinBox->value());
}


/////////////////////////////////////
////////////// SLIDER ///////////////
/////////////////////////////////////


void MainWindow::on_smoothZSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_SMOOTHZ + (char)(127 - value));
    int result = kbDev.checkFeedback(Check_SmoothZ);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_SmoothZSlider_C);
    else
    {
        ui->smoothZSpinBox->setValue(127 - result);
        ui->smoothZSlider->setValue(127 - result);
    }
}

void MainWindow::on_filterZSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_FILTZ + (char)(value));
    int result = kbDev.checkFeedback(Check_FiltZ);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_FilterZSlider_C);
    else
    {
        ui->filterZSpinBox->setValue(result);
        ui->filterZSlider->setValue(result);
    }
}

void MainWindow::on_ampZSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_AMPZ + (char)(128 - value));
    int result = kbDev.checkFeedback(Check_AmpZ);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_AmpZSlider_C);
    else
    {
        ui->ampZSpinBox->setValue(128 - result);
        ui->ampZSlider->setValue(128 - result);
    }
}

void MainWindow::on_stabZSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_STABZ + (char)(value));
    int result = kbDev.checkFeedback(Check_StabZ);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_StabZSlider_C);
    else
    {
        ui->stabZSpinBox->setValue(result);
        ui->stabZSlider->setValue(result);
    }
}


/////////////////////////////////////
///////////// COMBO BOX /////////////
/////////////////////////////////////

/*
 * ============================================
 * Z modulation Combo Box
 * ============================================
 */
void MainWindow::on_modulationZComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        kbDev.sendCom(MIDI_RELATIVEH + (char)1);
        if (kbDev.checkFeedback(Check_RelativeH) != 1)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_ModulationZ_1_C);

        ui->nbAbsoluteLabel->setVisible(0);
    }
    else
    {
        kbDev.sendCom(MIDI_RELATIVEH + (char)0);
        if (kbDev.checkFeedback(Check_RelativeH) != 0)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_ModulationZ_2_C);

        ui->nbAbsoluteLabel->setVisible(1);
    }
}

void MainWindow::on_nStepsZComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_NBEAMSZ + (char)(index + 1));
}


/////////////////////////////////////
///////////// CHECK BOX /////////////
/////////////////////////////////////

void MainWindow::on_invertZCheckBox_toggled(bool checked)
{
    if (checked)
    {
        kbDev.sendCom(MIDI_INVERTZ + (char)1);
        if (kbDev.checkFeedback(Check_InvertZ) != 1)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_InvertZ_1_C);
    }
    else
    {
        kbDev.sendCom(MIDI_INVERTZ + (char)0);
        if (kbDev.checkFeedback(Check_InvertZ) != 0)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_InvertZ_2_C);
    }
}

