#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helper.h"
#include "settingsdialog.h"
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QInputDialog>
#include <QMessageBox>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->on_pushButtonRefresh_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRefresh_clicked()
{
    QString output = Helper::GetHostedNetworkStatus();

    ui->plainTextEditInfo->clear();
    ui->plainTextEditInfo->appendPlainText(output);
}

void MainWindow::on_pushButtonStart_clicked()
{
    QString output = Helper::StartHostedNetwork();

    output += Helper::GetHostedNetworkStatus();

    ui->plainTextEditInfo->clear();
    ui->plainTextEditInfo->appendPlainText(output);
}

void MainWindow::on_pushButtonStop_clicked()
{
    QString output = Helper::StopHostedNetwork();

    output += Helper::GetHostedNetworkStatus();

    ui->plainTextEditInfo->clear();
    ui->plainTextEditInfo->appendPlainText(output);
}

void MainWindow::on_pushButtonSettings_clicked()
{
    SettingsDialog dialog;
    QString output;

    if(dialog.exec() == QDialog::Rejected)
        return;

    if(dialog.isHostedNetworkEnabled())
    {
        output = Helper::SetHostedNetwork(dialog.getSSID(), dialog.getKey());
    }
    else
    {
        output = Helper::DisableHostedNetwork();
    }

    output += Helper::GetHostedNetworkStatus();
    ui->plainTextEditInfo->clear();
    ui->plainTextEditInfo->appendPlainText(output);
}
