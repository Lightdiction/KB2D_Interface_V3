#ifndef UTILS_H
#define UTILS_H


#include <QApplication>
#include <QFileDialog>
#include <QTimer>
#include <QElapsedTimer>
#include <QGridLayout>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QString>
#include <QWidget>
#include <QTabWidget>

#define _ENUM_(name, base) enum name : base

#define LAST_VERSION    350

#define NUM_CONFIGS     128
#define MAX_NBEAMS      16

#define MAX_ACCURACY    0x7F
#define MIN_ACCURACY    10
#define RANGE_ACCURACY (MAX_ACCURACY - MIN_ACCURACY)
#define MAX_FPS         130
#define MIN_FPS         50
#define RANGE_FPS (MAX_FPS - MIN_FPS)

#define MAX_SMOOTH      17
#define MAX_AMP         40

#define NAME_NOTES_PRESETS   "_kb2dNotes.preset"
#define NAME_NOTES_USER   "_Notes.preset"
#define MAX_PRESETS_NOTES   128



#define _TR(a) QWidget::tr(a)


void qSleep(int timSleep);
void SendError(QWidget *parent, const QString &errMessage, int errorIndex, const QString &compMessage = "xxx", bool disp = true);
void SendLog(const QString &logMessage);
void clearLayout(QLayout* layout, bool deleteWidgets = true);
int  GetTabIndex(QTabWidget *tabWidget, QString tabName);

#endif // UTILS_H
