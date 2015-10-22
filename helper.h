#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QStringList>

class Helper
{
public:
    static QString RunProgram(const QString &path, const QStringList &arg);

private:
    Helper();
};

#endif // HELPER_H
