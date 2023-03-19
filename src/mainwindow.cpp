/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Main Window **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All Main functions regarding:
 * - UI
 * - MIDI Callbacks
 * - Generic Buttons
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/versiondialog.h"

#include "QStyle"
#include "QStyleFactory"

//#include "comhw.h"

//#define Z_DIMENSION

//int mappingCommand[NUM_EXTERNAL_COMMANDS][3] = {{-1}};

//unsigned long timeRec = 0;

bool configDone = false;
bool testMode = false;

bool cancelValue = false;

QString saveNameMidi;
QString saveNameMidiIn;
int saveIndexMidiOut = 0;
int saveIndexMidiIn = 0;

int extMidiIndexToLearn;

#ifdef MAC_PLATFORM
int macOSVersion = 0;
#endif


/*
 * ========================
 * Custom Resize event
 * ========================
 *//*
void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    //
}*/

/*
 * =============================================
 * Event Filter for Wheel events
 * Spin Box, Double Spin Box, Slider, Combo Box
 * =============================================
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Wheel)
    {
        QSpinBox* spin = qobject_cast<QSpinBox*>(obj);
        if(spin && !spin->hasFocus())
        {
            event->ignore();
            return true;
        }
        QDoubleSpinBox* dSpin = qobject_cast<QDoubleSpinBox*>(obj);
        if(dSpin && !dSpin->hasFocus())
        {
            event->ignore();
            return true;
        }
        QSlider* slider = qobject_cast<QSlider*>(obj);
        if(slider && !slider->hasFocus())
        {
            event->ignore();
            return true;
        }
        QComboBox* combo = qobject_cast<QComboBox*>(obj);
        if(combo && !combo->hasFocus())
        {
            event->ignore();
            return true;
        }
    }

    event->accept();
    return false;
}

/*
 * ======================================
 * All ports are initialized in main.cpp
 * Just after this MainWindow is created
 * ======================================
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //qDebug() << QStyleFactory::keys();
    QApplication::setStyle("windowsvista");

    //qDebug() << QSysInfo::kernelType() << QSysInfo::kernelVersion();

    SendLog("\n===================== Starting... " + QSysInfo::kernelType() + " " + QSysInfo::kernelVersion());
#ifdef MAC_PLATFORM
    macOSVersion = QSysInfo::kernelVersion().split(".").at(0).toInt() - 9;
    qDebug() << "Mac OS Version found: " << macOSVersion;
#endif

    /////// Filter for Wheel Events ///////
    QList <QSpinBox *> listSpin = this->findChildren<QSpinBox *>();
    foreach (QSpinBox *qs, listSpin)
    {
        qs->setFocusPolicy(Qt::StrongFocus);
        qs->installEventFilter(this);
    }

    QList <QDoubleSpinBox *> listDSpin = this->findChildren<QDoubleSpinBox *>();
    foreach (QDoubleSpinBox *qs, listDSpin)
    {
        qs->setFocusPolicy(Qt::StrongFocus);
        qs->installEventFilter(this);
    }

    QList <QSlider *> listSlider = this->findChildren<QSlider *>();
    foreach (QSlider *qs, listSlider)
    {
        qs->setFocusPolicy(Qt::StrongFocus);
        qs->installEventFilter(this);
    }

    QList <QComboBox *> listCombo = this->findChildren<QComboBox *>();
    foreach (QComboBox *qs, listCombo)
    {
        qs->setFocusPolicy(Qt::StrongFocus);
        qs->installEventFilter(this);
    }
    ///////

    updateInProgress = true;
    for (int _i = 0 ; _i < Note_Number ; _i ++)
    {
        ui->startKeyComboBox->addItem(ListNameNotes[_i]);
        ui->startKeyComboBox_2->addItem(ListNameNotes[_i]);
        ui->startKeyComboBox_3->addItem(ListNameNotes[_i]);
    }
    QApplication::processEvents();
    updateInProgress = false;

    extMidiIndexToLearn = -1;

    ui->statusBar->addPermanentWidget(ui->statusLabel, 0);

    // List all Tabs once, before we remove some of these.
    for (int _i = 0; _i < Tab_NumTabs; _i++)
        listNameTabs[_i] = ui->tabWidget->tabText(_i);

    groupList[Group_KB2DPorts] = ui->kb2dPortsGroup;
    groupList[Group_MainPresets] = ui->presetsGroup;
    groupList[Group_AnglesParam] = ui->anglesParamGroup;
    groupList[Group_AngleDetails] = ui->anglesWidget;
    groupList[Group_GlobalMidiAngle] = ui->globalMidiAngleWidget;
    groupList[Group_MidiTab] = ui->midiTabWidget;

    groupList[Group_Assign] = ui->assignGroup;
    groupList[Group_NotesSetWidget] = ui->notesSetWidget;
    groupList[Group_Enable] = ui->enableGroup;
    groupList[Group_AllMidi] = ui->midiAllWidget;
    groupList[Group_NotesMidi] = ui->notesMidiWidget;
    groupList[Group_CC1Midi] = ui->CC1MidiWidget;
    groupList[Group_CC2Midi] = ui->CC2MidiWidget;
    groupList[Group_NotesParam] = ui->notesParamGroup;
    groupList[Group_KeyboardSetWidget] = ui->keyboardSetWidget;
    groupList[Group_NotesScroll] = ui->notesScrollArea;
    groupList[Group_Effect0] = ui->effect01GroupBox;
    groupList[Group_Effect1] = ui->effect11GroupBox;
    groupList[Group_Effect2] = ui->effect21GroupBox;

    groupList[Group_MainWidget] = ui->mainSettingsWidget;
    groupList[Group_DetXParam] = ui->detectionGroup;
    groupList[Group_PosXParam] = ui->posXGroup;
    groupList[Group_DetZParam] = ui->heightGroup;

    groupList[Group_Assign_2] = ui->assignGroup_2;
    groupList[Group_NotesSetWidget_2] = ui->notesSetWidget_2;
    groupList[Group_Enable_2] = ui->enableGroup_2;
    groupList[Group_AllMidi_2] = ui->midiAllWidget_2;
    groupList[Group_NotesMidi_2] = ui->notesMidiWidget_2;
    groupList[Group_CC1Midi_2] = ui->CC1MidiWidget_2;
    groupList[Group_CC2Midi_2] = ui->CC2MidiWidget_2;
    groupList[Group_NotesParam_2] = ui->notesParamGroup_2;
    groupList[Group_KeyboardSetWidget_2] = ui->keyboardSetWidget_2;
    groupList[Group_NotesScroll_2] = ui->notesScrollArea_2;
    groupList[Group_Effect0_2] = ui->effect02GroupBox;
    groupList[Group_Effect1_2] = ui->effect12GroupBox;
    groupList[Group_Effect2_2] = ui->effect22GroupBox;

    groupList[Group_Assign_3] = ui->assignGroup_3;
    groupList[Group_NotesSetWidget_3] = ui->notesSetWidget_3;
    groupList[Group_Enable_3] = ui->enableGroup_3;
    groupList[Group_AllMidi_3] = ui->midiAllWidget_3;
    groupList[Group_NotesMidi_3] = ui->notesMidiWidget_3;
    groupList[Group_CC1Midi_3] = ui->CC1MidiWidget_3;
    groupList[Group_CC2Midi_3] = ui->CC2MidiWidget_3;
    groupList[Group_NotesParam_3] = ui->notesParamGroup_3;
    groupList[Group_KeyboardSetWidget_3] = ui->keyboardSetWidget_3;
    groupList[Group_NotesScroll_3] = ui->notesScrollArea_3;
    groupList[Group_Effect0_3] = ui->effect03GroupBox;
    groupList[Group_Effect1_3] = ui->effect13GroupBox;
    groupList[Group_Effect2_3] = ui->effect23GroupBox;

    qDebug() << "Reset Ports";
    resetMidiPorts();

    qDebug() << "Set Angle Learn";
    ///// Angle Learn /////
    angleLearn[0] = ui->learn_1;
    angleLearn[1] = ui->learn_2;
    angleLearn[2] = ui->learn_3;
    angleLearn[3] = ui->learn_4;
    angleLearn[4] = ui->learn_5;
    angleLearn[5] = ui->learn_6;
    angleLearn[6] = ui->learn_7;
    angleLearn[7] = ui->learn_8;
    angleLearn[8] = ui->learn_9;
    angleLearn[9] = ui->learn_10;
    angleLearn[10] = ui->learn_11;
    angleLearn[11] = ui->learn_12;
    angleLearn[12] = ui->learn_13;
    angleLearn[13] = ui->learn_14;
    angleLearn[14] = ui->learn_15;
    angleLearn[15] = ui->learn_16;

    for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
        connect(angleLearn[_i], &QPushButton::clicked, this, [this, _i] () {this->learnOneAngle(_i);});

    qDebug() << "Set Angle SpinBox";
    ///// Angle Spin Box /////
    angleDoubleSpinBox[0] = ui->angleDoubleSpinBox_1;
    angleDoubleSpinBox[1] = ui->angleDoubleSpinBox_2;
    angleDoubleSpinBox[2] = ui->angleDoubleSpinBox_3;
    angleDoubleSpinBox[3] = ui->angleDoubleSpinBox_4;
    angleDoubleSpinBox[4] = ui->angleDoubleSpinBox_5;
    angleDoubleSpinBox[5] = ui->angleDoubleSpinBox_6;
    angleDoubleSpinBox[6] = ui->angleDoubleSpinBox_7;
    angleDoubleSpinBox[7] = ui->angleDoubleSpinBox_8;
    angleDoubleSpinBox[8] = ui->angleDoubleSpinBox_9;
    angleDoubleSpinBox[9] = ui->angleDoubleSpinBox_10;
    angleDoubleSpinBox[10] = ui->angleDoubleSpinBox_11;
    angleDoubleSpinBox[11] = ui->angleDoubleSpinBox_12;
    angleDoubleSpinBox[12] = ui->angleDoubleSpinBox_13;
    angleDoubleSpinBox[13] = ui->angleDoubleSpinBox_14;
    angleDoubleSpinBox[14] = ui->angleDoubleSpinBox_15;
    angleDoubleSpinBox[15] = ui->angleDoubleSpinBox_16;

    for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
    {
        if (angleDoubleSpinBox[_i])
            connect(angleDoubleSpinBox[_i], &QDoubleSpinBox::editingFinished, this, [this, _i] () {this->multiAngleSpinBox_editing(_i);});
    }

    // PORT 1 2 3
    ///// Assign Button /////
    assignAllButton[Ports_Midi1] = ui->assignAllButton;
    assignAllButton[Ports_Midi3] = ui->assignAllButton_2;
    assignAllButton[Ports_Midi4] = ui->assignAllButton_3;

    assignButton[Ports_Midi1][0] = ui->assign1Button;
    assignButton[Ports_Midi1][1] = ui->assign2Button;
    assignButton[Ports_Midi1][2] = ui->assign3Button;
    assignButton[Ports_Midi1][3] = ui->assign4Button;
    assignButton[Ports_Midi1][4] = ui->assign5Button;
    assignButton[Ports_Midi1][5] = ui->assign6Button;
    assignButton[Ports_Midi1][6] = ui->assign7Button;
    assignButton[Ports_Midi1][7] = ui->assign8Button;
    assignButton[Ports_Midi1][8] = ui->assign9Button;
    assignButton[Ports_Midi1][9] = ui->assign10Button;
    assignButton[Ports_Midi1][10] = ui->assign11Button;
    assignButton[Ports_Midi1][11] = ui->assign12Button;
    assignButton[Ports_Midi1][12] = ui->assign13Button;
    assignButton[Ports_Midi1][13] = ui->assign14Button;
    assignButton[Ports_Midi1][14] = ui->assign15Button;
    assignButton[Ports_Midi1][15] = ui->assign16Button;

    assignButton[Ports_Midi3][0] = ui->assign1Button_2;
    assignButton[Ports_Midi3][1] = ui->assign2Button_2;
    assignButton[Ports_Midi3][2] = ui->assign3Button_2;
    assignButton[Ports_Midi3][3] = ui->assign4Button_2;
    assignButton[Ports_Midi3][4] = ui->assign5Button_2;
    assignButton[Ports_Midi3][5] = ui->assign6Button_2;
    assignButton[Ports_Midi3][6] = ui->assign7Button_2;
    assignButton[Ports_Midi3][7] = ui->assign8Button_2;
    assignButton[Ports_Midi3][8] = ui->assign9Button_2;
    assignButton[Ports_Midi3][9] = ui->assign10Button_2;
    assignButton[Ports_Midi3][10] = ui->assign11Button_2;
    assignButton[Ports_Midi3][11] = ui->assign12Button_2;
    assignButton[Ports_Midi3][12] = ui->assign13Button_2;
    assignButton[Ports_Midi3][13] = ui->assign14Button_2;
    assignButton[Ports_Midi3][14] = ui->assign15Button_2;
    assignButton[Ports_Midi3][15] = ui->assign16Button_2;

    assignButton[Ports_Midi4][0] = ui->assign1Button_3;
    assignButton[Ports_Midi4][1] = ui->assign2Button_3;
    assignButton[Ports_Midi4][2] = ui->assign3Button_3;
    assignButton[Ports_Midi4][3] = ui->assign4Button_3;
    assignButton[Ports_Midi4][4] = ui->assign5Button_3;
    assignButton[Ports_Midi4][5] = ui->assign6Button_3;
    assignButton[Ports_Midi4][6] = ui->assign7Button_3;
    assignButton[Ports_Midi4][7] = ui->assign8Button_3;
    assignButton[Ports_Midi4][8] = ui->assign9Button_3;
    assignButton[Ports_Midi4][9] = ui->assign10Button_3;
    assignButton[Ports_Midi4][10] = ui->assign11Button_3;
    assignButton[Ports_Midi4][11] = ui->assign12Button_3;
    assignButton[Ports_Midi4][12] = ui->assign13Button_3;
    assignButton[Ports_Midi4][13] = ui->assign14Button_3;
    assignButton[Ports_Midi4][14] = ui->assign15Button_3;
    assignButton[Ports_Midi4][15] = ui->assign16Button_3;

    repaintAssignButtons();

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        if (assignAllButton[_i])
            connect(assignAllButton[_i], &QPushButton::clicked, this, [this, _i] () {this->assignAllButtonClicked(_i);});
    }

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0 ; _j < MAX_NBEAMS ; _j++)
        {
            if (assignButton[_i][_j])
                connect(assignButton[_i][_j], &QPushButton::clicked, this, [this, _i, _j] () {this->assignButtonClicked(_i, _j);});
        }
    }

    ///// Tone Shift /////
    toneShiftButton[Ports_Midi1][ToneShift_PlusHalfTone] = ui->plusHtButton;
    toneShiftButton[Ports_Midi1][ToneShift_MinusHalfTone] = ui->minusHtButton;
    toneShiftButton[Ports_Midi1][ToneShift_PlusTone] = ui->plusToneButton;
    toneShiftButton[Ports_Midi1][ToneShift_MinusTone] = ui->minusToneButton;

    toneShiftButton[Ports_Midi3][ToneShift_PlusHalfTone] = ui->plusHtButton_2;
    toneShiftButton[Ports_Midi3][ToneShift_MinusHalfTone] = ui->minusHtButton_2;
    toneShiftButton[Ports_Midi3][ToneShift_PlusTone] = ui->plusToneButton_2;
    toneShiftButton[Ports_Midi3][ToneShift_MinusTone] = ui->minusToneButton_2;

    toneShiftButton[Ports_Midi4][ToneShift_PlusHalfTone] = ui->plusHtButton_3;
    toneShiftButton[Ports_Midi4][ToneShift_MinusHalfTone] = ui->minusHtButton_3;
    toneShiftButton[Ports_Midi4][ToneShift_PlusTone] = ui->plusToneButton_3;
    toneShiftButton[Ports_Midi4][ToneShift_MinusTone] = ui->minusToneButton_3;

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0 ; _j < ToneShift_NumTotal ; _j++)
        {
            if (toneShiftButton[_i][_j])
                connect(toneShiftButton[_i][_j], &QPushButton::clicked, this, [this, _i, _j] () {this->toneShiftClicked(_i, _j);});
        }
    }

    ///// Note Presets /////
    notePresetButton[Ports_Midi1][NotePreset_User1] = ui->user1Button;
    notePresetButton[Ports_Midi1][NotePreset_User2] = ui->user2Button;
    notePresetButton[Ports_Midi1][NotePreset_User3] = ui->user3Button;

    notePresetButton[Ports_Midi3][NotePreset_User1] = ui->user1Button_2;
    notePresetButton[Ports_Midi3][NotePreset_User2] = ui->user2Button_2;
    notePresetButton[Ports_Midi3][NotePreset_User3] = ui->user3Button_2;

    notePresetButton[Ports_Midi4][NotePreset_User1] = ui->user1Button_3;
    notePresetButton[Ports_Midi4][NotePreset_User2] = ui->user2Button_3;
    notePresetButton[Ports_Midi4][NotePreset_User3] = ui->user3Button_3;

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0 ; _j < NotePreset_NumTotal ; _j++)
        {
            if (notePresetButton[_i][_j])
                connect(notePresetButton[_i][_j], &QPushButton::clicked, this, [this, _i, _j] () {this->notePresetClicked(_i, _j);});
        }
    }

    saveNotesDialogButton[Ports_Midi1] = ui->saveNotesPresetButton;
    saveNotesDialogButton[Ports_Midi3] = ui->saveNotesPresetButton_2;
    saveNotesDialogButton[Ports_Midi4] = ui->saveNotesPresetButton_3;

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        connect(saveNotesDialogButton[_i], &QPushButton::clicked, this, [this, _i] () { this->saveNotesDialogClicked(_i); });
    }

    manageNotesDialogButton[Ports_Midi1] = ui->mngNotesPresetButton;
    manageNotesDialogButton[Ports_Midi3] = ui->mngNotesPresetButton_2;
    manageNotesDialogButton[Ports_Midi4] = ui->mngNotesPresetButton_3;

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        connect(manageNotesDialogButton[_i], &QPushButton::clicked, this, [this, _i] () { this->manageNotesDialogClicked(_i); });
    }

    notesPresetCombos[Ports_Midi1] = ui->notesPresetCombo;
    notesPresetCombos[Ports_Midi3] = ui->notesPresetCombo_2;
    notesPresetCombos[Ports_Midi4] = ui->notesPresetCombo_3;

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        connect(notesPresetCombos[_i], &QComboBox::currentIndexChanged, this, [this, _i] (int ind) { this->notesPresetComboChanged(_i,ind); });
    }

    updateNotesPresetList();

    ///// Beam Activation /////
    enableButton[Ports_Midi1][0] = ui->enable1Button;
    enableButton[Ports_Midi1][1] = ui->enable2Button;
    enableButton[Ports_Midi1][2] = ui->enable3Button;
    enableButton[Ports_Midi1][3] = ui->enable4Button;
    enableButton[Ports_Midi1][4] = ui->enable5Button;
    enableButton[Ports_Midi1][5] = ui->enable6Button;
    enableButton[Ports_Midi1][6] = ui->enable7Button;
    enableButton[Ports_Midi1][7] = ui->enable8Button;
    enableButton[Ports_Midi1][8] = ui->enable9Button;
    enableButton[Ports_Midi1][9] = ui->enable10Button;
    enableButton[Ports_Midi1][10] = ui->enable11Button;
    enableButton[Ports_Midi1][11] = ui->enable12Button;
    enableButton[Ports_Midi1][12] = ui->enable13Button;
    enableButton[Ports_Midi1][13] = ui->enable14Button;
    enableButton[Ports_Midi1][14] = ui->enable15Button;
    enableButton[Ports_Midi1][15] = ui->enable16Button;

    enableButton[Ports_Midi3][0] = ui->enable1Button_2;
    enableButton[Ports_Midi3][1] = ui->enable2Button_2;
    enableButton[Ports_Midi3][2] = ui->enable3Button_2;
    enableButton[Ports_Midi3][3] = ui->enable4Button_2;
    enableButton[Ports_Midi3][4] = ui->enable5Button_2;
    enableButton[Ports_Midi3][5] = ui->enable6Button_2;
    enableButton[Ports_Midi3][6] = ui->enable7Button_2;
    enableButton[Ports_Midi3][7] = ui->enable8Button_2;
    enableButton[Ports_Midi3][8] = ui->enable9Button_2;
    enableButton[Ports_Midi3][9] = ui->enable10Button_2;
    enableButton[Ports_Midi3][10] = ui->enable11Button_2;
    enableButton[Ports_Midi3][11] = ui->enable12Button_2;
    enableButton[Ports_Midi3][12] = ui->enable13Button_2;
    enableButton[Ports_Midi3][13] = ui->enable14Button_2;
    enableButton[Ports_Midi3][14] = ui->enable15Button_2;
    enableButton[Ports_Midi3][15] = ui->enable16Button_2;

    enableButton[Ports_Midi4][0] = ui->enable1Button_3;
    enableButton[Ports_Midi4][1] = ui->enable2Button_3;
    enableButton[Ports_Midi4][2] = ui->enable3Button_3;
    enableButton[Ports_Midi4][3] = ui->enable4Button_3;
    enableButton[Ports_Midi4][4] = ui->enable5Button_3;
    enableButton[Ports_Midi4][5] = ui->enable6Button_3;
    enableButton[Ports_Midi4][6] = ui->enable7Button_3;
    enableButton[Ports_Midi4][7] = ui->enable8Button_3;
    enableButton[Ports_Midi4][8] = ui->enable9Button_3;
    enableButton[Ports_Midi4][9] = ui->enable10Button_3;
    enableButton[Ports_Midi4][10] = ui->enable11Button_3;
    enableButton[Ports_Midi4][11] = ui->enable12Button_3;
    enableButton[Ports_Midi4][12] = ui->enable13Button_3;
    enableButton[Ports_Midi4][13] = ui->enable14Button_3;
    enableButton[Ports_Midi4][14] = ui->enable15Button_3;
    enableButton[Ports_Midi4][15] = ui->enable16Button_3;

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0 ; _j < MAX_NBEAMS ; _j++)
        {
            if (enableButton[_i][_j])
                connect(enableButton[_i][_j], &QPushButton::clicked, this, [this, _i, _j] () {this->enableButtonClicked(_i, _j);});
        }
    }

    qDebug() << "Set MIDI Selection Combos";
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_Channel] = ui->ChanNoteComboBox;
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_CtrlNotes] = ui->NoteNoteComboBox;
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_ValVel] = ui->VelNoteComboBox;
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_Channel] = ui->ChanCC1ComboBox;
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_CtrlNotes] = ui->ControlCC1ComboBox;
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_ValVel] = ui->ValCC1ComboBox;
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_Channel] = ui->ChanCC2ComboBox;
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_CtrlNotes] = ui->ControlCC2ComboBox;
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_ValVel] = ui->ValCC2ComboBox;

    midiSelection_Combo[Ports_Midi3][ModeActiv_Notes][ValSelection_Channel] = ui->ChanNoteComboBox_2;
    midiSelection_Combo[Ports_Midi3][ModeActiv_Notes][ValSelection_CtrlNotes] = ui->NoteNoteComboBox_2;
    midiSelection_Combo[Ports_Midi3][ModeActiv_Notes][ValSelection_ValVel] = ui->VelNoteComboBox_2;
    midiSelection_Combo[Ports_Midi3][ModeActiv_Control1][ValSelection_Channel] = ui->ChanCC1ComboBox_2;
    midiSelection_Combo[Ports_Midi3][ModeActiv_Control1][ValSelection_CtrlNotes] = ui->ControlCC1ComboBox_2;
    midiSelection_Combo[Ports_Midi3][ModeActiv_Control1][ValSelection_ValVel] = ui->ValCC1ComboBox_2;
    midiSelection_Combo[Ports_Midi3][ModeActiv_Control2][ValSelection_Channel] = ui->ChanCC2ComboBox_2;
    midiSelection_Combo[Ports_Midi3][ModeActiv_Control2][ValSelection_CtrlNotes] = ui->ControlCC2ComboBox_2;
    midiSelection_Combo[Ports_Midi3][ModeActiv_Control2][ValSelection_ValVel] = ui->ValCC2ComboBox_2;

    midiSelection_Combo[Ports_Midi4][ModeActiv_Notes][ValSelection_Channel] = ui->ChanNoteComboBox_3;
    midiSelection_Combo[Ports_Midi4][ModeActiv_Notes][ValSelection_CtrlNotes] = ui->NoteNoteComboBox_3;
    midiSelection_Combo[Ports_Midi4][ModeActiv_Notes][ValSelection_ValVel] = ui->VelNoteComboBox_3;
    midiSelection_Combo[Ports_Midi4][ModeActiv_Control1][ValSelection_Channel] = ui->ChanCC1ComboBox_3;
    midiSelection_Combo[Ports_Midi4][ModeActiv_Control1][ValSelection_CtrlNotes] = ui->ControlCC1ComboBox_3;
    midiSelection_Combo[Ports_Midi4][ModeActiv_Control1][ValSelection_ValVel] = ui->ValCC1ComboBox_3;
    midiSelection_Combo[Ports_Midi4][ModeActiv_Control2][ValSelection_Channel] = ui->ChanCC2ComboBox_3;
    midiSelection_Combo[Ports_Midi4][ModeActiv_Control2][ValSelection_CtrlNotes] = ui->ControlCC2ComboBox_3;
    midiSelection_Combo[Ports_Midi4][ModeActiv_Control2][ValSelection_ValVel] = ui->ValCC2ComboBox_3;

    Z0_ComboBox[Ports_Midi1][0] = ui->X0Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][1] = ui->X1Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][2] = ui->X2Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][3] = ui->X3Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][4] = ui->X4Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][5] = ui->X5Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][6] = ui->X6Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][7] = ui->X7Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][8] = ui->X8Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][9] = ui->X9Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][10] = ui->X10Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][11] = ui->X11Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][12] = ui->X12Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][13] = ui->X13Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][14] = ui->X14Z0_ComboBox;
    Z0_ComboBox[Ports_Midi1][15] = ui->X15Z0_ComboBox;

    Z0_ComboBox[Ports_Midi3][0] = ui->X0Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][1] = ui->X1Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][2] = ui->X2Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][3] = ui->X3Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][4] = ui->X4Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][5] = ui->X5Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][6] = ui->X6Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][7] = ui->X7Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][8] = ui->X8Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][9] = ui->X9Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][10] = ui->X10Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][11] = ui->X11Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][12] = ui->X12Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][13] = ui->X13Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][14] = ui->X14Z0_ComboBox_2;
    Z0_ComboBox[Ports_Midi3][15] = ui->X15Z0_ComboBox_2;

    Z0_ComboBox[Ports_Midi4][0] = ui->X0Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][1] = ui->X1Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][2] = ui->X2Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][3] = ui->X3Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][4] = ui->X4Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][5] = ui->X5Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][6] = ui->X6Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][7] = ui->X7Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][8] = ui->X8Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][9] = ui->X9Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][10] = ui->X10Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][11] = ui->X11Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][12] = ui->X12Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][13] = ui->X13Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][14] = ui->X14Z0_ComboBox_3;
    Z0_ComboBox[Ports_Midi4][15] = ui->X15Z0_ComboBox_3;

    LabelZ0Combo[Ports_Midi1][0] = ui->X1_Label;
    LabelZ0Combo[Ports_Midi1][1] = ui->X2_Label;
    LabelZ0Combo[Ports_Midi1][2] = ui->X3_Label;
    LabelZ0Combo[Ports_Midi1][3] = ui->X4_Label;
    LabelZ0Combo[Ports_Midi1][4] = ui->X5_Label;
    LabelZ0Combo[Ports_Midi1][5] = ui->X6_Label;
    LabelZ0Combo[Ports_Midi1][6] = ui->X7_Label;
    LabelZ0Combo[Ports_Midi1][7] = ui->X8_Label;
    LabelZ0Combo[Ports_Midi1][8] = ui->X9_Label;
    LabelZ0Combo[Ports_Midi1][9] = ui->X10_Label;
    LabelZ0Combo[Ports_Midi1][10] = ui->X11_Label;
    LabelZ0Combo[Ports_Midi1][11] = ui->X12_Label;
    LabelZ0Combo[Ports_Midi1][12] = ui->X13_Label;
    LabelZ0Combo[Ports_Midi1][13] = ui->X14_Label;
    LabelZ0Combo[Ports_Midi1][14] = ui->X15_Label;
    LabelZ0Combo[Ports_Midi1][15] = ui->X16_Label;

    LabelZ0Combo[Ports_Midi3][0] = ui->X1_Label_2;
    LabelZ0Combo[Ports_Midi3][1] = ui->X2_Label_2;
    LabelZ0Combo[Ports_Midi3][2] = ui->X3_Label_2;
    LabelZ0Combo[Ports_Midi3][3] = ui->X4_Label_2;
    LabelZ0Combo[Ports_Midi3][4] = ui->X5_Label_2;
    LabelZ0Combo[Ports_Midi3][5] = ui->X6_Label_2;
    LabelZ0Combo[Ports_Midi3][6] = ui->X7_Label_2;
    LabelZ0Combo[Ports_Midi3][7] = ui->X8_Label_2;
    LabelZ0Combo[Ports_Midi3][8] = ui->X9_Label_2;
    LabelZ0Combo[Ports_Midi3][9] = ui->X10_Label_2;
    LabelZ0Combo[Ports_Midi3][10] = ui->X11_Label_2;
    LabelZ0Combo[Ports_Midi3][11] = ui->X12_Label_2;
    LabelZ0Combo[Ports_Midi3][12] = ui->X13_Label_2;
    LabelZ0Combo[Ports_Midi3][13] = ui->X14_Label_2;
    LabelZ0Combo[Ports_Midi3][14] = ui->X15_Label_2;
    LabelZ0Combo[Ports_Midi3][15] = ui->X16_Label_2;

    LabelZ0Combo[Ports_Midi4][0] = ui->X1_Label_3;
    LabelZ0Combo[Ports_Midi4][1] = ui->X2_Label_3;
    LabelZ0Combo[Ports_Midi4][2] = ui->X3_Label_3;
    LabelZ0Combo[Ports_Midi4][3] = ui->X4_Label_3;
    LabelZ0Combo[Ports_Midi4][4] = ui->X5_Label_3;
    LabelZ0Combo[Ports_Midi4][5] = ui->X6_Label_3;
    LabelZ0Combo[Ports_Midi4][6] = ui->X7_Label_3;
    LabelZ0Combo[Ports_Midi4][7] = ui->X8_Label_3;
    LabelZ0Combo[Ports_Midi4][8] = ui->X9_Label_3;
    LabelZ0Combo[Ports_Midi4][9] = ui->X10_Label_3;
    LabelZ0Combo[Ports_Midi4][10] = ui->X11_Label_3;
    LabelZ0Combo[Ports_Midi4][11] = ui->X12_Label_3;
    LabelZ0Combo[Ports_Midi4][12] = ui->X13_Label_3;
    LabelZ0Combo[Ports_Midi4][13] = ui->X14_Label_3;
    LabelZ0Combo[Ports_Midi4][14] = ui->X15_Label_3;
    LabelZ0Combo[Ports_Midi4][15] = ui->X16_Label_3;

    qDebug() << "Midi Selection Combo";
    ///// Midi Selection ComboBox /////
    initializeMidiCombos();

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0; _j < ModeActiv_NumModes; _j++)
        {
            for (int _k = 0; _k < ValSelection_NumCombo; _k++)
            {
                if (midiSelection_Combo[_i][_j][_k])
                    connect(midiSelection_Combo[_i][_j][_k], qOverload<int>(&QComboBox::currentIndexChanged), \
                            this, [this, _i, _j, _k] (int index) {this->sendMidiModeValues(_i, _j, _k, index);});
            }
        }
    }

    qDebug() << "Notes Sel Combo";
    ///// Notes Selection ComboBox /////
    initializeZ0Combos();

    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0 ; _j < MAX_NBEAMS ; _j++)
        {
            if (Z0_ComboBox[_i][_j])
                connect(Z0_ComboBox[_i][_j], qOverload<int>(&QComboBox::currentIndexChanged), this, [this, _i, _j] (int index) {this->comboNoteSelected(_i, _j, index);});
        }
    }

    qDebug() << "Initialize Main Conf";
    ///// QSettings MAIN /////
    InitializeMainConfig();


    qDebug() << "Initialize Mapping";
    ///// TAB 3 & QSettings Mapping /////
    InitializeMapping();

    qDebug() << "Restore Settings and keyboard properties";
    ///// Restore QSettings /////
    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    if (globQSettings.childGroups().contains("Global Settings", Qt::CaseInsensitive))
    {
        globQSettings.beginGroup("Global Settings");
        // Test Mode
        testMode = globQSettings.value("ForTests", false).toBool();

        // Module Enabled
        //modeEnabled = globQSettings.value("ActiveModule", Mode_BasicHarp).toInt();

        // Window Properties
        this->setGeometry(0,0,globQSettings.value("Width", 1150).toInt(),globQSettings.value("Height", 718).toInt());
        QSize screenSize = qApp->primaryScreen()->availableSize();
        this->move((screenSize.width() / 2) - (this->width() / 2), (screenSize.height() / 2) - (this->height() / 2));

        if (globQSettings.value("MaxWin", 0).toInt() == 1)
            this->showMaximized();

        // Restore Keyboard properties
        updateInProgress = true;
        ui->nKeysSpinBox->setValue(globQSettings.value("NKeys", 60).toInt());
        ui->startKeyComboBox->setCurrentIndex(globQSettings.value("StartKey", 48).toInt());
        ui->sendOnClickCheckBox->setChecked(globQSettings.value("SendOnClick", true).toBool());

        ui->nKeysSpinBox_2->setValue(globQSettings.value("NKeys_2", 60).toInt());
        ui->startKeyComboBox_2->setCurrentIndex(globQSettings.value("StartKey_2", 0).toInt());
        ui->sendOnClickCheckBox_2->setChecked(globQSettings.value("SendOnClick_2", true).toBool());

        ui->nKeysSpinBox_3->setValue(globQSettings.value("NKeys_3", 60).toInt());
        ui->startKeyComboBox_3->setCurrentIndex(globQSettings.value("StartKey_3", 0).toInt());
        ui->sendOnClickCheckBox_3->setChecked(globQSettings.value("SendOnClick_3", true).toBool());
        QApplication::processEvents();
        updateInProgress = false;

        globQSettings.endGroup();
    }
    else
    {
        ui->nKeysSpinBox->setValue(60);
        ui->startKeyComboBox->setCurrentIndex(48);
        ui->nKeysSpinBox_2->setValue(60);
        ui->startKeyComboBox_2->setCurrentIndex(0);
        ui->nKeysSpinBox_3->setValue(60);
        ui->startKeyComboBox_3->setCurrentIndex(0);
        this->showMaximized();
    }

    ///// Show last version informations /////
    globQSettings.beginGroup("Last_Version");
    if (globQSettings.value("Version", 0).toInt() != LAST_VERSION)
    {
        globQSettings.setValue("Version", LAST_VERSION);
        VersionDialog verDialog;
        verDialog.setModal(true);
        verDialog.exec();
    }
    globQSettings.endGroup();

    ///// Last MIDI Mode /////
    globQSettings.beginGroup("MIDI Settings");
    lastMidiMode[Ports_Midi1][0] = globQSettings.value("LastMidiMode_Port1_Eff1", Mode_PitchBend - Mode_PolyAftertouch).toInt();
    lastMidiMode[Ports_Midi1][1] = globQSettings.value("LastMidiMode_Port1_Eff2", Mode_ControlChange - Mode_PolyAftertouch).toInt();
    lastMidiMode[Ports_Midi3][0] = globQSettings.value("LastMidiMode_Port3_Eff1", Mode_PitchBend - Mode_PolyAftertouch).toInt();
    lastMidiMode[Ports_Midi3][1] = globQSettings.value("LastMidiMode_Port3_Eff2", Mode_ControlChange - Mode_PolyAftertouch).toInt();
    lastMidiMode[Ports_Midi4][0] = globQSettings.value("LastMidiMode_Port4_Eff1", Mode_PitchBend - Mode_PolyAftertouch).toInt();
    lastMidiMode[Ports_Midi4][1] = globQSettings.value("LastMidiMode_Port4_Eff2", Mode_ControlChange - Mode_PolyAftertouch).toInt();
    globQSettings.endGroup();

    updateInProgress = true;
    ui->DescCC1ComboBox->setCurrentIndex(lastMidiMode[Ports_Midi1][0]);
    ui->DescCC2ComboBox->setCurrentIndex(lastMidiMode[Ports_Midi1][1]);
    ui->DescCC1ComboBox_2->setCurrentIndex(lastMidiMode[Ports_Midi3][0]);
    ui->DescCC2ComboBox_2->setCurrentIndex(lastMidiMode[Ports_Midi3][1]);
    ui->DescCC1ComboBox_3->setCurrentIndex(lastMidiMode[Ports_Midi4][0]);
    ui->DescCC2ComboBox_3->setCurrentIndex(lastMidiMode[Ports_Midi4][1]);
    updateInProgress = false;

    ///// Timer for display update - NOT USED /////
    modifTimer.setInterval(100);
    modifTimer.setSingleShot(false);
    connect(&modifTimer, &QTimer::timeout, this, &MainWindow::checkModifications);
    //modifTimer.start();

    ///// Timer for software connection /////
    softwareConnect.setInterval(1500);
    softwareConnect.setSingleShot(true);
    connect(&softwareConnect, &QTimer::timeout, this, [this] () { this->retryConnection(0); });

    configDone = 1;
    SendLog("Init OK");
    QTimer::singleShot(0, this, &MainWindow::firstLoad);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::firstLoad()
{
    connect(&kbDev, &ComHwKb2d::comFailed, this, &MainWindow::resetMidiPorts);
    connect(&dfuDev, &ComHwDfu::comFailed, this, &MainWindow::resetMidiPorts);
    connect(&harpIn, &MidiDevIn::harpInCalled, this, &MainWindow::harpInProc, Qt::QueuedConnection);
    connect(&extIn, &MidiDevIn::extInCalled, this, &MainWindow::extInProc, Qt::QueuedConnection);

    if (checkNewVersions())
        close();
    else
        updateMidiPortsList();
}

/*
 * ================================
 * Close everything before leaving
 * ================================
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Request for exiting";
    QCoreApplication::processEvents();
    if (ui->actionStopCal->isVisible())
        on_actionStopCal_triggered();
    // Wait for all Feedback and reading actions to stop
    while (kbDev.isConnected() && kbDev.isWaitingFb())
        QApplication::processEvents();
    while (dfuDev.isConnected() && dfuDev.isWaitingFb())
        QApplication::processEvents();
    qDebug() << "Ready to exit";
    modifTimer.stop();
    softwareConnect.stop();
    disconnect(&modifTimer, &QTimer::timeout, this, &MainWindow::checkModifications);
    kbDev.setConnected(0);
    dfuDev.setConnected(0);
    harpOut.close();
    harpIn.stop();
    harpIn.close();
    extIn.stop();
    extIn.close();
    extOut.close();
    throughIn.stop();
    throughIn.close();
    throughOut.close();

    disconnect(&kbDev, &ComHwKb2d::comFailed, this, &MainWindow::resetMidiPorts);
    disconnect(&dfuDev, &ComHwDfu::comFailed, this, &MainWindow::resetMidiPorts);
    disconnect(&harpIn, &MidiDevIn::harpInCalled, this, &MainWindow::harpInProc);
    disconnect(&extIn, &MidiDevIn::extInCalled, this, &MainWindow::extInProc);

    // Save global session settings
    WriteTempMapping();

    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    globQSettings.beginGroup("Global Settings");

    if (this->isMaximized())
        globQSettings.setValue("MaxWin", 1);
    else
    {
        globQSettings.setValue("MaxWin", 0);
        globQSettings.setValue("Width", this->width());
        globQSettings.setValue("Height", this->height());
    }

    // For Tests
    globQSettings.setValue("ForTests", testMode);
    // Mode Enabled
    //globQSettings.setValue("ActiveModule", modeEnabled);

    // External MIDI Controller
    globQSettings.setValue("Ext MIDI In", ui->extMidiInComboBox->currentText());
    globQSettings.setValue("Ext MIDI Out", ui->extMidiOutComboBox->currentText());

    // Keyboard
    globQSettings.setValue("StartKey", ui->startKeyComboBox->currentIndex());
    globQSettings.setValue("NKeys", ui->nKeysSpinBox->value());
    globQSettings.setValue("SendOnClick", ui->sendOnClickCheckBox->isChecked());

    globQSettings.setValue("StartKey_2", ui->startKeyComboBox_2->currentIndex());
    globQSettings.setValue("NKeys_2", ui->nKeysSpinBox_2->value());
    globQSettings.setValue("SendOnClick_2", ui->sendOnClickCheckBox_2->isChecked());

    globQSettings.setValue("StartKey_3", ui->startKeyComboBox_3->currentIndex());
    globQSettings.setValue("NKeys_3", ui->nKeysSpinBox_3->value());
    globQSettings.setValue("SendOnClick_3", ui->sendOnClickCheckBox_3->isChecked());

    globQSettings.endGroup();

    ///// Last MIDI Mode /////
    globQSettings.beginGroup("MIDI Settings");
    globQSettings.setValue("LastMidiMode_Port1_Eff1", lastMidiMode[Ports_Midi1][0]);
    globQSettings.setValue("LastMidiMode_Port1_Eff2", lastMidiMode[Ports_Midi1][1]);
    globQSettings.setValue("LastMidiMode_Port3_Eff1", lastMidiMode[Ports_Midi3][0]);
    globQSettings.setValue("LastMidiMode_Port3_Eff2", lastMidiMode[Ports_Midi3][1]);
    globQSettings.setValue("LastMidiMode_Port4_Eff1", lastMidiMode[Ports_Midi4][0]);
    globQSettings.setValue("LastMidiMode_Port4_Eff2", lastMidiMode[Ports_Midi4][1]);
    globQSettings.endGroup();

    QApplication::processEvents();
    SendLog("Exit Ok\n=====================");

    event->accept();
}

/*
 * ==============================
 * Retry connection to KB2D
 * ==============================
 */
