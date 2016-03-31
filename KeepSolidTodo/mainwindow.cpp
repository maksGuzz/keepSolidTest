#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "treemodel.h"

#include <QDebug>
#include <QInputDialog>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //emit sigLogin(QString(), QString());
    //view.setModel(&model);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModel(TreeModel *model)
{
    ui->treeView->setModel(model);
    m_tree = model;
    connect(ui->treeView, SIGNAL(pressed(QModelIndex)), m_tree, SLOT(activated(QModelIndex)));
    connect(m_tree, SIGNAL(setInfo(QVariantMap)), this, SLOT(setDetailsInfo(QVariantMap)));
}


void MainWindow::slSetStausBarText(QString text)
{
    statusBar()->showMessage(text);
}


void MainWindow::slGetCredentials()
{
    LoginDialog dialog(this);
    connect(&dialog, SIGNAL(sigLoginEntered(QString,QString)), this, SIGNAL(sigLogin(QString,QString)));
    dialog.exec();
}

void MainWindow::slLoggedIn()
{
    qDebug() << "Logged In!";
}


void MainWindow::on_actionConnect_triggered()
{
    qDebug() << "CONNECT";
    slSetStausBarText("start");

    QString connTxt = "Connecting...";
    slSetStausBarText(connTxt);
    slGetCredentials();
}

QStringList parseMap(const QVariantMap &map)
{
    QStringList l;
    foreach (QString k, map.keys())
    {
        qDebug() << "typename:" << map[k].typeName();
        if(QString(map[k].typeName()) == "QVariantMap")
        {
            qDebug() << "recurse";
            l << "--" + k;
            l.append(parseMap(map[k].toMap()));
        }
        else
        {
            QString s = k + ": " + map[k].toString();
            l << s;
        }
    }
    return l;
}


void MainWindow::setDetailsInfo(QVariantMap meta)
{
    qDebug() << "update detailsinfo";
    QListWidget *di = ui->listWidget;
    di->clear();
    di->addItems(parseMap(meta));
}
