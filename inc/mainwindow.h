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
#include "math.h"
#include "colordesign.h"
#include "errorEnum.h"
#include "comEnum.h"
#include "utils.h"
#include "grnotes.h"
#include "grextmapping.h"
#include "keyboard.h"
#include "grpresets.h"
#include "mididevices.h"

#ifdef MAKE_DLL
#define LIB_EXPORT      Q_DECL_EXPORT
#else
#define LIB_EXPORT      Q_DECL_IMPORT
#endif

//#define TEST_MODE     // Do not use TEST_MODE (for Lightdiction only), unless you want to kill your device. No support if you do that.



_ENUM_(GroupListId, int)
{
    Group_KB2DPorts,
    Group_MainPresets,

    Group_AnglesParam,
    Group_AngleDetails,

    Group_GlobalMidiAngle,
    Group_MidiTab,

    Group_Assign,
    Group_NotesSetWidget,
    Group_Enable,
    Group_AllMidi,
    Group_NotesMidi,
    Group_CC1Midi,
    Group_CC2Midi,
    Group_NotesParam,
    Group_KeyboardSetWidget,
    Group_NotesScroll,
    Group_Effect0,
    Group_Effect1,
    Group_Effect2,

    Group_MainWidget,
    Group_DetXParam,
    Group_PosXParam,
    Group_DetZParam,

    Group_Assign_2,
    Group_NotesSetWidget_2,
    Group_Enable_2,
    Group_AllMidi_2,
    Group_NotesMidi_2,
    Group_CC1Midi_2,
    Group_CC2Midi_2,
    Group_NotesParam_2,
    Group_KeyboardSetWidget_2,
    Group_NotesScroll_2,
    Group_Effect0_2,
    Group_Effect1_2,
    Group_Effect2_2,

    Group_Assign_3,
    Group_NotesSetWidget_3,
    Group_Enable_3,
    Group_AllMidi_3,
    Group_NotesMidi_3,
    Group_CC1Midi_3,
    Group_CC2Midi_3,
    Group_NotesParam_3,
    Group_KeyboardSetWidget_3,
    Group_NotesScroll_3,
    Group_Effect0_3,
    Group_Effect1_3,
    Group_Effect2_3,

    Group_NumTotal
};
/*
_ENUM_(ModeList, int)
{
    Mode_BasicHarp,
    Mode_HarpHeight,
    Mode_Tracking,
    Mode_Theremin,

    Mode_NumTotal
};*/


_ENUM_(TabList, int)
{
    Tab_KB2DSettings,
    Tab_ExternalMIDIMapping,
    Tab_FirmwareUpdater,

    Tab_NumTabs
};


extern MidiDevIn harpIn;
extern MidiDevOut harpOut;
extern MidiDevIn extIn;
extern MidiDevOut extOut;
extern MidiDevIn throughIn;
extern MidiDevOut throughOut;

extern bool configDone;
extern bool testMode;

extern QString saveNameMidi;
extern QString saveNameMidiIn;
extern int saveIndexMidiOut;
extern int saveIndexMidiIn;

extern bool cancelValue;

extern bool changeLanguage;

namespace Ui {
class MainWindow;
}


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

    // Firmware Updater
    int  readCyFile(FILE *cyFile);
#ifndef GITX
    int  readLegacyFile(FILE *legFile);