void MainWindow::retryConnection(int attempts)
{
    static int attCount = 1;
    if (attempts != 0)
        attCount = attempts;

    if (attempts == 0)
        attCount --;

    if (attCount != 0)
    {
        updateMidiPortsList();  // Update ports so the KB2D or DFU reconnects
        QApplication::processEvents();
        // Retry is nothing is connected...
        if ((dfuDev.isConnected() == 0) && (kbDev.isConnected() == 0))
            softwareConnect.start();
    }
    else
    {
        updateMidiPortsList();  // Update ports so the KB2D or DFU reconnects
        QApplication::processEvents();
        // DFU is supposed to start now...
        if ((dfuDev.isConnected() == 0) && (kbDev.isConnected() == 0))
        {
            SendError(this, tr("Cannot connect to the device\n\n"
                                 "If this is the first time you start the Firmware Updater on this computer, it is normal. Do not panic.\n"
                                 "Please wait for the driver to be installed (it should take less than 1 minute). Please do not disconnect your KB2D device.\n\n"
                                 "Then press F5 to update the ports (after closing this warning) or restart this User interface. Your LD firmware Updater should now automatically connect "
                                 "to your KB2D Laser Harp interface."), MenuFunc_LoadFW, tr("Cannot connect to LD Firmware Updater"));
        }
    }

}

