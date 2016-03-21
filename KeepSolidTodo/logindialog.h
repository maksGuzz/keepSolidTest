#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
class QDialogButtonBox;
class QWidget;
class QLineEdit;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void sigLoginEntered(QString login, QString pwd);

public slots:
    void slClose();
    void slAcceptLogin();

private:
    QDialogButtonBox *m_buttons;
    QLineEdit *m_editPassword;
    QLineEdit *m_editLogin;
    void setupGui();

};

#endif // LOGINDIALOG_H
