#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>

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
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    if(ui->checkBoxEnableHostedNetwork->isChecked())
    {
        if(ui->lineEditSSID->hasAcceptableInput() == false)
        {
            QMessageBox::information(this, QString("提示"), QString("SSID 至少需要两个字符，请重新输入！"));
            ui->lineEditSSID->selectAll();
            ui->lineEditSSID->setFocus();
            return;
        }
        if(ui->lineEditKey->hasAcceptableInput() == false)
        {
            QMessageBox::information(this, QString("提示"), QString("密码至少需要 8 个字符，请重新输入！"));
            ui->lineEditKey->selectAll();
            ui->lineEditKey->setFocus();
            return;
        }
    }

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

void SettingsDialog::on_checkBoxEnableHostedNetwork_clicked()
{
    bool hostedNetworkEnabled = ui->checkBoxEnableHostedNetwork->isChecked();
    ui->lineEditSSID->setEnabled(hostedNetworkEnabled);
    ui->lineEditKey->setEnabled(hostedNetworkEnabled);
}
