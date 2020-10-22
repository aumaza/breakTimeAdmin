#include "dialogaltapacks.h"
#include "ui_dialogaltapacks.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DialogAltaPacks::DialogAltaPacks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAltaPacks)
{
    ui->setupUi(this);
    setWindowTitle("Alta de Packs");
}

DialogAltaPacks::~DialogAltaPacks()
{
    delete ui;
}

void DialogAltaPacks::addPacks()
{
    QString consulta;
    consulta.append("INSERT INTO packs ("
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

void DialogAltaPacks::on_pushButton_2_clicked()
{
    addPacks();
    ui->descripcion->clear();
}

void DialogAltaPacks::on_pushButton_3_clicked()
{
    reject();
}
