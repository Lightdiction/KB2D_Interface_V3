#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QApplication>
#include <QFileDialog>
#include <QTimer>
#include <QElapsedTimer>
#include <QCloseEvent>
#include <QSettings>
#include <QGridLayout>
#include <QScreen>
//#include <QDebug>

#include "midi.h"
#include "comhw.h"
//#include "time.h"
#include "math.h"
#include "colordesign.h"
#include "errorEnum.h"
#include "comEnum.h"

#ifdef MAKE_DLL
#define LIB_EXPORT      Q_DECL_EXPORT
#else
#define LIB_EXPORT      Q_DECL_IMPORT
#endif

#define NUM_CONFIGS     128

//#define TEST_MODE     // Do not use TEST_MODE (for Lightdiction only), unless you want to kill your device. No support if you do that.

//#define ENABLE_AUTOSAVE
#define NO_MORE_BUTTONS

#define READ_COMM   0xB7


#define MAX_NBEAMS      16
#define MAX_ACCURACY    0x7F
#define MIN_ACCURACY    10
#define RANGE_ACCURACY (MAX_ACCURACY - MIN_ACCURACY)
#define MAX_FPS         130
#define MIN_FPS         50
#define RANGE_FPS (MAX_FPS - MIN_FPS)

enum MainPresetList : int
{
    Main_NBeamsX,
    Main_Fps,
    Main_Threshold,
    Main_DetSpeed,
    Main_DetSelectivity,
    Main_Deviation,

    Main_ModulationTypeZ,
    Main_NStepsZ,
    Main_InvertZ,
    Main_SmoothZ,
    Main_AttackZ,
    Main_AmplitudeZ,
    Main_StabZ,

    Main_AngleZ0X0,
    Main_AngleZ0X1,
    Main_AngleZ0X2,
    Main_AngleZ0X3,
    Main_AngleZ0X4,
    Main_AngleZ0X5,
    Main_AngleZ0X6,
    Main_AngleZ0X7,
    Main_AngleZ0X8,
    Main_AngleZ0X9,
    Main_AngleZ0X10,
    Main_AngleZ0X11,
    Main_AngleZ0X12,
    Main_AngleZ0X13,
    Main_AngleZ0X14,
    Main_AngleZ0X15,

    Main_NumParam
};

enum MidiPresetList : int
{
    Midi_DescNote,
    Midi_DescCC1,
    Midi_DescCC2,
    Midi_ChanNote,
    Midi_ChanCC1,
    Midi_ChanCC2,
    Midi_NoteNote,
    Midi_ControlCC1,
    Midi_ControlCC2,
    Midi_VelNote,
    Midi_ValCC1,
    Midi_ValCC2,
    Midi_Note0,
    Midi_Note1,
    Midi_Note2,
    Midi_Note3,
    Midi_Note4,
    Midi_Note5,
    Midi_Note6,
    Midi_Note7,
    Midi_Note8,
    Midi_Note9,
    Midi_Note10,
    Midi_Note11,
    Midi_Note12,
    Midi_Note13,
    Midi_Note14,
    Midi_Note15,

    Midi_NumParam
};

enum MappingList : int
{
    Map_Start,
    Map_Pause,
    Map_Restart,
    Map_Default,
    Map_SaveFlash,
    Map_LearnOne,
    Map_InvertX,
    Map_DetectionAssistant,
    Map_AutoCalibration,

    /// 16 Beams
    Map_Note1,

    Map_SendNote1 = Map_Note1 + MAX_NBEAMS,
    Map_EnableNotesOnOff,
    Map_DisableNotesOnOff,
    Map_EnablePitch,
    Map_DisablePitch,
    Map_EnableCC,
    Map_DisableCC,

    Map_NoteChanIndX,
    Map_NoteChanIndZ,
    Map_NoteChan,
    Map_NoteValueVarX,
    Map_NoteValueVarZ,
    Map_NoteValue,
    Map_NoteVelocityVarX,
    Map_NoteVelocityVarZ,
    Map_NoteVelocity,
    Map_PitchChanIndX,
    Map_PitchChanIndZ,
    Map_PitchChan,
    Map_PitchControlVarX,
    Map_PitchControlVarZ,
    Map_PitchControl,
    Map_PitchValueVarX,
    Map_PitchValueVarZ,
    Map_PitchValue,
    Map_CCChanIndX,
    Map_CCChanIndZ,
    Map_CCChan,
    Map_CCControlVarX,
    Map_CCControlVarZ,
    Map_CCControl,
    Map_CCValueVarX,
    Map_CCValueVarZ,
    Map_CCValue,