/*
 * ==============================
 * Check some stuff
 * ==============================
 */
void MainWindow::checkModifications()
{
}

/*
 * ==============================
 * Close MainWindow
 * ==============================
 */
void MainWindow::quitProg()
{
    //QApplication::quit();
    close();
}

/*
 * =================================
 * Update display of Assign Buttons
 * =================================
 */
void MainWindow::repaintAssignButtons()
{
    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0 ; _j < MAX_NBEAMS ; _j++)
        {
            if (assignButton[_i][_j])
                assignButton[_i][_j]->setStyleSheet("");
        }
        if (keyboard[_i] && (keyboard[_i]->getNextAssign() >= 0))
        {
            assignButton[_i][keyboard[_i]->getNextAssign()]->setStyleSheet("background-color:#C22;");
        }
        if (assignAllButton[_i])
        {
            if (assignAllActivated[_i])
                assignAllButton[_i]->setStyleSheet("background-color:#C22;");
            else
                assignAllButton[_i]->setStyleSheet("");
        }
    }
}

void MainWindow::updateEnabledMode()
{

    ui->harpEnabPushButton->setStyleSheet("QPushButton {background-color:#336;} QPushButton:hover {background-color:#bb8800;} QPushButton:pressed {background-color:#bb0000;}");
    ui->harpHeightEnabPushButton->setStyleSheet("QPushButton {background-color:#336;} QPushButton:hover {background-color:#bb8800;} QPushButton:pressed {background-color:#bb0000;}");
    ui->trackingEnabPushButton->setStyleSheet("QPushButton {background-color:#336;} QPushButton:hover {background-color:#bb8800;} QPushButton:pressed {background-color:#bb0000;}");
    ui->thereminEnabPushButton->setStyleSheet("QPushButton {background-color:#336;} QPushButton:hover {background-color:#bb8800;} QPushButton:pressed {background-color:#bb0000;}");

    /*
    switch (modeEnabled)
    {
    case Mode_BasicHarp:
        ui->harpEnabPushButton->click();
        break;
    case Mode_HarpHeight:
        ui->harpHeightEnabPushButton->click();
        break;
    case Mode_Tracking:
        ui->trackingEnabPushButton->click();
        break;
    case Mode_Theremin:
        ui->thereminEnabPushButton->click();
        break;
    default:
        ui->harpEnabPushButton->click();
        break;
    }
    */
}

