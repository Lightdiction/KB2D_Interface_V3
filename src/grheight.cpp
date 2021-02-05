
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
    if (ui->smoothZSlider->value() != ui->smoothZSpinBox->value())
    {
        ui->smoothZSlider->setValue(ui->smoothZSpinBox->value());
        kbDev.sendCom(MIDI_SMOOTHZ + (char)(127 - ui->smoothZSpinBox->value()));
        if (kbDev.checkFeedback(Check_SmoothZ) != (127 - ui->smoothZSpinBox->value()))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrHeight_SmoothZ_C);
    }
}

void MainWindow::on_filterZSpinBox_editingFinished()
{
    if (ui->filterZSlider->value() != ui->filterZSpinBox->value())
    {
        ui->filterZSlider->setValue(ui->filterZSpinBox->value());
        kbDev.sendCom(MIDI_FILTZ + (char)ui->filterZSpinBox->value());
        if (kbDev.checkFeedback(Check_FiltZ) != ui->filterZSpinBox->value())
            SendError(this, tr("No Feedback / incorrect feedback received."), GrHeight_FilterZ_C);
    }
}

void MainWindow::on_ampZSpinBox_editingFinished()
{
    if (ui->ampZSlider->value() != ui->ampZSpinBox->value())
    {
        ui->ampZSlider->setValue(ui->ampZSpinBox->value());
        kbDev.sendCom(MIDI_AMPZ + (char)(128 - ui->ampZSpinBox->value()));
        if (kbDev.checkFeedback(Check_AmpZ) != (128 - ui->ampZSpinBox->value()))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrHeight_AmpZ_C);
    }
}

void MainWindow::on_stabZSpinBox_editingFinished()
{
    if (ui->stabZSlider->value() != ui->stabZSpinBox->value())
    {
        ui->stabZSlider->setValue(ui->stabZSpinBox->value());
        kbDev.sendCom(MIDI_STABZ + (char)ui->stabZSpinBox->value());
        if (kbDev.checkFeedback(Check_StabZ) != ui->stabZSpinBox->value())
            SendError(this, tr("No Feedback / incorrect feedback received."), GrHeight_StabZ_C);
    }
}


/////////////////////////////////////
////////////// SLIDER ///////////////
/////////////////////////////////////


void MainWindow::on_smoothZSlider_sliderReleased()
{
    if (ui->smoothZSlider->value() != ui->smoothZSpinBox->value())
    {
        ui->smoothZSpinBox->setValue(ui->smoothZSlider->value());
        kbDev.sendCom(MIDI_SMOOTHZ + (char)(127 - ui->smoothZSpinBox->value()));
        if (kbDev.checkFeedback(Check_SmoothZ) != (127 - ui->smoothZSpinBox->value()))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrHeight_SmoothZSlider_C);
    }
}

void MainWindow::on_filterZSlider_sliderReleased()
{
    if (ui->filterZSlider->value() != ui->filterZSpinBox->value())
    {
        ui->filterZSpinBox->setValue(ui->filterZSlider->value());
        kbDev.sendCom(MIDI_FILTZ + (char)ui->filterZSpinBox->value());
        if (kbDev.checkFeedback(Check_FiltZ) != ui->filterZSpinBox->value())
            SendError(this, tr("No Feedback / incorrect feedback received."), GrHeight_FilterZSlider_C);
    }
}

void MainWindow::on_ampZSlider_sliderReleased()
{
    if (ui->ampZSlider->value() != ui->ampZSpinBox->value())
    {
        ui->ampZSpinBox->setValue(ui->ampZSlider->value());
        kbDev.sendCom(MIDI_AMPZ + (char)(128 - ui->ampZSpinBox->value()));
        if (kbDev.checkFeedback(Check_AmpZ) != (128 - ui->ampZSpinBox->value()))
            SendError(this, tr("No Feedback / incorrect feedback received."), GrHeight_AmpZSlider_C);
    }
}

void MainWindow::on_stabZSlider_sliderReleased()
{
    if (ui->stabZSlider->value() != ui->stabZSpinBox->value())
    {
        ui->stabZSpinBox->setValue(ui->stabZSlider->value());
        kbDev.sendCom(MIDI_STABZ + (char)ui->stabZSpinBox->value());
        if (kbDev.checkFeedback(Check_StabZ) != ui->stabZSpinBox->value())
            SendError(this, tr("No Feedback / incorrect feedback received."), GrHeight_StabZSlider_C);
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