#endif

    void exitFUpdater();
    bool initializeFU();
    void updateProgressBar(int currentValue, int valMax = -1);
    bool checkNewVersions();
    bool autoStartFUAndParse();

    // General Display & Interface controls
    void setStatus(QString const& status);
    void setFlashText(QString const& text);
    void updateAngleBoxVisibility();
    void setDetActionsVisibility(bool enab, bool vis = true);
    void quitProg();
    int updateAll(bool optionWin);

    void disableAllGroups(bool hideToo = false);
    void enableAllGroups();
    void saveCurrentDisplay();
    void setEnableGroup(int indexGroup, bool state, bool hideToo = false);
    void restoreDisplay();
    void saveCurrentDisplayAndDisable(bool hideToo = false) { saveCurrentDisplay(); disableAllGroups(hideToo); }
    void updateEnabledMode();
    void repaintAssignButtons();

    // Communication
    void extInProc(int par1, int par2, int par3);
    void harpInProc();

    void updateMidiPortsList(bool forceDefault = false, QString nameKbIn = "", QString nameKbOut = "", QString nameExtIn = "", \
                             QString nameExtOut = "", QString nameThroughIn = "", QString nameThroughOut = "");
    void connectThroughPorts(QString nameThroughIn = "", QString nameThroughOut = "");
    void resetMidiPorts();
    void testConnectedDevices();

    // General Device Control
    bool flashProg(QString fileName = "");
    void saveInFlashFunc();
    void startFunc();
    void pauseFunc();
    void restartFunc();

    // Photo Detection
    void autoSetDet();

    // Angles
    void learnOneAngle(int beamInd);
    void calculateAngles();
    void calibrateAngles();

    // Notes
    void invertX();
    void initializeMidiCombos();
    void initializeZ0Combos();
    void updateEnableButtons(int nPort);
    void updateMidiComboVisibility(int nPort);
    void updateMidiModeWidgets(int nPort);

    // Presets

    void loadPresetMain(int indPre);
    void InitializeMainConfig();
    void UpdateMainConfigList();

    // Mapping
    void InitializeMapping(bool setIni = true);
    void WriteTempMapping(int mapId = -1);
    void ReadTempMapping(int mapId = -1);
    void updateMidiMappingValues(int mapId = -1);
    void learnExtMIDI(int extInd);

    void saveMappingFunction(void);
    void loadMappingFunction(void);
    void defaultMappingFunction(void);

    // Keyboard

signals:
    void oneAngleCalibrated(int beamIndex);