void MainWindow::on_harpEnabPushButton_clicked()
{
    //modeEnabled = Mode_BasicHarp;
    // Show modules
    //groupList[Group_PosXParam]->hide();
    //groupList[Group_DetZParam]->hide();
    if (!(enabState[Ports_Midi1] & Mode_NoteOn))
        on_enableNotesOnOffButton_clicked();
    if (((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn)
        on_enableEffect1Button_clicked();
    if (((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn)
        on_enableEffect2Button_clicked();
    //groupList[Group_Effect0]->show();
    //groupList[Group_Effect1]->hide();
    //groupList[Group_Effect2]->hide();
    // Set Midi values
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_Channel]->setCurrentIndex(Channel_1);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_CtrlNotes]->setCurrentIndex(Val_Keyboard);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_ValVel]->setCurrentText("127");
    // Set properties
    ui->minTimeSlider->setValue(5);
    ui->maxTimeSlider->setValue(15);
    /*
    ui->DetSpeedLabel->hide();
    ui->minTimeSpinBox->hide();
    ui->minTimeSlider->hide();
    ui->DetSelectivityLabel->hide();
    ui->maxTimeSpinBox->hide();
    ui->maxTimeSlider->hide();
    */
}

void MainWindow::on_harpHeightEnabPushButton_clicked()
{
    //modeEnabled = Mode_HarpHeight;
    // Show modules
    //groupList[Group_PosXParam]->hide();
    //groupList[Group_DetZParam]->show();
    if (!(enabState[Ports_Midi1] & Mode_NoteOn))
        on_enableNotesOnOffButton_clicked();
    if (!(((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn))
        on_enableEffect1Button_clicked();
    if (((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn)
        on_enableEffect2Button_clicked();
    //groupList[Group_Effect0]->show();
    //groupList[Group_Effect1]->show();
    //groupList[Group_Effect2]->hide();
    // Set Midi values
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_Channel]->setCurrentIndex(Channel_1);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_CtrlNotes]->setCurrentIndex(Val_Keyboard);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_ValVel]->setCurrentText("127");

    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_Channel]->setCurrentIndex(Channel_1);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_CtrlNotes]->setCurrentText("0");
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_ValVel]->setCurrentIndex(Val_HeightZ);

    ui->DescCC1ComboBox->setCurrentIndex(Mode_PitchBend - Mode_PolyAftertouch);
    // Set properties
    ui->minTimeSlider->setValue(5);
    ui->maxTimeSlider->setValue(15);
    /*ui->DetSpeedLabel->hide();
    ui->minTimeSpinBox->hide();
    ui->minTimeSlider->hide();
    ui->DetSelectivityLabel->hide();
    ui->maxTimeSpinBox->hide();
    ui->maxTimeSlider->hide();*/
}

