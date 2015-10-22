﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString RunProgram(const QString &path, const QStringList &arg);

private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonSettings_clicked();
    void on_pushButtonRefresh_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