    Map_NBeamsX,
    Map_FPS,
    Map_DetThreshold,
    Map_DetSpeed,
    Map_SpeedSelectivity,
    Map_AngleDeviation,

    Map_ZModeRelative,
    Map_ZModeAbsolute,
    Map_ZInvertedMod,
    Map_ZRegularMod,
    Map_ZSmooth,
    Map_ZAttackFilter,
    Map_ZAmplitude,
    Map_ZStabilization,

    /// 128 Configs
    Map_MainPreset1,

    /// 128 Configs
    Map_MidiPreset1 = Map_MainPreset1 + NUM_CONFIGS,

    Map_NumParam = Map_MidiPreset1 + NUM_CONFIGS
};

enum GroupListId : int
{
    Group_DetXParam,
    Group_DetZParam,

    Group_AnglesParam,
    Group_MidiParam,
    Group_NotesParam,

    Group_MainPresets,
    Group_MidiPresets,

    Group_MainMapping,
    Group_MidiMapping,
    Group_DetXMapping,
    Group_DetZMapping,
    Group_MainPresetsMapping,
    Group_MidiPresetsMapping,

    Group_NumTotal
};

enum EnumLayouts : int
{
    Layout_Main,
    Layout_Midi,
    Layout_DetX,
    Layout_DetZ,
    Layout_MainPresets,
    Layout_MidiPresets,

    Layout_NumTotal
};


extern MidiDevIn harpIn;
extern MidiDevOut harpOut;
extern MidiDevIn extIn;
extern MidiDevOut extOut;

extern bool configDone;

extern QString saveNameMidi;
extern QString saveNameMidiIn;
extern int saveIndexMidiOut;
extern int saveIndexMidiIn;

extern bool cancelValue;
extern int extMidiIndexToLearn;

extern bool changeLanguage;

namespace Ui {
class MainWindow;
}

void qSleep(int timSleep);
void SendError(QWidget *parent, const QString &errMessage, int errorIndex, const QString &compMessage = "xxx", bool disp = true);
void SendLog(const QString &logMessage);


/*
 * ===================
 * Class MapSpinBox
 * ===================
 */
class MapSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    MapSpinBox(int min, int max, int mapInd, bool isController = false, QWidget *parent = nullptr);
    ~MapSpinBox();

protected:
    virtual void wheelEvent(QWheelEvent *event);
};


