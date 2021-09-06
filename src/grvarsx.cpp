
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Gr VarsX **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions related to X Variables
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/comhw.h"


///////////////////////////
//////// CHECK BOX ////////
///////////////////////////


void MainWindow::on_invertPosXCheckBox_toggled(bool checked)
{
    int tempVar = kbDev.checkFeedback(Check_InvertVarsX);
    if (checked)
        tempVar |= VarInvert_PosX;
    else
        tempVar &= ~VarInvert_PosX;
    kbDev.sendCom(MIDI_INVERTVARSX + (char)tempVar);
    if (kbDev.checkFeedback(Check_InvertVarsX) != tempVar)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_InvertPosX);
}

void MainWindow::on_invertWidthXCheckBox_toggled(bool checked)
{
    int tempVar = kbDev.checkFeedback(Check_InvertVarsX);
    if (checked)
        tempVar |= VarInvert_WidthX;
    else
        tempVar &= ~VarInvert_WidthX;
    kbDev.sendCom(MIDI_INVERTVARSX + (char)tempVar);
    if (kbDev.checkFeedback(Check_InvertVarsX) != tempVar)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_InvertWidthX);
}

void MainWindow::on_invertGlideXCheckBox_toggled(bool checked)
{
    int tempVar = kbDev.checkFeedback(Check_InvertVarsX);
    if (checked)
        tempVar |= VarInvert_GlideX;
    else
        tempVar &= ~VarInvert_GlideX;
    kbDev.sendCom(MIDI_INVERTVARSX + (char)tempVar);
    if (kbDev.checkFeedback(Check_InvertVarsX) != tempVar)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_InvertGlideX);
}


///////////////////////////
///////// SPIN BOX ////////
///////////////////////////


void MainWindow::on_minPosXSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->minPosXSpinBox->value() != minPosXSave)
    {
        minPosXSave = ui->minPosXSpinBox->value();
        kbDev.sendCom(MIDI_MINPOSX + (char)(ui->minPosXSpinBox->value()));
        int result = kbDev.checkFeedback(Check_MinPosX);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_MinPosXSpinBox);
        else
        {
            ui->minPosXSpinBox->setValue(result);
        }
    }
}


void MainWindow::on_maxPosXSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->maxPosXSpinBox->value() != minPosXSave)
    {
        maxPosXSave = ui->maxPosXSpinBox->value();
        kbDev.sendCom(MIDI_MAXPOSX + (char)(ui->maxPosXSpinBox->value()));
        int result = kbDev.checkFeedback(Check_MaxPosX);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_MaxPosXSpinBox);
        else
        {
            ui->maxPosXSpinBox->setValue(result);
        }
    }
}


void MainWindow::on_minWidthXSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->minWidthXSpinBox->value() != minPosXSave)
    {
        minWidthXSave = ui->minWidthXSpinBox->value();
        kbDev.sendCom(MIDI_MINWIDTHX + (char)(ui->minWidthXSpinBox->value()));
        int result = kbDev.checkFeedback(Check_MinWidthX);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_MinWidthXSpinBox);
        else
        {
            ui->minWidthXSpinBox->setValue(result);
        }
    }
}


void MainWindow::on_maxWidthXSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->maxWidthXSpinBox->value() != minPosXSave)
    {
        maxWidthXSave = ui->maxWidthXSpinBox->value();
        kbDev.sendCom(MIDI_MAXWIDTHX + (char)(ui->maxWidthXSpinBox->value()));
        int result = kbDev.checkFeedback(Check_MaxWidthX);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_MaxWidthXSpinBox);
        else
        {
            ui->maxWidthXSpinBox->setValue(result);
        }
    }
}


void MainWindow::on_minGlideXSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->minGlideXSpinBox->value() != minPosXSave)
    {
        minGlideXSave = ui->minGlideXSpinBox->value();
        kbDev.sendCom(MIDI_MINGLIDEX + (char)(ui->minGlideXSpinBox->value()));
        int result = kbDev.checkFeedback(Check_MinGlideX);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_MinGlideXSpinBox);
        else
        {
            ui->minGlideXSpinBox->setValue(result);
        }
    }
}


void MainWindow::on_maxGlideXSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    if (ui->maxGlideXSpinBox->value() != minPosXSave)
    {
        maxGlideXSave = ui->maxGlideXSpinBox->value();
        kbDev.sendCom(MIDI_MAXGLIDEX + (char)(ui->maxGlideXSpinBox->value()));
        int result = kbDev.checkFeedback(Check_MaxGlideX);
        if (result < 0)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_MaxGlideXSpinBox);
        else
        {
            ui->maxGlideXSpinBox->setValue(result);
        }
    }
}

/*
 * ====================
 * Glide Stab Spin Box
 * ====================
 */
void MainWindow::on_stabGlideSpinBox_editingFinished()
{
    if (!kbDev.isConnected())
        return;
    ui->stabGlideSlider->setValue(ui->stabGlideSpinBox->value());
}


/////////////////////////////////////
////////////// SLIDER ///////////////
/////////////////////////////////////

/*
 * ==================
 * Glide Stab Slider
 * ==================
 */
void MainWindow::on_stabGlideSlider_valueChanged(int value)
{
    kbDev.sendCom(MIDI_GLIDESTAB + (char)(value));
    int result = kbDev.checkFeedback(Check_GlideStab);
    if (result < 0)
        SendError(this, tr("No Feedback / Error on Feedback received."), GrVarsX_GlideStabSlider);
    else
    {
        ui->stabGlideSpinBox->setValue(result);
        ui->stabGlideSlider->setValue(result);
    }
}