void MainWindow::on_trackingEnabPushButton_clicked()
{
    //modeEnabled = Mode_Tracking;
    // Show modules
    //groupList[Group_PosXParam]->show();
    //groupList[Group_DetZParam]->hide();
    if (enabState[Ports_Midi1] & Mode_NoteOn)
        on_enableNotesOnOffButton_clicked();
    if (((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn)
        on_enableEffect1Button_clicked();
    if (!(((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn))
        on_enableEffect2Button_clicked();
    //groupList[Group_Effect0]->hide();
    //groupList[Group_Effect1]->hide();
    //groupList[Group_Effect2]->show();
    // Set Midi values
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_Channel]->setCurrentIndex(Channel_1);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_CtrlNotes]->setCurrentText("1");
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_ValVel]->setCurrentIndex(Val_PosX);

    ui->DescCC2ComboBox->setCurrentIndex(Mode_ControlChange - Mode_PolyAftertouch);
    // Set properties
    ui->minTimeSlider->setValue(1);
    ui->maxTimeSlider->setValue(15);
    /*ui->DetSpeedLabel->show();
    ui->minTimeSpinBox->show();
    ui->minTimeSlider->show();
    ui->DetSelectivityLabel->show();
    ui->maxTimeSpinBox->show();
    ui->maxTimeSlider->show();

    ui->minWidthXLabel->hide();
    ui->minWidthXSpinBox->hide();
    ui->maxWidthXLabel->hide();
    ui->maxWidthXSpinBox->hide();
    ui->minGlideXLabel->hide();
    ui->minGlideXSpinBox->hide();
    ui->maxGlideXLabel->hide();
    ui->maxGlideXSpinBox->hide();
    ui->invertWidthXCheckBox->hide();
    ui->invertGlideXCheckBox->hide();*/
}

void MainWindow::on_thereminEnabPushButton_clicked()
{
    //modeEnabled = Mode_Theremin;
    // Show modules
    //groupList[Group_PosXParam]->show();
    //groupList[Group_DetZParam]->hide();

    if (!(enabState[Ports_Midi1] & Mode_NoteOn))
        on_enableNotesOnOffButton_clicked();
    if (!(((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn))
        on_enableEffect1Button_clicked();
    if (!(((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn))
        on_enableEffect2Button_clicked();
    //groupList[Group_Effect0]->show();
    //groupList[Group_Effect1]->show();
    //groupList[Group_Effect2]->show();
    // Set Midi values
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_Channel]->setCurrentIndex(Channel_1);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_CtrlNotes]->setCurrentText("63");
    midiSelection_Combo[Ports_Midi1][ModeActiv_Notes][ValSelection_ValVel]->setCurrentText("127");

    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_Channel]->setCurrentIndex(Channel_1);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_CtrlNotes]->setCurrentText("0");
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control1][ValSelection_ValVel]->setCurrentIndex(Val_PosX);

    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_Channel]->setCurrentIndex(Channel_1);
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_CtrlNotes]->setCurrentText("1");
    midiSelection_Combo[Ports_Midi1][ModeActiv_Control2][ValSelection_ValVel]->setCurrentIndex(Val_WidthX);

    ui->DescCC1ComboBox->setCurrentIndex(Mode_PitchBend - Mode_PolyAftertouch);
    ui->DescCC2ComboBox->setCurrentIndex(Mode_ControlChange - Mode_PolyAftertouch);
    // Set properties
    ui->enableAngFilterCheckBox->setChecked(false);
    ui->minTimeSlider->setValue(1);
    ui->maxTimeSlider->setValue(15);
    /*ui->DetSpeedLabel->show();
    ui->minTimeSpinBox->show();
    ui->minTimeSlider->show();
    ui->DetSelectivityLabel->show();
    ui->maxTimeSpinBox->show();
    ui->maxTimeSlider->show();

    ui->minWidthXLabel->show();
    ui->minWidthXSpinBox->show();
    ui->maxWidthXLabel->show();
    ui->maxWidthXSpinBox->show();
    ui->minGlideXLabel->show();
    ui->minGlideXSpinBox->show();
    ui->maxGlideXLabel->show();
    ui->maxGlideXSpinBox->show();
    ui->invertWidthXCheckBox->show();
    ui->invertGlideXCheckBox->show();*/
}

/*
 * ==============================
 * Save params
 * ==============================
 */
void MainWindow::saveInFlashFunc()
{
    if (kbDev.isConnected())
    {
        if (kbDev.checkFeedback(Check_SaveInFlash) == 0x7F)
            ui->statusBar->showMessage(tr("Parameters saved in Flash memory"), 3000);
    }
}

/*
 * ==============================
 * Start
 * ==============================
 */
void MainWindow::startFunc()
{
    kbDev.sendCom(MIDI_START);
    if (kbDev.checkFeedback(Check_PauseOn) == 0)
    {
        ui->actionStart->setEnabled(0);
        ui->actionPause->setEnabled(1);
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(1);
    }
}

/*
 * ==============================
 * Pause - Stop Laser
 * ==============================
 */
void MainWindow::pauseFunc()
{
    kbDev.sendCom(MIDI_PAUSE);
    if (kbDev.checkFeedback(Check_PauseOn) == 1)
    {

        ui->actionStart->setEnabled(1);
        ui->actionPause->setEnabled(0);
        ui->actionStart->setVisible(1);
        ui->actionPause->setVisible(0);
    }
}

/*
 * ==============================
 * Restart
 * ==============================
 */
void MainWindow::restartFunc()
{
    QCoreApplication::processEvents();
    QElapsedTimer timer;
    timer.start();
    while (kbDev.isWaitingFb())
    {
        QCoreApplication::processEvents();
        if (timer.elapsed() > 500)
        {
            // Communication error...
            SendError(0, QObject::tr("Timeout - Device is Busy"), MainWindow_Restart);
            return;
        }
    }
    kbDev.sendCom(MIDI_RESTART);
    harpOut.close();
    kbDev.setConnected(0);
    ui->statusBar->showMessage(tr("Wait while restarting..."), 2000);
    setStatus(tr("Wait while restarting..."));
    QApplication::processEvents();
    saveCurrentDisplayAndDisable();
    //ui->tabWidget->removeTab(GetTabIndex(ui->tabWidget, listNameTabs[Tab_KB2DSettings]));
    //ui->tabWidget->removeTab(GetTabIndex(ui->tabWidget, listNameTabs[Tab_ExternalMIDIMapping]));
    qSleep(2000);
    ui->statusBar->showMessage(tr("Ready"), 3000);
    restoreDisplay();
    //ui->tabWidget->addTab(ui->mainTab, listNameTabs[Tab_KB2DSettings]);
    //ui->tabWidget->addTab(ui->mappingTab, listNameTabs[Tab_ExternalMIDIMapping]);
    //ui->tabWidget->setCurrentIndex(0);
    updateMidiPortsList();  // updateAll is automatically used when ports are updated.
}

void MainWindow::disableAllGroups(bool hideToo)
{
    for (int _i = 0 ; _i < Group_NumTotal ; _i++)
    {
        if (groupList[_i])
        {
            groupList[_i]->setDisabled(1);
            if (hideToo)
                groupList[_i]->hide();
        }
    }
}

void MainWindow::enableAllGroups()
{
    for (int _i = 0 ; _i < Group_NumTotal ; _i++)
    {
        if (groupList[_i])
        {
            groupList[_i]->show();
            groupList[_i]->setEnabled(true);
        }
    }
}

void MainWindow::saveCurrentDisplay()
{
    for (int _i = 0 ; _i < Group_NumTotal ; _i++)
    {
        if (groupList[_i])
        {
            groupActivated[_i] = groupList[_i]->isEnabled();
            groupHidden[_i] = groupList[_i]->isHidden();
        }
    }
}

void MainWindow::setEnableGroup(int indexGroup, bool state, bool hideToo)
{
    if (groupList[indexGroup])
    {
        if (groupList[indexGroup]->isHidden() && state)
            groupList[indexGroup]->show();
        groupList[indexGroup]->setEnabled(state);
        if (!state && hideToo)
            groupList[indexGroup]->setVisible(0);
    }
}

void MainWindow::restoreDisplay()
{
    for (int _i = 0 ; _i < Group_NumTotal ; _i++)
    {
        if (groupList[_i])
        {
            groupList[_i]->setEnabled(groupActivated[_i]);
            groupList[_i]->setHidden(groupHidden[_i]);
        }
    }
}

/*
 * ==================
 * Update Status
 * ==================
 */
void MainWindow::setStatus(QString const& status)
{
    ui->statusLabel->setText(status);
}

/*
 * =========================
 * DFU Only
 * Set text on Flash Button
 * =========================
 */
void MainWindow::setFlashText(const QString &text)
{
    ui->flashProgButton->setText(text);
}

/*
 * =======================
 * Set Serial Number
 * Can be set only once
 * (Lightdiction Only)
 * =======================
 */
void MainWindow::on_SNButton_clicked()
{
    bool ok = 0;
    int SNToLoad = 0;
    SNToLoad = QInputDialog::getInt(this, "S/N ?", "S/N = ", 0, 0, 16383, 1, &ok);
    if (ok)
    {
        //QMessageBox::information(this, "Data sent", "\nS/N: " + (QString::number(((SNToLoad >> 7) & 0x7F)))+ " " + (QString::number((SNToLoad & 0x7F))));
        kbDev.sendCom(MIDI_SN + ((SNToLoad >> 7) & 0x7F));      // Set High bits value here (x127)
        kbDev.sendCom(MIDI_SUBSN + (SNToLoad & 0x7F));             // Set Low bits value here
    }
}

/*
 * ======================
 * DFU Only
 * ======================
 */
void MainWindow::on_flashProgButton_clicked()
{
    flashProg();
}

