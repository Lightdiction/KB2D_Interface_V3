
#include "inc/utils.h"


int catchCommIndex = -1;
unsigned char catchPar1 = 0;
unsigned char catchPar2 = 0;
unsigned char catchPar3 = 0;

void clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}


void qSleep(int timeToSleep)
{
    QElapsedTimer tim;
    tim.start();
    while(tim.elapsed() < timeToSleep)
        QApplication::processEvents();
}

/*
 * ==============================
 * Send Error to User and
 * Write error in log file
 * ==============================
 */
void SendError(QWidget *parent, const QString &errMessage, int errorIndex, const QString &compMessage, bool disp)
{
    if (errorIndex > 10000)
    {
        if (disp)
            QMessageBox::critical(parent, QObject::tr("Error"), errMessage + QObject::tr("\n\nError code: ") + QString::number(errorIndex));
    }
    else
    {
        if (disp)
            QMessageBox::warning(parent, "Warning", errMessage + "\n\nWarning code: " + QString::number(errorIndex));
    }

    // Check and create logs directory
    QDir dir("logs");
    if (!dir.exists())
        dir.mkpath(".");
    // Log File
    QFile logFile("logs/" + QDateTime::currentDateTime().toString("yyMM") + "_kb" + QString::number(LAST_VERSION) + ".log");
    logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    if (logFile.isOpen())
    {
        if (compMessage == "xxx")
        {
            QTextStream outStream(&logFile);
            outStream << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " \
                      << "Err " << QString::number(errorIndex) << " _ " << catchCommIndex << " - "
                      << QString::number(catchPar1, 16).toUpper() << " " << QString::number(catchPar2, 16).toUpper() << " " << QString::number(catchPar3, 16).toUpper()
                      << " _ " << errMessage << "\n";
            qDebug() << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " \
                      << "Err " << QString::number(errorIndex) << " _ " << catchCommIndex << " - "
                      << QString::number(catchPar1, 16).toUpper() << " " << QString::number(catchPar2, 16).toUpper() << " " << QString::number(catchPar3, 16).toUpper()
                      << " _ " << errMessage << "\n";
        }
        else
        {
            QTextStream outStream(&logFile);
            outStream << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " \
                      << "Err " << QString::number(errorIndex) << " _ " << catchCommIndex << " - "
                      << QString::number(catchPar1, 16).toUpper() << " " << QString::number(catchPar2, 16).toUpper() << " " << QString::number(catchPar3, 16).toUpper()
                      << " _ " << compMessage << "\n";
            qDebug() << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " \
                      << "Err " << QString::number(errorIndex) << " _ " << catchCommIndex << " - "
                      << QString::number(catchPar1, 16).toUpper() << " " << QString::number(catchPar2, 16).toUpper() << " " << QString::number(catchPar3, 16).toUpper()
                      << " _ " << compMessage << "\n";
        }
        logFile.close();
    }
    else
        qDebug() << "Can't open log file";
}

/*
 * ==============================
 * Write information in log file
 * ==============================
 */
void SendLog(const QString &logMessage)
{
    // Check and create logs directory
    QDir dir("logs");
    if (!dir.exists())
        dir.mkpath(".");
    // Log File
    QFile logFile("logs/" + QDateTime::currentDateTime().toString("yyMM") + "_kb" + QString::number(LAST_VERSION) + ".log");
    logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    if (logFile.isOpen())
    {
        QTextStream outStream(&logFile);
        outStream << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " << logMessage << "\n";
        qDebug() << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " << logMessage << "\n";
        logFile.close();
    }
    else
        qDebug() << "Can't open log file";
}

int GetTabIndex(QTabWidget *tabWidget, QString tabName)
{
    for (int _i = 0 ; _i < tabWidget->count() ; _i++)
    {
        if (tabWidget->tabText(_i) == tabName)
            return _i;
    }
    return -1;
}
