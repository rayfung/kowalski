#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QSettings>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QRegExp ssidRX("^[A-Za-z0-9_]{2,32}$");
    QValidator *ssidValidator = new QRegExpValidator(ssidRX);
    ui->lineEditSSID->setValidator(ssidValidator);

    QRegExp keyRX("^[\\0040-\\0176]{8,32}$");
    QValidator *keyValidator = new QRegExpValidator(keyRX);
    ui->lineEditKey->setValidator(keyValidator);

    LoadSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    if(ui->checkBoxEnableHostedNetwork->isChecked())
    {
        bool ignoreSSID = false;
        bool ignoreKey = false;

        if(ui->lineEditSSID->text().isEmpty() && ui->lineEditKey->text().isEmpty() == false)
        {
            if(QMessageBox::question(this, QString("提示"), QString("SSID 为空，表示不更改 SSID，是否继续？")) == QMessageBox::Yes)
                ignoreSSID = true;
            else
                return;
        }
        else if(ui->lineEditSSID->text().isEmpty() == false && ui->lineEditKey->text().isEmpty())
        {
            if(QMessageBox::question(this, QString("提示"), QString("密码为空，表示不更改密码，是否继续？")) == QMessageBox::Yes)
                ignoreKey = true;
            else
                return;
        }

        if(ignoreSSID == false && ui->lineEditSSID->hasAcceptableInput() == false)
        {
            QMessageBox::information(this, QString("提示"), QString("SSID 至少需要两个字符，请重新输入！"));
            ui->lineEditSSID->selectAll();
            ui->lineEditSSID->setFocus();
            return;
        }
        if(ignoreKey == false && ui->lineEditKey->hasAcceptableInput() == false)
        {
            QMessageBox::information(this, QString("提示"), QString("密码至少需要 8 个字符，请重新输入！"));
            ui->lineEditKey->selectAll();
            ui->lineEditKey->setFocus();
            return;
        }
    }

    SaveSettings();
    this->accept();
}

bool SettingsDialog::isHostedNetworkEnabled()
{
    return ui->checkBoxEnableHostedNetwork->isChecked();
}

QString SettingsDialog::getSSID()
{
    return ui->lineEditSSID->text();
}

QString SettingsDialog::getKey()
{
    return ui->lineEditKey->text();
}

void SettingsDialog::LoadSettings()
{
    QSettings settings(QString("Ray Fung"), QString("Kowalski"));

    ui->checkBoxEnableHostedNetwork->setChecked(settings.value(QString("enabled"), false).toBool());
    ui->lineEditSSID->setText(settings.value(QString("ssid"), QString("Kowalski")).toString());
}

void SettingsDialog::SaveSettings()
{
    QSettings settings(QString("Ray Fung"), QString("Kowalski"));

    settings.setValue(QString("enabled"), ui->checkBoxEnableHostedNetwork->isChecked());
    if(ui->lineEditSSID->text().isEmpty() == false)
        settings.setValue(QString("ssid"), ui->lineEditSSID->text());
}

void SettingsDialog::on_checkBoxEnableHostedNetwork_toggled(bool /* checked */)
{
    bool hostedNetworkEnabled = ui->checkBoxEnableHostedNetwork->isChecked();
    ui->lineEditSSID->setEnabled(hostedNetworkEnabled);
    ui->lineEditKey->setEnabled(hostedNetworkEnabled);
}