private slots:
    void closeEvent(QCloseEvent* event);
    void firstLoad();

    void checkModifications();

    void updatePresetsMain() { UpdateMainConfigList(); }    // Just an alias
    void savePresetMain(int indPre, QString nameConfig, bool incDet, bool incHeight, bool incAngles, bool incNotes, bool incVarsX);

    void on_actionQuit_triggered();

    void on_midiOutComboBox_currentIndexChanged(int index);
    void on_midiInComboBox_currentIndexChanged(int index);
    void on_extMidiInComboBox_currentIndexChanged(int index);
    void on_extMidiOutComboBox_currentIndexChanged(int index);

    void on_actionStart_triggered();
    void on_actionPause_triggered();

    void on_actionSave_in_Memory_triggered();
    void on_actionRestore_Defaults_triggered();
    void on_actionLoad_Firmware_triggered();

    void on_nBeamsXComboBox_currentIndexChanged(int index);

    void on_actionLoad_Firmware_2_0_triggered();
    void on_actionLoad_now_triggered();

    void on_actionAbout_triggered();

    // X Detection parameters
    void on_detLevelspinBox_editingFinished();
    void on_minTimeSpinBox_editingFinished();
    void on_maxTimeSpinBox_editingFinished();
    void on_FPSspinBox_editingFinished();

    void on_FPSSlider_valueChanged(int value);
    void on_detLevelSlider_valueChanged(int value);
    void on_minTimeSlider_valueChanged(int value);
    void on_maxTimeSlider_valueChanged(int value);

    void on_actionDetection_Assistant_triggered();
    void on_actionLearn_All_One_by_One_triggered();
    void on_actionLearn_One_Angle_triggered();
    void on_actionAuto_Calibration_triggered();
    void on_hardAmpComboBox_currentIndexChanged(int index);
    void on_releaseSlider_valueChanged(int value);
    void on_releaseSpinBox_editingFinished();

    // VarsX Settings
    void on_invertWidthXCheckBox_toggled(bool checked);
    void on_invertPosXCheckBox_toggled(bool checked);
    void on_invertGlideXCheckBox_toggled(bool checked);
    void on_stabGlideSlider_valueChanged(int value);
    void on_stabGlideSpinBox_editingFinished();
    void on_minPosXSpinBox_editingFinished();
    void on_maxPosXSpinBox_editingFinished();
    void on_minWidthXSpinBox_editingFinished();
    void on_maxWidthXSpinBox_editingFinished();
    void on_minGlideXSpinBox_editingFinished();
    void on_maxGlideXSpinBox_editingFinished();
    void on_subPosXSpinBox_editingFinished();
    void on_subWidthXSpinBox_editingFinished();
    void on_subGlideXSpinBox_editingFinished();

    void on_activSubEffect11CheckBox_toggled(bool checked);
    void on_activSubEffect12CheckBox_toggled(bool checked);
    void on_activSubEffect31CheckBox_toggled(bool checked);
    void on_activSubEffect32CheckBox_toggled(bool checked);
    void on_activSubEffect41CheckBox_toggled(bool checked);
    void on_activSubEffect42CheckBox_toggled(bool checked);

    // Angles
    void multiAngleSpinBox_editing(int nIndex);
    void on_accuracySpinBox_editingFinished();
    void on_enableAngFilterCheckBox_toggled(bool checked);

    // Notes and MIDI Modes Parameters
    void sendMidiModeValues(int nPort, int nMode, int nMidi, int value = 0);
    void comboNoteSelected(int nPort, int indCombo, int index);

    void on_enableNotesOnOffButton_clicked();
    void on_enableEffect1Button_clicked();
    void on_enableEffect2Button_clicked();
    void on_DescCC1ComboBox_currentIndexChanged(int index);
    void on_DescCC2ComboBox_currentIndexChanged(int index);
    void on_enableNotesOnOffButton_2_clicked();
    void on_enableEffect1Button_2_clicked();
    void on_enableEffect2Button_2_clicked();
    void on_DescCC1ComboBox_2_currentIndexChanged(int index);
    void on_DescCC2ComboBox_2_currentIndexChanged(int index);
    void on_enableNotesOnOffButton_3_clicked();
    void on_enableEffect1Button_3_clicked();
    void on_enableEffect2Button_3_clicked();
    void on_DescCC1ComboBox_3_currentIndexChanged(int index);
    void on_DescCC2ComboBox_3_currentIndexChanged(int index);

    void enableButtonClicked(int nPort, int nIndex);
    void assignButtonClicked(int nPort, int nIndex);
    void assignAllButtonClicked(int nPort);
    void toneShiftClicked(int nPort, int typeShift);
    void notePresetClicked(int nPort, int user);
    void saveNotesDialogClicked(int nPort);
    void manageNotesDialogClicked(int nPort);
    void notesPresetComboChanged(int nPort, int index);

    void updateNotesPresetList();
    void loadNotesPreset(int nPort, int nPreset);
    void loadNotesUser(int nPort, QString userName);
    void saveNotesPreset(int nPort, int indPreset, QString custName);
    void saveNotesUser(int nPort, int numUser);

    // Keyboard
    void assignNoteToKey(int portNum, int noteToAssign);

    void on_nKeysSpinBox_editingFinished();
    void on_startKeyComboBox_currentIndexChanged(int index);
    void on_sendOnClickCheckBox_toggled(bool checked);

    void on_nKeysSpinBox_2_editingFinished();
    void on_startKeyComboBox_2_currentIndexChanged(int index);
    void on_sendOnClickCheckBox_2_stateChanged(int arg1);

    void on_nKeysSpinBox_3_editingFinished();
    void on_startKeyComboBox_3_currentIndexChanged(int index);
    void on_sendOnClickCheckBox_3_stateChanged(int arg1);


    void on_SNButton_clicked();

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

    // Height detection
    void on_minHeightSpinBox_editingFinished();
    void on_centerHeightSpinBox_editingFinished();
    void on_maxHeightSpinBox_editingFinished();

    void on_smoothZSpinBox_editingFinished();
    void on_filterZSpinBox_editingFinished();
    void on_ampZSpinBox_editingFinished();
    void on_stabZSpinBox_editingFinished();
    void on_subHeightSpinBox_editingFinished();

    void on_smoothZSlider_valueChanged(int value);
    void on_filterZSlider_valueChanged(int value);
    void on_ampZSlider_valueChanged(int value);
    void on_stabZSlider_valueChanged(int value);

    void on_actionStopCal_triggered();

    // Presets
    void on_mainSaveAsButton_clicked();
    void on_mainManageButton_clicked();
    void on_mainConfigComboBox_currentIndexChanged(int index);

    // Global
    void on_actionEnglish_triggered();
    void on_actionFrench_triggered();
    void on_actionShow_Version_Notes_triggered();
    void on_actionUpdate_All_triggered();
    void on_actionRestart_triggered();

    void on_exitUpdaterButton_clicked();

    void on_nbPortsCombo_currentIndexChanged(int index);
    void retryConnection(int attempts = 0);

    // Modules
    void on_harpEnabPushButton_clicked();
    void on_harpHeightEnabPushButton_clicked();
    void on_trackingEnabPushButton_clicked();
    void on_thereminEnabPushButton_clicked();

    void on_actionMidi_configuration_triggered();

