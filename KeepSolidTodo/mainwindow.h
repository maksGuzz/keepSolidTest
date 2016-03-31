#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariantMap>

namespace Ui {
class MainWindow;
}

class TreeModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setModel(TreeModel *model);

public slots:
    void slSetStausBarText(QString text);
    void slGetCredentials();
    void slLoggedIn();

signals:
    void sigLogin(QString login, QString pass);

private slots:
    void on_actionConnect_triggered();
    void setDetailsInfo(QVariantMap meta);

private:
    Ui::MainWindow *ui;
    TreeModel *m_tree;
};

#endif // MAINWINDOW_H
