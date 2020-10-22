#include "dialoguserregister.h"
#include "ui_dialoguserregister.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DialogUserRegister::DialogUserRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUserRegister)
{
    ui->setupUi(this);
    setWindowTitle("Registro/Administracion de Usuarios");
}

DialogUserRegister::~DialogUserRegister()
{
    delete ui;
}

void DialogUserRegister::cleanScreen()
{
    ui->nombre->clear();
    ui->nickname->clear();
    ui->pass->clear();
    ui->pass1->clear();
}


//REGISTER
//==================================================================================================
void DialogUserRegister::addUser()
{
   QString pass = ui->pass->text();
   QString pass1 = ui->pass1->text();

   if(pass == pass1)
   {
       ui->mensaje->setText("USUARIO AGREGADO EXITOSAMENTE!!");
       qDebug()<<"Password Correcto";


    QString consulta;
    consulta.append("INSERT INTO usuarios ("
                    "nombre,"
                    "password,"
                    "nickname"
                    ")"
                    "VALUES("
                    "'"+ui->nombre->text()+"',"
                    "'"+ui->pass->text()+"',"
                    "'"+ui->nickname->text()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        qDebug() << "User has been insert Succesfully";

    }

    else
    {
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< insertar.executedQuery();
        qDebug()<<"ERROR!"<< insertar.lastError();
    }
   }

   else
   {
       ui->mensaje->setText("EROOR!! LOS PASSWORD NO COINCIDEN...REINTENTE!!");
       qDebug()<<"Error! El password no coincide, por favor reintente!!";
   }
}


void DialogUserRegister::on_pushButton_3_clicked()
{
    reject();
}

void DialogUserRegister::on_pushButton_2_clicked()
{
    addUser();
    cleanScreen();
}



//SEARCH
//====================================================================================
void DialogUserRegister::searchUser()
{
    QString nombre = ui->nombre->text();

    QString consulta;
    consulta.append("SELECT * FROM usuarios where nombre='"+nombre+"'");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        int flag = 0;

        while(consultar.next())
        {
            ui->nombre->setText(consultar.value(1).toString());
            ui->nickname->setText(consultar.value(3).toString());
            flag = 1;
        }

        if(flag == 1)
        {
            qDebug() << "USUARIO ENCONTRADO!!";
            ui->mensaje->setText("USUARIO ENCONTRADO!!");
        }

      else
      {
          ui->mensaje->setText("USUARIO INEXISTENTE!!");
          qDebug()<<"ERROR! USUARIO INEXISTENTE...";
      }
    }

    else
    {
        ui->mensaje->setText("USUARIO INEXISTENTE!!");
        qDebug()<<"ERROR! USUARIO INEXISTENTE...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }


}

//EDIT
//===============================================================================================

void DialogUserRegister::editUser()
{

    QString nickname = ui->nickname->text();
    QString pass = ui->pass->text();
    QString pass1 = ui->pass1->text();

    if(pass == pass1)
    {

    QSqlQuery qry;
    qry.prepare("UPDATE usuarios set password='"+pass+"' WHERE nickname='"+nickname+"'");

    if(qry.exec())
    {
        ui->mensaje->setText("REGISTRO ACTUALIZADO EXITOSAMENTE");
        qDebug() << "User has been update Succesfully";

    }

    else
    {
        ui->mensaje->setText("LOS PASSWORD NO COINCIDEN...REINTENTE!!");
        qDebug()<<"ERROR! Impossible update...";
        qDebug()<<"ERROR!"<< qry.executedQuery();
        qDebug()<<"ERROR!"<< qry.lastError();
    }
    }
}


//DELETE
//=======================================================================================================
void DialogUserRegister::deleteUser()
{
    QString nombre = ui->nombre->text();

    QSqlQuery consultar;
    consultar.prepare("Delete from usuarios where nombre='"+nombre+"'");


    if(consultar.exec())
    {

        ui->mensaje->setText("EL USUARIO HA SIDO ELIMINADO!!");
        qDebug() << "User has been deleted Succesfully";

    }

    else
    {

        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}


//BUTTONS
//========================================================================================

void DialogUserRegister::on_buscarUsuario_clicked()
{
    searchUser();
}

void DialogUserRegister::on_modificarPass_clicked()
{
    editUser();
    cleanScreen();
}

void DialogUserRegister::on_eliminarUser_clicked()
{
    deleteUser();
    cleanScreen();
}
