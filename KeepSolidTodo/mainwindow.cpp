#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"

#include <QDebug>
#include <QInputDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slSetStausBarText(QString text)
{
    statusBar()->showMessage(text);
}


void MainWindow::slGetCredentials()
{
    LoginDialog dialog(this);
    dialog.exec();
}


void MainWindow::on_actionConnect_triggered()
{
    qDebug() << "CONNECT";
    QString connTxt = "Connecting...";
    slSetStausBarText(connTxt);
    slGetCredentials();
}
