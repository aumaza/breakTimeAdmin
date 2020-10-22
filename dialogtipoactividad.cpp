#include "dialogtipoactividad.h"
#include "ui_dialogtipoactividad.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DialogTipoActividad::DialogTipoActividad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTipoActividad)
{
    ui->setupUi(this);
    setWindowTitle("Alta Tipo de Actividad");
}

DialogTipoActividad::~DialogTipoActividad()
{
    delete ui;
}

void DialogTipoActividad::addTipoActividad()
{
    QString consulta;
    consulta.append("INSERT INTO tipoActividad ("
                    "descripcion"
                    ")"
                    "VALUES("
                    "'"+ui->actividad->text()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        ui->mensaje->setText("REGISTRO EXITOSO!!!");
        qDebug() << "Register has been insert Succesfully";

    }

    else
    {
        ui->mensaje->setText("ERROR...NO SE HA PODIDO REALIZAR EL REGISTRO");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< insertar.executedQuery();
        qDebug()<<"ERROR!"<< insertar.lastError();
    }
}

void DialogTipoActividad::on_back_clicked()
{
    reject();
}

void DialogTipoActividad::on_agregar_clicked()
{
    addTipoActividad();
    ui->actividad->clear();
}
