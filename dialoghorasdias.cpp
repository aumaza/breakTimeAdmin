#include "dialoghorasdias.h"
#include "ui_dialoghorasdias.h"

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QtSql/QSqlError>

DialogHorasDias::DialogHorasDias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHorasDias)
{
    ui->setupUi(this);
    setWindowTitle("Dias y Horarios");

    cargarComboBoxStyles();
    cargarComboBoxDocente();
    listarHoraDia();
}

DialogHorasDias::~DialogHorasDias()
{
    delete ui;
}

void DialogHorasDias::cargarComboBoxStyles()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT descripcion FROM stylos");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->comboBoxStyle->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogHorasDias::cargarComboBoxDocente()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT nombreApellido FROM docentes");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->comboBoxDocente->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogHorasDias::addHoraDia()
{
    QString consulta;
    consulta.append("INSERT INTO diasHorario ("
                    "hora,"
                    "dia,"
                    "actividad,"
                    "style,"
                    "docente"
                    ")"
                    "VALUES("
                    "'"+ui->comboBoxHora->currentText()+"',"
                    "'"+ui->comboBoxDia->currentText()+"',"
                    "'"+ui->comboBoxActividad->currentText()+"',"
                    "'"+ui->comboBoxStyle->currentText()+"',"
                    "'"+ui->comboBoxDocente->currentText()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        ui->mensaje->setText("ACTIVIDAD PROGRAMADA!!!");
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

void DialogHorasDias::listarHoraDia()
{
    QString consulta;
    consulta.append("SELECT * FROM diasHorario");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
      qDebug() << "All registers are shown Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible show table registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }

    int count = 0;
    int fila = 0;
    ui->tableDiasHorario->setRowCount(0);

    while(consultar.next())
      {
         ui->tableDiasHorario->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableDiasHorario->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString contador = QString::number(count);
    ui->mensajeTabla->setText("Hay " + contador + " Actividades/s");
}

void DialogHorasDias::filtrarDia()
{
    QString dia = ui->comboBoxDia_2->currentText();

    QString consulta;
    consulta.append("SELECT * FROM diasHorario where dia='"+dia+"'");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
      qDebug() << "All registers are shown Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible show table registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }

    int count = 0;
    int fila = 0;
    ui->tableDiasHorario->setRowCount(0);

    while(consultar.next())
      {
         ui->tableDiasHorario->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableDiasHorario->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString contador = QString::number(count);
    ui->mensajeTabla->setText("Hay " + contador + " Actividades/s");
}

void DialogHorasDias::filtrarActividad()
{
    QString actividad = ui->comboBoxActividad_2->currentText();

    QString consulta;
    consulta.append("SELECT * FROM diasHorario where actividad='"+actividad+"'");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
      qDebug() << "All registers are shown Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible show table registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }

    int count = 0;
    int fila = 0;
    ui->tableDiasHorario->setRowCount(0);

    while(consultar.next())
      {
         ui->tableDiasHorario->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableDiasHorario->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString contador = QString::number(count);
    ui->mensajeTabla->setText("Hay " + contador + " Actividades/s");
}

void DialogHorasDias::buscarStyle()
{
    QString style = ui->comboBoxStyle->currentText();
    QSqlQuery consultar;
    consultar.prepare("SELECT * from diasHorario where style='"+style+"'");


    if(consultar.exec())
    {
        while(consultar.next())
        {
            ui->comboBoxHora->setCurrentIndex(ui->comboBoxHora->findText(consultar.value(1).toString()));
            ui->comboBoxDia->setCurrentIndex(ui->comboBoxDia->findText(consultar.value(2).toString()));
            ui->comboBoxActividad->setCurrentIndex(ui->comboBoxActividad->findText(consultar.value(3).toString()));
            ui->comboBoxStyle->setCurrentIndex(ui->comboBoxStyle->findText(consultar.value(4).toString()));
            ui->comboBoxDocente->setCurrentIndex(ui->comboBoxDocente->findText(consultar.value(5).toString()));

        }
        ui->mensaje->setText("REGISTRO ENCONTRADO!!!");
        qDebug() << "All registers are shown Succesfully";
    }

    else
    {
        ui->mensaje->setText("REGISTRO INEXISTENTE!!");
        qDebug()<<"ERROR! Impossible show table registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}


void DialogHorasDias::on_pushButton_2_clicked()
{
    reject();
}

void DialogHorasDias::on_agregar_clicked()
{
    addHoraDia();
}

void DialogHorasDias::on_filtrarDia_clicked()
{
    filtrarDia();
}

void DialogHorasDias::on_filtrarActividad_clicked()
{
    filtrarActividad();
}

void DialogHorasDias::on_buscar_clicked()
{
    buscarStyle();
}
