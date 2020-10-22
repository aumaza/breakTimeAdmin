#include "dialogaltaclases.h"
#include "ui_dialogaltaclases.h"
#include <QDebug>
#include <QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDate>
#include <QDateEdit>

DialogAltaClases::DialogAltaClases(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAltaClases)
{
    ui->setupUi(this);
    setWindowTitle("Inscripcion a Clases");

    cargarComboBoxPack();
    cargarComboxStyles();
    cargarComboBoxAlumno();
    cargarComboBoxTipoActividad();
}

DialogAltaClases::~DialogAltaClases()
{
    delete ui;
}

void DialogAltaClases::cargarComboBoxPack()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT descripcion FROM packs");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->pack->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAltaClases::cargarComboxStyles()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT descripcion FROM stylos");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->style->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAltaClases::cargarComboBoxAlumno()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT nombreApellido FROM personas");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->comboBoxAlumno->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAltaClases::cargarComboBoxTipoActividad()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT descripcion FROM tipoActividad");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->comboBoxTipActividad->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAltaClases::addClases()
{
    QString consulta;
    consulta.append("INSERT INTO actividades ("
                    "actividad,"
                    "nombreApellido,"
                    "style,"
                    "pack,"
                    "dia,"
                    "mes,"
                    "anio,"
                    "docente,"
                    "valor,"
                    "formaPago"
                    ")"
                    "VALUES("
                    "'"+ui->comboBoxTipActividad->currentText()+"',"
                    "'"+ui->comboBoxAlumno->currentText()+"',"
                    "'"+ui->style->currentText()+"',"
                    "'"+ui->pack->currentText()+"',"
                    "'"+ui->comboBoxDia->currentText()+"',"
                    "'"+ui->mes_3->currentText()+"',"
                    "'"+ui->anio_3->currentText()+"',"
                    "'"+ui->nombreDocente->text()+"',"
                    "'"+ui->monto->text()+"',"
                    "'"+ui->formaPago->currentText()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        ui->mensaje->setText("INSCRIPCION EXITOSA!!!");
        qDebug() << "Register has been insert Succesfully";

    }

    else
    {
        ui->mensaje->setText("ERROR...NO SE HA PODIDO REALIZAR LA INSCRIPCIÓN");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< insertar.executedQuery();
        qDebug()<<"ERROR!"<< insertar.lastError();
    }
}

void DialogAltaClases::clearScreen()
{
    ui->nombreDocente->clear();
    ui->monto->clear();
}

void DialogAltaClases::on_salir_clicked()
{
    reject();
}

void DialogAltaClases::on_agregar_clicked()
{
    addClases();
    clearScreen();
}
