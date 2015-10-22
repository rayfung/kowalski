#include "helper.h"
#include <QProcess>

QString Helper::RunProgram(const QString &path, const QStringList &arg)
{
    QProcess process;

    process.start(path, arg);
    if(!process.waitForStarted())
        return QString("Cannot start program: " + path);
    if(!process.waitForFinished())
        return QString("Program not responding: " + path);
    return QString::fromLocal8Bit(process.readAll());
}
