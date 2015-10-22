﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
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

QString MainWindow::RunProgram(const QString &path, const QStringList &arg)
{
    QProcess process;

    process.start(path, arg);
    if(!process.waitForStarted())
        return QString("Cannot start program: " + path);
    if(!process.waitForFinished())
        return QString("Program not responding: " + path);
    return QString::fromLocal8Bit(process.readAll());
}

void MainWindow::on_pushButtonRefresh_clicked()
{
    QString output = RunProgram("netsh", QStringList() << "wlan" << "show" << "hostednetwork");

    ui->plainTextEditInfo->clear();
    ui->plainTextEditInfo->appendPlainText(output);
}

void MainWindow::on_pushButtonStart_clicked()
{
    QString output = RunProgram("netsh", QStringList() << "wlan" << "start" << "hostednetwork");

    ui->plainTextEditInfo->clear();
    ui->plainTextEditInfo->appendPlainText(output);
}

void MainWindow::on_pushButtonStop_clicked()
{
    QString output = RunProgram("netsh", QStringList() << "wlan" << "stop" << "hostednetwork");

    ui->plainTextEditInfo->clear();
    ui->plainTextEditInfo->appendPlainText(output);
}

void MainWindow::on_pushButtonSettings_clicked()
{
    QString ssid = QInputDialog::getText(this, QString("设置 SSID"), QString("请输入热点的 SSID"),
                                         QLineEdit::Normal, QString(), 0, 0, Qt::ImhLatinOnly);
    if(ssid.trimmed().isEmpty())
        return;

    QString passphrase = QInputDialog::getText(this, QString("设置密码"), QString("请输入密码（8 至 32 个字符）"),
                                               QLineEdit::Password, QString(), 0, 0, Qt::ImhLatinOnly);
    if(passphrase.isNull())
        return;
    if(passphrase.length() < 8 || passphrase.length() > 32)
    {
        QMessageBox::information(this, QString("设置密码"), QString("密码不正确！"));
        return;
    }

    QString output = RunProgram("netsh", QStringList() << "wlan" << "set" << "hostednetwork"
                                << "mode=allow"
                                << QString("ssid=%1").arg(ssid)
                                << QString("key=%1").arg(passphrase)
                                );
    ui->plainTextEditInfo->clear();
    ui->plainTextEditInfo->appendPlainText(output);
}