/*
 * =============================================
 * Harp In function linked to CALLBACK
 * =============================================
 */
void MainWindow::harpInProc()
{
    ////////////////////// Firmware Tests /////////////////////
    /// Firmware tests are directly done in ComHw function

    ////////////////// Start and Pause Tests //////////////////
    if (kbDev.isWaitingFb() == 0)
    {
        if ((kbDev.getID(VERSION) > 8) || ((kbDev.getID(VERSION) == 8) && (kbDev.getID(SUBVERSION) >= 3)))
        {
            if ((harpIn.getParam(0) == _DEPLOY_MIDIBUTTON[0]) && (harpIn.getParam(1) == _DEPLOY_MIDIBUTTON[1]) && (harpIn.getParam(2) == 0))
            {
                //ui->startButton->click();
                ui->actionStart->trigger();
            }
            else if ((harpIn.getParam(0) == _DEPLOY_MIDIBUTTON[0]) && (harpIn.getParam(1) == _DEPLOY_MIDIBUTTON[1]) && (harpIn.getParam(2) == 1))
            {
                //ui->pauseButton->click();
                ui->actionPause->trigger();
            }
            else if (harpIn.getParam(0) == 0xB5)
                qDebug() << "Debug value =" << (int)harpIn.getParam(1) * 128 + harpIn.getParam(2);
        }
        else
        {
            if ((harpIn.getParam(0) == 0xB7) && (harpIn.getParam(1) == 0x2C) && (harpIn.getParam(2) == 0))
            {
                //ui->startButton->click();
                ui->actionStart->trigger();
            }
            else if ((harpIn.getParam(0) == 0xB7) && (harpIn.getParam(1) == 0x2C) && (harpIn.getParam(2) == 1))
            {
                //ui->pauseButton->click();
                ui->actionPause->trigger();
            }
        }
    }
    ///////////////////////////////////////////////////////////
    kbDev.waitForFeedback(0);
    dfuDev.waitForFeedback(0);
}

#ifdef WIN_PLATFORM
/*
 * ========================
 * MIDI Callback for users
 * ========================
 */
void MidiDevIn::midiInCallback(HMIDIIN hMidiIn, DWORD_PTR dwInstance, unsigned char data1, unsigned char data2, unsigned char data3, DWORD_PTR mdTimestamp)
{
    (void)dwInstance;
    (void)mdTimestamp; // Does nothing. Just avoid to get a warning because that var is unused.
    if (hMidiIn == harpIn.getDev())
    {
        harpIn.setParam(0, data1);
        harpIn.setParam(1, data2);
        harpIn.setParam(2, data3);
        emit harpIn.harpInCalled();
        //reinterpret_cast<MainWindow*> (dwInstance)->harpInProc();
    }
    else if (hMidiIn == extIn.getDev())
    {
        if (((kbDev.isConnected() == 1) || (extMidiIndexToLearn >= 0)) && (kbDev.isWaitingFb() == 0) && (data1 < 0xF0)) // Check we are not already waiting for a signal from the KB2D
            emit extIn.extInCalled(data1, data2, data3);
            //reinterpret_cast<MainWindow*> (dwInstance)->extInProc(data1, data2, data3);
    }
    // MIDI Through is directly sent here
    else if ((hMidiIn == throughIn.getDev()) && (throughOut.getName() != ""))
    {
        if (throughOut.sendWord(data1, data2, data3) != MMSYSERR_NOERROR)
            qDebug() << "Midi Out err";
    }
}
#endif
#ifdef LIN_PLATFORM
/*
 * ========================
 * MIDI Thread Input
 * ========================
 */
void MidiDevIn::midiInThread()
{
    char buffer[3] = {0};

    while (devIn != nullptr)
    {
        while (((unsigned int)buffer[0] < 0x80) && (devIn != nullptr))
        {
            snd_rawmidi_read(devIn, buffer, 1);
        }
        if (devIn == nullptr)
            return;
        snd_rawmidi_read(devIn, buffer + 1, 1);
        if (devIn == nullptr)
            return;
        snd_rawmidi_read(devIn, buffer + 2, 1);

        if (devIn == harpIn.getDev())
        {
            harpIn.setParam(0, (unsigned char) buffer[0]);
            harpIn.setParam(1, (unsigned char) buffer[1]);
            harpIn.setParam(2, (unsigned char) buffer[2]);
            emit harpIn.harpInCalled();
            //reinterpret_cast<MainWindow*> (dwInstance)->harpInProc();
        }
        else if (devIn == extIn.getDev())
        {
            if (((kbDev.isConnected() == 1) || (extMidiIndexToLearn >= 0)) && (kbDev.isWaitingFb() == 0))    // Check we are not already waiting for a signal from the KB2D
                emit extIn.extInCalled((unsigned char) buffer[0], (unsigned char) buffer[1], (unsigned char) buffer[2]);
                //reinterpret_cast<MainWindow*> (dwInstance)->extInProc(data1, data2, data3);
        }
        // MIDI Through is directly sent here
        else if ((devIn == throughIn.getDev()) && (throughOut.getName() != ""))
        {
            if (throughOut.sendWord((unsigned char) buffer[0], (unsigned char) buffer[1], (unsigned char) buffer[2]) < 0)
                qDebug() << "Midi Out err";
        }
        buffer[0] = 0;
        buffer[1] = 0;
        buffer[2] = 0;
    }
}
#endif
#ifdef MAC_PLATFORM
void MidiDevIn::midiInProcMac11(const MIDIEventList *listEventsIn, void *refCon)
{
    MIDIEndpointRef hMidiIn = *((MIDIEndpointRef*)refCon);
    MIDIEventPacket* packet = (MIDIEventPacket*)listEventsIn->packet;
    for (unsigned int _i = 0 ; _i < listEventsIn->numPackets ; _i++)
    {
        unsigned char data1 = (unsigned char)((packet->words[0] >> 16) & 0xFF);
        unsigned char data2 = (unsigned char)((packet->words[0] >> 8) & 0xFF);
        unsigned char data3 = (unsigned char)((packet->words[0] >> 0) & 0xFF);

        if (hMidiIn == harpIn.getDev())
        {
            harpIn.setParam(0, data1);
            harpIn.setParam(1, data2);
            harpIn.setParam(2, data3);
            emit harpIn.harpInCalled();
        }
        else if (hMidiIn == extIn.getDev())
        {
            if (((kbDev.isConnected() == 1) || (extMidiIndexToLearn >= 0)) && (kbDev.isWaitingFb() == 0))    // Check we are not already waiting for a signal from the KB2D
                emit extIn.extInCalled(data1, data2, data3);
        }
        // MIDI Through is directly sent here
        else if ((hMidiIn == throughIn.getDev()) && (throughOut.getName() != ""))
        {
            if (throughOut.sendWord(data1, data2, data3) != MMSYSERR_NOERROR)
                qDebug() << "Midi Out err";
        }
        packet = MIDIEventPacketNext(packet);
    }
}

void MidiDevIn::midiInProc(const MIDIPacketList *listPacketsIn, void *readProcRef, void *refCon)
{
    (void)readProcRef;
    MIDIEndpointRef hMidiIn = *((MIDIEndpointRef*)refCon);
    MIDIPacket* packet = (MIDIPacket*)listPacketsIn->packet;
    for (unsigned int _i = 0 ; _i < listPacketsIn->numPackets ; _i++)
    {
        unsigned char data1 = (unsigned char)packet->data[0];
        unsigned char data2 = (unsigned char)packet->data[1];
        unsigned char data3 = (unsigned char)packet->data[2];

        if (hMidiIn == harpIn.getDev())
        {
            harpIn.setParam(0, data1);
            harpIn.setParam(1, data2);
            harpIn.setParam(2, data3);
            emit harpIn.harpInCalled();
        }
        else if (hMidiIn == extIn.getDev())
        {
            if (((kbDev.isConnected() == 1) || (extMidiIndexToLearn >= 0)) && (kbDev.isWaitingFb() == 0))    // Check we are not already waiting for a signal from the KB2D
                emit extIn.extInCalled(data1, data2, data3);
        }
        // MIDI Through is directly sent here
        else if ((hMidiIn == throughIn.getDev()) && (throughOut.getName() != ""))
        {
            if (throughOut.sendWord(data1, data2, data3) != MMSYSERR_NOERROR)
                qDebug() << "Midi Out err";
        }
        packet = MIDIPacketNext(packet);
    }
}
#endif

/*
 * ==========================
 * Exit the Firmware Updater
 * ==========================
 */
void MainWindow::on_exitUpdaterButton_clicked()
{
    exitFUpdater();
}

/*
 * ==============================
 * Update All Values
 * ==============================
 */
