#include "logindialog.h"


#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    setupGui();
    setWindowTitle( tr("User Login") );
    setModal( true );
}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::slClose()
{
    qDebug() << "close";
    close();
}

void LoginDialog::slAcceptLogin()
{
    qDebug() << "Login" << m_editLogin->text() << ":" << m_editPassword->text();
    emit sigLoginEntered(m_editLogin->text(), m_editPassword->text());
    close();
}

void LoginDialog::setupGui()
{
    QGridLayout *formGridLayout = new QGridLayout( this );

    m_editLogin = new QLineEdit( this );
    m_editLogin->setEchoMode(QLineEdit::Normal);// QLineEdit::Password );
    m_editPassword = new QLineEdit( this );
    m_editPassword->setEchoMode(QLineEdit::Normal);// QLineEdit::Password );

    // initialize the labels
    QLabel *labelUsername = new QLabel( this );
    QLabel *labelPassword = new QLabel( this );
    labelUsername->setText( tr( "Username" ) );
    labelUsername->setBuddy( m_editLogin );
    labelPassword->setText( tr( "Password" ) );
    labelPassword->setBuddy( m_editPassword );

    // initialize buttons
    m_buttons = new QDialogButtonBox( this );
    m_buttons->addButton( QDialogButtonBox::Ok );
    m_buttons->addButton( QDialogButtonBox::Cancel );
    m_buttons->button( QDialogButtonBox::Ok )->setText( tr("Login") );
    m_buttons->button( QDialogButtonBox::Cancel )->setText( tr("Abort") );

    // connects slots
    connect( m_buttons->button( QDialogButtonBox::Cancel ), SIGNAL (clicked()), this, SLOT (slClose()));
    connect( m_buttons->button( QDialogButtonBox::Ok ),SIGNAL (clicked()),this,SLOT (slAcceptLogin()));

    // place components into the dialog
    formGridLayout->addWidget( labelUsername, 0, 0 );
    formGridLayout->addWidget( m_editLogin, 0, 1 );
    formGridLayout->addWidget( labelPassword, 1, 0 );
    formGridLayout->addWidget( m_editPassword, 1, 1 );
    formGridLayout->addWidget( m_buttons, 2, 0, 1, 2 );

    setLayout( formGridLayout );
}