/*
 * ===================
 * Class MainWindow
 * ===================
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //LIB_EXPORT void qSleep(int timeToSleep);
    //LIB_EXPORT int  readCyFile(FILE *cyFile);
    //LIB_EXPORT int  readLegacyFile(FILE *legFile);

    //void qSleep(int timeToSleep);
    int  readCyFile(FILE *cyFile);
#ifndef GITX
    int  readLegacyFile(FILE *legFile);
#endif

    void setStatus(QString const& status);
    void setFlashText(QString const& text);

    void extInProc(int par1, int par2, int par3);
    void harpInProc();

    void updateMidiPortsList();
    void resetMidiPorts();

    void updateAngleBoxVisibility();
    void setDetActionsVisibility(bool enab, bool vis = true);
    void updateWidgetsDisplay();

    void autoSetDet();

    void quitProg();
    void flashProg();
    void saveInFlashFunc();
    void startFunc();
    void pauseFunc();
    void restartFunc();
    void learnOneAngle();
    void calculateAngles();
    void calibrateAngles();
    void invertX();
    void sendTestNote();

    void loadPresetMidi(int indPre);
    void InitializeMidiConfig();
    void UpdateMidiConfigList();

    void loadPresetMain(int indPre);
    void InitializeMainConfig();
    void UpdateMainConfigList();

    void InitializeMapping(bool setIni = true);
    void WriteTempMapping(int mapId = -1);
    void ReadTempMapping(int mapId = -1);

    void updateMidiMappingValues(int mapId = -1);

    void learnExtMIDI(int extInd);

    void updateAll(bool optionWin);

    void saveMappingFunction(void);
    void loadMappingFunction(void);
    void defaultMappingFunction(void);

private slots:
    void closeEvent(QCloseEvent* event);

    void checkModifications();
    void updatePresetsMidi() { UpdateMidiConfigList(); }    // Just an alias
    void savePresetMidi(int indPre, QString nameConfig);

    void updatePresetsMain() { UpdateMainConfigList(); }    // Just an alias
    void savePresetMain(int indPre, QString nameConfig);

    void on_actionQuit_triggered();

    void on_midiOutComboBox_currentIndexChanged(int index);
    void on_midiInComboBox_currentIndexChanged(int index);
    void on_extMidiInComboBox_currentIndexChanged(int index);
    void on_extMidiOutComboBox_currentIndexChanged(int index);

    void on_actionStart_triggered();
    void on_actionPause_triggered();

    void on_SaveParamButton_clicked();

    void on_actionSave_in_Memory_triggered();
    void on_actionRestore_Defaults_triggered();
    void on_actionLoad_Firmware_triggered();

    void on_nBeamsXComboBox_currentIndexChanged(int index);
    void on_nStepsZComboBox_currentIndexChanged(int index);

    void on_startButton_clicked();
    void on_pauseButton_clicked();

    void on_actionLoad_Firmware_2_0_triggered();
    void on_actionLoad_now_triggered();

    void on_readButton_clicked();

    void on_actionRead_All_triggered();
    void on_actionAbout_triggered();

    void on_minMaxCalibrationButton_clicked();
    void on_learnOneButton_clicked();

    void on_detLevelspinBox_editingFinished();
    void on_detSpeedspinBox_editingFinished();
    void on_detSelectivityspinBox_editingFinished();
    void on_FPSspinBox_editingFinished();
    void on_accuracySpinBox_editingFinished();

    void on_FPSSlider_valueChanged(int value);
    void on_detLevelSlider_valueChanged(int value);
    void on_detSpeedSlider_valueChanged(int value);
    void on_detSelectivitySlider_valueChanged(int value);
    void on_accuracySlider_valueChanged(int value);

    void on_invertXButton_clicked();

    void on_angleDoubleSpinBox_1_editingFinished();
    void on_angleDoubleSpinBox_2_editingFinished();
    void on_angleDoubleSpinBox_3_editingFinished();
    void on_angleDoubleSpinBox_4_editingFinished();
    void on_angleDoubleSpinBox_5_editingFinished();
    void on_angleDoubleSpinBox_6_editingFinished();
    void on_angleDoubleSpinBox_7_editingFinished();
    void on_angleDoubleSpinBox_8_editingFinished();
    void on_angleDoubleSpinBox_9_editingFinished();
    void on_angleDoubleSpinBox_10_editingFinished();
    void on_angleDoubleSpinBox_11_editingFinished();
    void on_angleDoubleSpinBox_12_editingFinished();
    void on_angleDoubleSpinBox_13_editingFinished();
    void on_angleDoubleSpinBox_14_editingFinished();
    void on_angleDoubleSpinBox_15_editingFinished();
    void on_angleDoubleSpinBox_16_editingFinished();

    void on_angleMinDoubleSpinBox_editingFinished();
    void on_angleMaxDoubleSpinBox_editingFinished();

    void on_actionUpdate_All_triggered();
    void on_actionRestart_triggered();

    void on_DescNoteComboBox_currentIndexChanged(int index);
    void on_DescCC1ComboBox_currentIndexChanged(int index);
    void on_DescCC2ComboBox_currentIndexChanged(int index);
    void on_ChanNoteComboBox_currentIndexChanged(int index);
    void on_ChanCC1ComboBox_currentIndexChanged(int index);
    void on_ChanCC2ComboBox_currentIndexChanged(int index);
    void on_NoteNoteComboBox_currentIndexChanged(int index);
    void on_ControlCC1ComboBox_currentIndexChanged(int index);
    void on_ControlCC2ComboBox_currentIndexChanged(int index);
    void on_VelNoteComboBox_currentIndexChanged(int index);
    void on_ValCC1ComboBox_currentIndexChanged(int index);
    void on_ValCC2ComboBox_currentIndexChanged(int index);

    void on_X0Z0_ComboBox_currentIndexChanged(int index);
    void on_X1Z0_ComboBox_currentIndexChanged(int index);
    void on_X2Z0_ComboBox_currentIndexChanged(int index);
    void on_X3Z0_ComboBox_currentIndexChanged(int index);
    void on_X4Z0_ComboBox_currentIndexChanged(int index);
    void on_X5Z0_ComboBox_currentIndexChanged(int index);
    void on_X6Z0_ComboBox_currentIndexChanged(int index);
    void on_X7Z0_ComboBox_currentIndexChanged(int index);
    void on_X8Z0_ComboBox_currentIndexChanged(int index);
    void on_X9Z0_ComboBox_currentIndexChanged(int index);
    void on_X10Z0_ComboBox_currentIndexChanged(int index);
    void on_X11Z0_ComboBox_currentIndexChanged(int index);
    void on_X12Z0_ComboBox_currentIndexChanged(int index);
    void on_X13Z0_ComboBox_currentIndexChanged(int index);
    void on_X14Z0_ComboBox_currentIndexChanged(int index);
    void on_X15Z0_ComboBox_currentIndexChanged(int index);

    void on_SNButton_clicked();

    void on_autosetButton_clicked();

    void on_thresholdButton_clicked();

    void on_stopCalButton_clicked();

    void on_extMapButton_clicked();

    void MapSpinUpdate(int mapSpinId = -1);
    void MapButtonClicked(int indexButton);

    void on_loadMappingPushButton_clicked();
    void on_saveMappingPushButton_clicked();
    void on_defaultMappingPushButton_clicked();

    void on_actionGo_to_mapping_settings_triggered();
    void on_actionSave_mapping_triggered();
    void on_actionLoad_mapping_triggered();
    void on_actionRestore_default_mapping_triggered();

    void on_actionInvert_X_Notes_triggered();

    void on_flashProgButton_clicked();

    void on_modulationZComboBox_currentIndexChanged(int index);
    void on_invertZCheckBox_toggled(bool checked);

    void on_smoothZSpinBox_editingFinished();
    void on_filterZSpinBox_editingFinished();
    void on_ampZSpinBox_editingFinished();
    void on_stabZSpinBox_editingFinished();

    void on_smoothZSlider_valueChanged(int value);
    void on_filterZSlider_valueChanged(int value);
    void on_ampZSlider_valueChanged(int value);
    void on_stabZSlider_valueChanged(int value);

    void on_actionStopCal_triggered();

    void on_midiConfigComboBox_currentIndexChanged(int index);
    void on_midiSaveAsButton_clicked();
    void on_midiManageButton_clicked();

    void on_mainSaveAsButton_clicked();

    void on_mainManageButton_clicked();

    void on_mainConfigComboBox_currentIndexChanged(int index);

    void on_actionDetection_Assistant_triggered();
    void on_actionAuto_Calibration_triggered();
    void on_actionLearn_One_Angle_triggered();

    void on_hardAmpComboBox_currentIndexChanged(int index);

    void on_actionEnglish_triggered();
    void on_actionFrench_triggered();

    void on_actionShow_Version_Notes_triggered();


    void on_releaseSlider_valueChanged(int value);

    void on_releaseSpinBox_editingFinished();

protected:
    Ui::MainWindow *ui;

    QWidget* groupList[Group_NumTotal];

private:

    bool eventFilter(QObject *obj, QEvent *event);

    // Beams
    QLabel* angleLabel[MAX_NBEAMS];
    QDoubleSpinBox* angleDoubleSpinBox[MAX_NBEAMS];
    QComboBox* Z0_ComboBox[MAX_NBEAMS];
    double angleSaveValue[MAX_NBEAMS] = {-10000};
    double angleSaveMin = -10000;
    double angleSaveMax = -10000;

    // Main Settings
    QString mainSettingsNames[Main_NumParam] = {0};

    // MIDI Settings
    QString midiSettingsNames[Midi_NumParam] = {0};
    QComboBox* midiComboBox[Midi_NumParam];

    // Mapping Settings
    QString mapNames[Map_NumParam] = {0};
    MapSpinBox* mapSpinBox[Map_NumParam][3];
    QPushButton* mapLearnButton[Map_NumParam];
    int mappingCommand[Map_NumParam][3] = {{-1}};
    QLabel* mapLabel[Map_NumParam];
    bool mapIsController[Map_NumParam] = {0};
    QGridLayout* mapGridLayout[Map_NumParam];

    QGridLayout* LayoutList[Layout_NumTotal];

    // States
    QTimer modifTimer;
    bool updateInProgress;
};

#endif // MAINWINDOW_H