int MainWindow::updateAll(bool optionWin)
{
    int retErr = 0;
    //kbDev.setID(VERSION, 0);
    QApplication::processEvents();

    ui->midiTabWidget->setCurrentIndex(0);
    //ui->midiTabWidget->removeTab(2);
    //ui->midiTabWidget->removeTab(1);
    ui->midiTabWidget->setTabEnabled(1, false);
    ui->midiTabWidget->setTabEnabled(2, false);

    if (keyboard[Ports_Midi1])
    {
        delete keyboard[Ports_Midi1];
        keyboard[Ports_Midi1] = nullptr;
    }
    if (keyboard[Ports_Midi3])
    {
        delete keyboard[Ports_Midi3];
        keyboard[Ports_Midi3] = nullptr;
    }
    if (keyboard[Ports_Midi4])
    {
        delete keyboard[Ports_Midi4];
        keyboard[Ports_Midi4] = nullptr;
    }

    setEnableGroup(Group_KB2DPorts, false);

    if ((kbDev.checkFeedback(Check_SN) >= 0) && (kbDev.checkFeedback(Check_SubSN) >= 0) && (kbDev.checkFeedback(Check_Version) >= 0) && (kbDev.checkFeedback(Check_SubVersion) >= 0))
    {
        kbDev.setID(VERSION, kbDev.checkFeedback(Check_Version));
        kbDev.setID(SUBVERSION, kbDev.checkFeedback(Check_SubVersion));
        kbDev.setID(SERIAL, (kbDev.checkFeedback(Check_SN) << 7) + kbDev.checkFeedback(Check_SubSN));

        if (lastParsedFirmware > (int)kbDev.getID(VERSION) * 100 + (int)kbDev.getID(SUBVERSION))
        {
            if (QMessageBox::question(this, tr("Firmware outdated"), \
                                      "KB2D - S/N: " + QString::number(kbDev.getID(SERIAL)).rightJustified(4, QChar('0')) + \
                                      tr(" - Firmware version: ") + QString::number(kbDev.getID(VERSION)) + \
                                      "."+ QString::number(kbDev.getID(SUBVERSION)).rightJustified(2, QChar('0')) + "\n\n" + \
                                     tr("The new firmware version ") + QString::number(float(lastParsedFirmware) / 100, 'f', 2) + \
                                     tr(" is available.\n\nYour KB2D will be updated automatically, do you want to continue?\n\n"
                                        "(Firmware updates may be necessary to keep using the last software version)")) == QMessageBox::Yes)
            {
                //kbDev.sendCom(MIDI_INAPPBOOT);  // Sends a message to KB2D / DFU so it disconnects and restarts in the other mode.
                //qSleep(1000);
                fuUpdateRequested = true;
                return -1;
            }
        }

        // This interface is not compatible with older version. It requires an update to version 8.00
        if (!((kbDev.getID(VERSION) > 8) || ((kbDev.getID(VERSION) == 8) && (kbDev.getID(SUBVERSION) >= 3))))
        {
            QMessageBox::warning(this, tr("Update Required"), tr("Firmware outdated: you must update your firmware (v8.03 or higher) to use this version of the software.\n"
                                                          "Current firmware version: ") + QString::number(kbDev.getID(VERSION)) + \
                                                            "."+ QString::number(kbDev.getID(SUBVERSION)).rightJustified(2, QChar('0')));
            //kbDev.sendCom(MIDI_INAPPBOOT);  // Sends a message to KB2D / DFU so it disconnects and restarts in the other mode.
            //qSleep(1000);
            return -1;
        }
    }
    else
        retErr = 1;

    int nbPorts = kbDev.checkFeedback(Check_NbPorts);
    if ((retErr == 0) && (nbPorts >= 0))
    {
        updateInProgress = true;
        if (nbPorts == 3)
        {
            ui->nbPortsCombo->setCurrentIndex(1);
            //ui->midiTabWidget->addTab(ui->midiPort3Tab, "MIDI Effects configuration [ KB2D_3 ]");
            ui->midiTabWidget->setTabEnabled(1, true);
        }
        else if (nbPorts == 4)
        {
            ui->nbPortsCombo->setCurrentIndex(2);
            //ui->midiTabWidget->addTab(ui->midiPort3Tab, "MIDI Effects configuration [ KB2D_3 ]");
            //ui->midiTabWidget->addTab(ui->midiPort4Tab, "MIDI Effects configuration [ KB2D_4 ]");
            ui->midiTabWidget->setTabEnabled(1, true);
            ui->midiTabWidget->setTabEnabled(2, true);
        }
        else
        {
            ui->nbPortsCombo->setCurrentIndex(0);
        }

        ui->midiTabWidget->setCurrentIndex(0);
        QApplication::processEvents();
        updateInProgress = false;
    }
    else
        retErr = 1;

    qDebug() << "Reading Parameters...";
    if ((retErr == 0) && (kbDev.checkFeedback(Check_nBeamsX) >= 0) && (kbDev.checkFeedback(Check_DetLevel) >= 0) && (kbDev.checkFeedback(Check_DetLevelH) >= 0) && \
            (kbDev.checkFeedback(Check_FPS) >= 0) && (kbDev.checkFeedback(Check_MinPos) >= 0) && (kbDev.checkFeedback(Check_MultPos) >= 0) && \
            (kbDev.checkFeedback(Check_HalfDelta) >= 0) && (kbDev.checkFeedback(Check_Gain) >= 0) && (kbDev.checkFeedback(Check_Release) >= 0) && \
            (kbDev.checkFeedback(Check_RelativeH) >= 0) && (kbDev.checkFeedback(Check_InvertZ) >= 0) && (kbDev.checkFeedback(Check_StabZ) >= 0) && \
            (kbDev.checkFeedback(Check_AmpZ) >= 0) && (kbDev.checkFeedback(Check_SmoothZ) >= 0) && (kbDev.checkFeedback(Check_FiltZ) >= 0) && \
            (kbDev.checkFeedback(Check_MinZ) >= 0) && (kbDev.checkFeedback(Check_MaxZ) >= 0) && \
            (kbDev.checkFeedback(Check_InvertVarsX) >= 0) && (kbDev.checkFeedback(Check_GlideStab) >= 0) && (kbDev.checkFeedback(Check_AngFilter) >= 0) && \
            (kbDev.checkFeedback(Check_MinPosX) >= 0) && (kbDev.checkFeedback(Check_MaxPosX) >= 0) && (kbDev.checkFeedback(Check_MinWidthX) >= 0) && \
            (kbDev.checkFeedback(Check_MaxWidthX) >= 0) && (kbDev.checkFeedback(Check_MinGlideX) >= 0) && (kbDev.checkFeedback(Check_MaxGlideX) >= 0) && \

            (kbDev.checkFeedback(Check_BeamAngleListX0) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH0) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX1) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListXH1) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX2) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH2) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListX3) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH3) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX4) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListXH4) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX5) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH5) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListX6) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH6) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX7) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListXH7) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX8) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH8) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListX9) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH9) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX10) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListXH10) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX11) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH11) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListX12) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH12) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX13) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListXH13) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX14) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH14) >= 0) && \
            (kbDev.checkFeedback(Check_BeamAngleListX15) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH15) >= 0) && (kbDev.checkFeedback(Check_NbPorts) >= 0) && \
            // PORT 1
            (kbDev.checkFeedback(Check_EnabMidiMode) >= 0) && (kbDev.checkFeedback(Check_CheckVarUse) >= 0) && \
            (kbDev.checkFeedback(Check_NoteChan) >= 0) && (kbDev.checkFeedback(Check_NoteNote) >= 0) && (kbDev.checkFeedback(Check_NoteVel) >= 0) && \
            (kbDev.checkFeedback(Check_CC1Chan) >= 0) && (kbDev.checkFeedback(Check_CC1Ctrl) >= 0) && (kbDev.checkFeedback(Check_CC1Val) >= 0) && \
            (kbDev.checkFeedback(Check_CC2Chan) >= 0) && (kbDev.checkFeedback(Check_CC2Ctrl) >= 0) && (kbDev.checkFeedback(Check_CC2Val) >= 0) && \
            (kbDev.checkFeedback(Check_Activate2PL) >= 0) && (kbDev.checkFeedback(Check_Activate2PM) >= 0) && (kbDev.checkFeedback(Check_Activate2PH) >= 0) && \

            (kbDev.checkFeedback(Check_NoteToPlay0) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay1) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay2) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay3) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay4) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay5) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay6) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay7) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay8) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay9) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay10) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay11) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay12) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay13) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay14) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay15) >= 0) && \
            // PORT 3
            (kbDev.checkFeedback(Check_EnabMidiMode_3P) >= 0) && (kbDev.checkFeedback(Check_CheckVarUse_3P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteChan_3P) >= 0) && (kbDev.checkFeedback(Check_NoteNote_3P) >= 0) && (kbDev.checkFeedback(Check_NoteVel_3P) >= 0) && \
            (kbDev.checkFeedback(Check_CC1Chan_3P) >= 0) && (kbDev.checkFeedback(Check_CC1Ctrl_3P) >= 0) && (kbDev.checkFeedback(Check_CC1Val_3P) >= 0) && \
            (kbDev.checkFeedback(Check_CC2Chan_3P) >= 0) && (kbDev.checkFeedback(Check_CC2Ctrl_3P) >= 0) && (kbDev.checkFeedback(Check_CC2Val_3P) >= 0) && \
            (kbDev.checkFeedback(Check_Activate3PL) >= 0) && (kbDev.checkFeedback(Check_Activate3PM) >= 0) && (kbDev.checkFeedback(Check_Activate3PH) >= 0) && \

            (kbDev.checkFeedback(Check_NoteToPlay0_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay1_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay2_3P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay3_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay4_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay5_3P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay6_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay7_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay8_3P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay9_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay10_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay11_3P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay12_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay13_3P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay14_3P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay15_3P) >= 0) && \
            // PORT 4
            (kbDev.checkFeedback(Check_EnabMidiMode_4P) >= 0) && (kbDev.checkFeedback(Check_CheckVarUse_4P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteChan_4P) >= 0) && (kbDev.checkFeedback(Check_NoteNote_4P) >= 0) && (kbDev.checkFeedback(Check_NoteVel_4P) >= 0) && \
            (kbDev.checkFeedback(Check_CC1Chan_4P) >= 0) && (kbDev.checkFeedback(Check_CC1Ctrl_4P) >= 0) && (kbDev.checkFeedback(Check_CC1Val_4P) >= 0) && \
            (kbDev.checkFeedback(Check_CC2Chan_4P) >= 0) && (kbDev.checkFeedback(Check_CC2Ctrl_4P) >= 0) && (kbDev.checkFeedback(Check_CC2Val_4P) >= 0) && \
            (kbDev.checkFeedback(Check_Activate4PL) >= 0) && (kbDev.checkFeedback(Check_Activate4PM) >= 0) && (kbDev.checkFeedback(Check_Activate4PH) >= 0) && \

            (kbDev.checkFeedback(Check_NoteToPlay0_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay1_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay2_4P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay3_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay4_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay5_4P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay6_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay7_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay8_4P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay9_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay10_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay11_4P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay12_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay13_4P) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay14_4P) >= 0) && \
            (kbDev.checkFeedback(Check_NoteToPlay15_4P) >= 0))
    {
        qDebug() << "All parameters read";
        enableAllGroups();
        setDetActionsVisibility(1);

        if (nbPorts < 3)    // If only 1 port is selected, "Enable beams" option is useless. Just enable all beams and hide this option.
        {
            setEnableGroup(Group_Enable, false, true);
            beamsEnabled[Ports_Midi1] = 0xFFFF;
            kbDev.sendCom(MIDI_ACTIVATE2PL + 0x7F);
            kbDev.sendCom(MIDI_ACTIVATE2PM + 0x7F);
            kbDev.sendCom(MIDI_ACTIVATE2PH + 0x3);
        }

        ui->actionLoad_now->setEnabled(0);
        ui->actionLoad_now->setVisible(0);
        ui->actionLoad_Firmware_2_0->setEnabled(1);
        ui->menuCommands->setEnabled(1);
        ui->menuOutils->setEnabled(1);
        ui->actionSave_in_Memory->setEnabled(1);

        if (kbDev.checkFeedback(Check_PauseOn) == 0)
        {

            ui->actionStart->setEnabled(0);
            ui->actionPause->setEnabled(1);
            ui->actionStart->setVisible(0);
            ui->actionPause->setVisible(1);
        }
        else if (kbDev.checkFeedback(Check_PauseOn) == 1)
        {
            ui->actionStart->setEnabled(1);
            ui->actionPause->setEnabled(0);
            ui->actionStart->setVisible(1);
            ui->actionPause->setVisible(0);
        }
        else
        {
            ui->actionStart->setEnabled(0);
            ui->actionPause->setEnabled(0);
            ui->actionStart->setVisible(1);
            ui->actionPause->setVisible(1);
        }

        //////////////////////////////

        int saveNBeamsX = kbDev.checkFeedback(Check_nBeamsX);
        updateInProgress = true;
        ui->nBeamsXComboBox->setCurrentIndex(saveNBeamsX - 1);
        QApplication::processEvents();
        updateInProgress = false;
        updateAngleBoxVisibility();

        int valueFb = (kbDev.checkFeedback(Check_DetLevelH) << 7) + kbDev.checkFeedback(Check_DetLevel);
        if (valueFb <= 3000)
            ui->detLevelSlider->setValue(valueFb);
        else
            ui->detLevelSlider->setValue(3000);
        ui->FPSSlider->setValue(kbDev.checkFeedback(Check_FPS) + 50);
        ui->minTimeSlider->setValue(qCeil(qPow(kbDev.checkFeedback(Check_MinPos), 1 / POW_MINPOS)) + 1);
        ui->maxTimeSlider->setValue(qCeil(qPow(kbDev.checkFeedback(Check_MultPos), 1 / POW_MAXPOS)) + 1);
        ui->accuracySpinBox->setValue(kbDev.checkFeedback(Check_HalfDelta));
        ui->hardAmpComboBox->setCurrentIndex(kbDev.checkFeedback(Check_Gain));
        ui->releaseSlider->setValue(kbDev.checkFeedback(Check_Release));

        int tempInvert = kbDev.checkFeedback(Check_InvertVarsX);
        ui->invertPosXCheckBox->setChecked(tempInvert & VarInvert_PosX);
        ui->invertWidthXCheckBox->setChecked(tempInvert & VarInvert_WidthX);
        ui->invertGlideXCheckBox->setChecked(tempInvert & VarInvert_GlideX);

        ui->enableAngFilterCheckBox->setChecked(kbDev.checkFeedback(Check_AngFilter));
        ui->accuracySpinBox->setEnabled(ui->enableAngFilterCheckBox->isChecked());
        stabGlideSave = kbDev.checkFeedback(Check_GlideStab);
        minPosXSave = kbDev.checkFeedback(Check_MinPosX);
        maxPosXSave = kbDev.checkFeedback(Check_MaxPosX);
        minWidthXSave = kbDev.checkFeedback(Check_MinWidthX);
        maxWidthXSave = kbDev.checkFeedback(Check_MaxWidthX);
        minGlideXSave = kbDev.checkFeedback(Check_MinGlideX);
        maxGlideXSave = kbDev.checkFeedback(Check_MaxGlideX);
        ui->stabGlideSlider->setValue(stabGlideSave);
        ui->minPosXSpinBox->setValue(minPosXSave);
        ui->maxPosXSpinBox->setValue(maxPosXSave);
        ui->minWidthXSpinBox->setValue(minWidthXSave);
        ui->maxWidthXSpinBox->setValue(maxWidthXSave);
        ui->minGlideXSpinBox->setValue(minGlideXSave);
        ui->maxGlideXSpinBox->setValue(maxGlideXSave);

        if (kbDev.checkFeedback(Check_RelativeH) == 1)
        {
            updateInProgress = true;
            ui->modulationZComboBox->setCurrentIndex(0);
            ui->nbAbsoluteLabel->setVisible(0);
            QApplication::processEvents();
            updateInProgress = false;
        }
        else
        {
            updateInProgress = true;
            ui->modulationZComboBox->setCurrentIndex(1);
            ui->nbAbsoluteLabel->setVisible(1);
            QApplication::processEvents();
            updateInProgress = false;
        }

        ui->ampZSpinBox->setMaximum(MAX_AMP);
        ui->ampZSlider->setMaximum(MAX_AMP);

        ui->invertZCheckBox->setChecked((kbDev.checkFeedback(Check_InvertZ) == 1));
        ui->stabZSlider->setValue(kbDev.checkFeedback(Check_StabZ));
        ui->ampZSlider->setValue(MAX_AMP - kbDev.checkFeedback(Check_AmpZ));

        if (!((kbDev.getID(VERSION) > 8) || ((kbDev.getID(VERSION) == 8) && (kbDev.getID(SUBVERSION) >= 3))))
            ui->smoothZSlider->setValue(MAX_SMOOTH - kbDev.checkFeedback(Check_SmoothZ));
        ui->filterZSlider->setValue(kbDev.checkFeedback(Check_FiltZ));
        minZSave = kbDev.checkFeedback(Check_MinZ);
        maxZSave = kbDev.checkFeedback(Check_MaxZ);
        ui->minHeightSpinBox->setValue(minZSave);
        ui->maxHeightSpinBox->setValue(maxZSave);

        updateMidiComboVisibility(Ports_Midi1);
        updateMidiModeWidgets(Ports_Midi1);
        updateEnableButtons(Ports_Midi1);
        //// Keyboard 1 ////
        keyboard[Ports_Midi1] = new Keyboard(ui->keyboardLayout, ui->startKeyComboBox->currentIndex(), ui->nKeysSpinBox->value(), this);
        connect(keyboard[Ports_Midi1], &Keyboard::keyClicked, this, [this] (int _key) {this->assignNoteToKey(Ports_Midi1, _key);});
        QVector <int> listN;
        for (int _i = 0 ; _i < saveNBeamsX ; _i++)
        {
            int tempNote = kbDev.checkFeedback(Check_NoteToPlay0 + _i);
            if (tempNote >= 0)
                listN.append(tempNote);
        }
        keyboard[Ports_Midi1]->updateNotesOnKeyboard(listN);

        if (nbPorts >= 3)
        {
            updateMidiComboVisibility(Ports_Midi3);
            updateMidiModeWidgets(Ports_Midi3);
            updateEnableButtons(Ports_Midi3);
            //// Keyboard 2 ////
            keyboard[Ports_Midi3] = new Keyboard(ui->keyboardLayout_2, ui->startKeyComboBox_2->currentIndex(), ui->nKeysSpinBox_2->value(), this);
            connect(keyboard[Ports_Midi3], &Keyboard::keyClicked, this, [this] (int _key) {this->assignNoteToKey(Ports_Midi3, _key);});
            QVector <int> listN3;
            for (int _i = 0 ; _i < saveNBeamsX ; _i++)
            {
                int tempNote = kbDev.checkFeedback(Check_NoteToPlay0_3P + _i);
                if (tempNote >= 0)
                    listN3.append(tempNote);
            }
            keyboard[Ports_Midi3]->updateNotesOnKeyboard(listN3);
        }

        if (nbPorts >= 4)
        {
            updateMidiComboVisibility(Ports_Midi4);
            updateMidiModeWidgets(Ports_Midi4);
            updateEnableButtons(Ports_Midi4);
            //// Keyboard 3 ////
            keyboard[Ports_Midi4] = new Keyboard(ui->keyboardLayout_3, ui->startKeyComboBox_3->currentIndex(), ui->nKeysSpinBox_3->value(), this);
            connect(keyboard[Ports_Midi4], &Keyboard::keyClicked, this, [this] (int _key) {this->assignNoteToKey(Ports_Midi4, _key);});
            QVector <int> listN4;
            for (int _i = 0 ; _i < saveNBeamsX ; _i++)
            {
                int tempNote = kbDev.checkFeedback(Check_NoteToPlay0_4P + _i);
                if (tempNote >= 0)
                    listN4.append(tempNote);
            }
            keyboard[Ports_Midi4]->updateNotesOnKeyboard(listN4);
        }


        updateEnabledMode();

        updateInProgress = true;
        for (int _i = 0; _i < Ports_Num; _i++)
        {
            for (int _ii = 0 ; _ii < MAX_NBEAMS ; _ii++)
            {
                if (Z0_ComboBox[_i][_ii])
                    Z0_ComboBox[_i][_ii]->setCurrentIndex(kbDev.checkFeedback(Check_NoteToPlay0 + (16 * _i) + _ii));
            }
        }

        for (int _ii = 0 ; _ii < MAX_NBEAMS ; _ii++)
        {
            angleSaveValue[_ii] = (double)(kbDev.checkFeedback(Check_BeamAngleListX0 + _ii) + ((kbDev.checkFeedback(Check_BeamAngleListXH0 + _ii) - 63) * 128)) / 10;
            angleDoubleSpinBox[_ii]->setValue(angleSaveValue[_ii]);
        }
        updateInProgress = false;
    }
    else
        retErr = 1;


    //updateAngleBoxVisibility();

    ////////////////////////////
    //////////// V8.02 /////////
    ////////////////////////////

    ui->centerHeightSpinBox->hide();

    if ((kbDev.getID(VERSION) > 8) || ((kbDev.getID(VERSION) == 8) && (kbDev.getID(SUBVERSION) >= 2)))
    {
        if (kbDev.checkFeedback(Check_CenterZ) >= 0)
        {
            ui->centerHeightSpinBox->show();
            centerZSave = kbDev.checkFeedback(Check_CenterZ);
            ui->centerHeightSpinBox->setValue(centerZSave);
        }
        else
            retErr = 1;
    }

    //////////// V8.03 /////////

    if ((kbDev.getID(VERSION) > 8) || ((kbDev.getID(VERSION) == 8) && (kbDev.getID(SUBVERSION) >= 3)))
    {
        ui->smoothZSpinBox->setMinimum(1);
        ui->smoothZSpinBox->setMaximum(MAX_SMOOTH803);
        ui->smoothZSlider->setMinimum(1);
        ui->smoothZSlider->setMaximum(MAX_SMOOTH803);
        ui->smoothZSlider->setValue(MAX_SMOOTH803 - qPow(kbDev.checkFeedback(Check_SmoothZ), 1 / POW_SMOOTHZ) + 1);

        if ((kbDev.checkFeedback(Check_SubPosX) >= 0) && (kbDev.checkFeedback(Check_SubWidthX) >= 0) && (kbDev.checkFeedback(Check_SubGlideX) >= 0) && (kbDev.checkFeedback(Check_SubHeight) >= 0) && (kbDev.checkFeedback(Check_ActiveSub) >= 0))
        {
            ui->subPosXSpinBox->setValue(kbDev.checkFeedback(Check_SubPosX));
            ui->subWidthXSpinBox->setValue(kbDev.checkFeedback(Check_SubWidthX));
            ui->subGlideXSpinBox->setValue(kbDev.checkFeedback(Check_SubGlideX));
            ui->subHeightSpinBox->setValue(kbDev.checkFeedback(Check_SubHeight));

            ui->activSubEffect11CheckBox->setChecked(kbDev.checkFeedback(Check_ActiveSub) & SubEffect_Midi11);
            ui->activSubEffect12CheckBox->setChecked(kbDev.checkFeedback(Check_ActiveSub) & SubEffect_Midi12);
            ui->activSubEffect31CheckBox->setChecked(kbDev.checkFeedback(Check_ActiveSub) & SubEffect_Midi31);
            ui->activSubEffect32CheckBox->setChecked(kbDev.checkFeedback(Check_ActiveSub) & SubEffect_Midi32);
            ui->activSubEffect41CheckBox->setChecked(kbDev.checkFeedback(Check_ActiveSub) & SubEffect_Midi41);
            ui->activSubEffect42CheckBox->setChecked(kbDev.checkFeedback(Check_ActiveSub) & SubEffect_Midi42);
        }
        else
            retErr = 1;
    }



    ///////////////////////////////////////////////////
    else if ((retErr == 0) && (optionWin == 1) && (lastParsedFirmware == -1)) //
        SendError(this, tr("Please, update your firmware to the last version (") + "8.03 " + tr("or above) to get all functionnalities:"
                                                        "\n> The firmware can be downloaded here: https://lightdiction.com/Ressources"
                                                        "\n> Or contact us at contact@lightdiction.com"), MainWindow_UpdateAll_FWUP, tr("Firmware outdated"));

