#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include "dialogmenu.h"

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
    setWindowTitle("LogIn");
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::clearScreen()
{
    ui->usuario->clear();
    ui->password->clear();
}

void DialogLogin::on_pushButton_clicked()
{
        QString user = ui->usuario->text();
        QString pass = ui->password->text();

        QString consulta;
        consulta.append("SELECT * FROM usuarios");
        QSqlQuery consultar;
        consultar.prepare(consulta);



        if(consultar.exec("SELECT * FROM usuarios where nickname='"+user+"' and password='"+pass+"'"))
        {
            if(consultar.next())
            {
            ui->mensaje->setText("Bienvenido: " + user);
            clearScreen();
            DialogMenu Mn;
            Mn.exec();
            qDebug() << "LogIn Succesfully";

            }

            if(!consultar.next())
            {
                ui->mensaje->setText("Usuario o Password Incorrecto...Reintente");
                clearScreen();

            }

            else
            {

                //ui->mensaje->setText("Usuario o contraseña Incorrecta");
                exit(0);
                qDebug()<<"ERROR! LogIn failure...";

            }
         }
}
