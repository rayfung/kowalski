#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    bool isHostedNetworkEnabled();
    QString getSSID();
    QString getKey();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
