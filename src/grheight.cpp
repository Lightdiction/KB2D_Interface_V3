
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


void MainWindow::on_minHeightSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->minHeightSpinBox->value() != minZSave)
    {
        minZSave = ui->minHeightSpinBox->value();
        kbDev.sendCom(MIDI_MINZ + (char)(ui->minHeightSpinBox->value()));
        int result = kbDev.checkFeedback(Check_MinZ);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrHeight_MinZSpinBox);
        else
            ui->minHeightSpinBox->setValue(result);
    }
}
void MainWindow::on_centerHeightSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->centerHeightSpinBox->value() != centerZSave)
    {
        centerZSave = ui->centerHeightSpinBox->value();
        kbDev.sendCom(MIDI_CENTERZ + (char)(ui->centerHeightSpinBox->value()));
        int result = kbDev.checkFeedback(Check_CenterZ);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrHeight_CenterZSpinBox);
        else
            ui->centerHeightSpinBox->setValue(result);
    }
}

void MainWindow::on_maxHeightSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->maxHeightSpinBox->value() != maxZSave)
    {
        maxZSave = ui->maxHeightSpinBox->value();
        kbDev.sendCom(MIDI_MAXZ + (char)(ui->maxHeightSpinBox->value()));
        int result = kbDev.checkFeedback(Check_MaxZ);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrHeight_MaxZSpinBox);
        else
            ui->maxHeightSpinBox->setValue(result);
    }
}

void MainWindow::on_subHeightSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->subHeightSpinBox->value() != subZSave)
    {
        subZSave = ui->subHeightSpinBox->value();
        kbDev.sendCom(MIDI_SUBHEIGHT + (char)(ui->subHeightSpinBox->value()));
        int result = kbDev.checkFeedback(Check_SubHeight);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrHeight_SubZSpinBox);
        else
            ui->subHeightSpinBox->setValue(result);
    }
}

void MainWindow::on_smoothZSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->smoothZSlider->setValue(ui->smoothZSpinBox->value());
}

void MainWindow::on_filterZSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->filterZSlider->setValue(ui->filterZSpinBox->value());
}

void MainWindow::on_ampZSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->ampZSlider->setValue(ui->ampZSpinBox->value());
}

void MainWindow::on_stabZSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->stabZSlider->setValue(ui->stabZSpinBox->value());
}


/////////////////////////////////////
////////////// SLIDER ///////////////
/////////////////////////////////////


void MainWindow::on_smoothZSlider_valueChanged(int value)
{
    if ((kbDev.getID(VERSION) > 8) || ((kbDev.getID(VERSION) == 8) && (kbDev.getID(SUBVERSION) >= 3)))
    {
        kbDev.sendCom(MIDI_SMOOTHZ + (char)(qPow(MAX_SMOOTH803 - value + 1, POW_SMOOTHZ)));
        int result = kbDev.checkFeedback(Check_SmoothZ);
        if (result < 0)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_SmoothZSlider);
        else
        {
            ui->smoothZSpinBox->setValue(MAX_SMOOTH803 - qPow(result, 1 / POW_SMOOTHZ) + 1);
            ui->smoothZSlider->setValue(MAX_SMOOTH803 - qPow(result, 1 / POW_SMOOTHZ) + 1);
        }
    }
    else
    {
        kbDev.sendCom(MIDI_SMOOTHZ + (char)(MAX_SMOOTH - value));
        int result = kbDev.checkFeedback(Check_SmoothZ);
        if (result < 0)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_SmoothZSlider);
        else
        {
            ui->smoothZSpinBox->setValue(MAX_SMOOTH - result);
            ui->smoothZSlider->setValue(MAX_SMOOTH - result);
        }
    }
}

void MainWindow::on_filterZSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_FILTZ + (char)(value));
    int result = kbDev.checkFeedback(Check_FiltZ);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_FilterZSlider);
    else
    {
        ui->filterZSpinBox->setValue(result);
        ui->filterZSlider->setValue(result);
    }
}

void MainWindow::on_ampZSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_AMPZ + (char)(MAX_AMP - value));
    int result = kbDev.checkFeedback(Check_AmpZ);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_AmpZSlider);
    else
    {
        ui->ampZSpinBox->setValue(MAX_AMP - result);
        ui->ampZSlider->setValue(MAX_AMP - result);
    }
}

void MainWindow::on_stabZSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_STABZ + (char)(value));
    int result = kbDev.checkFeedback(Check_StabZ);
    if (result < 0)
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_StabZSlider);
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
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_ModulationZ_1);

        ui->nbAbsoluteLabel->setVisible(0);
    }
    else
    {
        kbDev.sendCom(MIDI_RELATIVEH + (char)0);
        if (kbDev.checkFeedback(Check_RelativeH) != 0)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_ModulationZ_2);

        ui->nbAbsoluteLabel->setVisible(1);
    }
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
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_InvertZ_1);
    }
    else
    {
        kbDev.sendCom(MIDI_INVERTZ + (char)0);
        if (kbDev.checkFeedback(Check_InvertZ) != 0)
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrHeight_InvertZ_2);
    }
}

