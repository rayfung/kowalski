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

QString Helper::StartHostedNetwork()
{
    return Helper::RunProgram("netsh", QStringList() << "wlan" << "start" << "hostednetwork");
}

QString Helper::StopHostedNetwork()
{
    return Helper::RunProgram("netsh", QStringList() << "wlan" << "stop" << "hostednetwork");
}

QString Helper::GetHostedNetworkStatus()
{
    return Helper::RunProgram("netsh", QStringList() << "wlan" << "show" << "hostednetwork");
}

QString Helper::EnableHostedNetwork()
{
    return Helper::RunProgram("netsh", QStringList() << "wlan" << "set" << "hostednetwork" << "mode=allow");
}

QString Helper::DisableHostedNetwork()
{
    return Helper::RunProgram("netsh", QStringList() << "wlan" << "set" << "hostednetwork" << "mode=disallow");
}

QString Helper::SetHostedNetwork(const QString &ssid, const QString &key)
{
    return Helper::RunProgram("netsh", QStringList() << "wlan" << "set" << "hostednetwork"
                              << "mode=allow"
                              << QString("ssid=%1").arg(ssid)
                              << QString("key=%1").arg(key)
                              );
}

QString Helper::SetHostedNetworkSSID(const QString &ssid)
{
    return Helper::RunProgram("netsh", QStringList() << "wlan" << "set" << "hostednetwork" << QString("ssid=%1").arg(ssid));
}

QString Helper::SetHostedNetworkKey(const QString &key)
{
    return Helper::RunProgram("netsh", QStringList() << "wlan" << "set" << "hostednetwork" << QString("key=%1").arg(key));
}