////////////////////////

    if (retErr == 0)
    {
        ui->midiInComboBox->setEnabled(0);
        ui->midiOutComboBox->setEnabled(0);
        if (kbDev.getID(SERIAL) == 16383)
            ui->SNButton->setVisible(true);
        SendLog("KB2D Connected - SN: " + QString::number(kbDev.getID(SERIAL)).rightJustified(4, QChar('0')) + " - FW:"+ QString::number(kbDev.getID(VERSION)) + \
                "."+ QString::number(kbDev.getID(SUBVERSION)).rightJustified(2, QChar('0')));
        setStatus(tr("KB2D connected: Firmware version: ") + QString::number(kbDev.getID(VERSION)) + "."+ QString::number(kbDev.getID(SUBVERSION)).rightJustified(2, QChar('0')) + \
                  " - S/N: " + (QString::number(kbDev.getID(SERIAL)).rightJustified(4, QChar('0'))));

        if (optionWin == 1)
            QMessageBox::information(this, tr("KB2D connected - Device information"), "KB2D - S/N: " + QString::number(kbDev.getID(SERIAL)).rightJustified(4, QChar('0')) + \
                                     tr("\n\nFirmware version: ") + QString::number(kbDev.getID(VERSION)) + \
                                     "."+ QString::number(kbDev.getID(SUBVERSION)).rightJustified(2, QChar('0')) + \
                                     tr("\n\nFind the version notes and manual at:\nhttps://lightdiction.com/Ressources/"));
    }
    else
        SendError(this, tr("KB2D Parameters cannot be read."), MainWindow_UpdateAll_1_C);

    return retErr;
}

/*
void MainWindow::on_openMapButton_clicked()
{
    AngleMidiDialog angleMIDIDialog;
    angleMIDIDialog.setModal(true);
    angleMIDIDialog.exec();
}
*/

