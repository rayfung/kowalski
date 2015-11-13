#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QStringList>

class Helper
{
public:
    static QString RunProgram(const QString &path, const QStringList &arg);
    static QString StartHostedNetwork();
    static QString StopHostedNetwork();
    static QString GetHostedNetworkStatus();
    static QString EnableHostedNetwork();
    static QString DisableHostedNetwork();
    static QString SetHostedNetwork(const QString &ssid, const QString &key);
    static QString SetHostedNetworkSSID(const QString &ssid);
    static QString SetHostedNetworkKey(const QString &key);

private:
    Helper();
};

#endif // HELPER_H