protected:
    Ui::MainWindow *ui;

    QWidget* groupList[Group_NumTotal] = {nullptr};

private:

    bool eventFilter(QObject *obj, QEvent *event);
    //void resizeEvent(QResizeEvent* event);

    // Notes and Midi Modes
    QComboBox* midiSelection_Combo[Ports_Num][ModeActiv_NumModes][ValSelection_NumCombo] = {{{nullptr}}};

    // Beams
    QPushButton* angleLearn[MAX_NBEAMS] = {nullptr};
    QDoubleSpinBox* angleDoubleSpinBox[MAX_NBEAMS] = {nullptr};
    double angleSaveValue[MAX_NBEAMS] = {-10000};

    // Main Settings
    QString mainSettingsNames[Main_NumParam] = {0};

    // Vars X
    int stabGlideSave = -1;
    int minPosXSave = -1;
    int maxPosXSave = -1;
    int minWidthXSave = -1;
    int maxWidthXSave = -1;
    int minGlideXSave = -1;
    int maxGlideXSave = -1;
    int subPosXSave = -1;
    int subWidthXSave = -1;
    int subGlideXSave = -1;

    // Height Z
    int minZSave = -1;
    int centerZSave = -1;
    int maxZSave = -1;
    int subZSave = -1;

    // Mapping Settings
    QString mapNames[Map_NumParam][2] = {{""}};
    MapSpinBox* mapSpinBox[Map_NumParam][3] = {{nullptr}};
    QPushButton* mapLearnButton[Map_NumParam] = {nullptr};
    int mappingCommand[Map_NumParam][3] = {{-1}};
    QLabel* mapLabel[Map_NumParam] = {nullptr};
    bool mapIsController[Map_NumParam] = {false};
    QGridLayout* mapGridLayout[Map_NumParam] = {nullptr};

    QGridLayout* LayoutList[Layout_NumTotal] = {nullptr};

    // Notes
    QComboBox* Z0_ComboBox[Ports_Num][MAX_NBEAMS] = {{nullptr}};
    QLabel *LabelZ0Combo[Ports_Num][MAX_NBEAMS] = {{nullptr}};
    QPushButton* enableButton[Ports_Num][MAX_NBEAMS] = {{nullptr}};
    QPushButton* assignButton[Ports_Num][MAX_NBEAMS] = {{nullptr}};
    QPushButton* assignAllButton[Ports_Num] = {nullptr};
    bool assignAllActivated[Ports_Num] = {false};
    QPushButton* toneShiftButton[Ports_Num][ToneShift_NumTotal] = {{nullptr}};
    QPushButton* notePresetButton[Ports_Num][NotePreset_NumTotal] = {{nullptr}};
    QPushButton* saveNotesDialogButton[Ports_Num] = {nullptr};
    QPushButton* manageNotesDialogButton[Ports_Num] = {nullptr};
    QComboBox* notesPresetCombos[Ports_Num] = {nullptr};

    // Keyboard
    Keyboard* keyboard[Ports_Num] = {nullptr};

    // States
    QTimer modifTimer;
    QTimer softwareConnect;
    int lastParsedFirmware = -1;
    QString newVersionDesc = "";

    bool updateInProgress = false;
    bool groupActivated[Group_NumTotal] = {true};
    bool groupHidden[Group_NumTotal] = {false};
    int beamsEnabled[Ports_Num] = {0};
    int enabState[Ports_Num] = {0};
    int lastMidiMode[Ports_Num][2] = {{0}};
    bool connectionReq = true;
    bool fuUpdateRequested = false;

    // Tabs
    QString listNameTabs[Tab_NumTabs];

    // Module Enabled
    //int modeEnabled = Mode_BasicHarp;
};

#endif // MAINWINDOW_H
