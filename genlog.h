#ifndef GENLOG_H
#define GENLOG_H

#define LOGSIZE 1024 * 100 //log size in bytes
#define LOGFILES 10

#include <QObject>
#include <QString>
#include <QDebug>
#include <QDate>
#include <QTime>

namespace GENLOG
{
    const QString logFolderName = "logs";
    bool initLogging();
    void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString& msg);
}

#endif // GENLOG_H
