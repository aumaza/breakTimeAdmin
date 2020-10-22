#include "dialogaltastylos.h"
#include "ui_dialogaltastylos.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DialogAltaStylos::DialogAltaStylos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAltaStylos)
{
    ui->setupUi(this);
    setWindowTitle("Alta de Styles");
}

DialogAltaStylos::~DialogAltaStylos()
{
    delete ui;
}

void DialogAltaStylos::addStylos()
{
    QString consulta;
    consulta.append("INSERT INTO stylos ("
                    "descripcion"
                    ")"
                    "VALUES("
                    "'"+ui->descripcion->text()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        ui->mensaje->setText("REGISTRO AGREGADO CON EXITO!!!");
        qDebug() << "Register has been insert Succesfully";

    }

    else
    {
        ui->mensaje->setText("ERROR...NO SE HA PODIDO AGREGAR EL REGISTRO");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< insertar.executedQuery();
        qDebug()<<"ERROR!"<< insertar.lastError();
    }
}

void DialogAltaStylos::on_salir_clicked()
{
    reject();
}

void DialogAltaStylos::on_agregar_clicked()
{
    addStylos();
    ui->descripcion->clear();
}
