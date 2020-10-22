#include "dialogventas.h"
#include "ui_dialogventas.h"

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QtSql/QSqlError>

DialogVentas::DialogVentas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVentas)
{
    ui->setupUi(this);
}

DialogVentas::~DialogVentas()
{
    delete ui;
}

void DialogVentas::agregarVenta()
{
    QString consulta;
    consulta.append("INSERT INTO ventas ("
                    "concepto,"
                    "monto,"
                    "formaPago,"
                    "dia,"
                    "mes,"
                    "anio,"
                    "observaciones"
                    ")"
                    "VALUES("
                    "'"+ui->lineEditConcepto->text()+"',"
                    "'"+ui->lineEditMonto->text()+"',"
                    "'"+ui->comboBoxFormaPago->currentText()+"',"
                    "'"+ui->cBoxDia->currentText()+"',"
                    "'"+ui->cBoxMes->currentText()+"',"
                    "'"+ui->cBoxAnio->currentText()+"',"
                    "'"+ui->observaciones->toPlainText()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        ui->mensajeVentas->setText("VENTA INGRESADA!!!");
        qDebug() << "Register has been insert Succesfully";

    }

    else
    {
        ui->mensajeVentas->setText("ERROR...NO SE HA PODIDO CARGAR LA VENTA");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< insertar.executedQuery();
        qDebug()<<"ERROR!"<< insertar.lastError();
    }
}

void DialogVentas::cleanScreen()
{
    ui->lineEditConcepto->clear();
    ui->lineEditMonto->clear();
    ui->observaciones->clear();
}

void DialogVentas::listarVentas()
{
    QString formaPago = ui->comboBoxFormaPago_2->currentText();
    QString dia = ui->cBoxDia_2->currentText();
    QString mes = ui->cBoxMes_2->currentText();
    QString anio = ui->cBoxAnio_2->currentText();

    QString consulta;
    consulta.append("SELECT * FROM ventas where formaPago='"+formaPago+"' and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");
    //consulta.append("SELECT sum(monto) as total FROM ventas where formaPago='"+formaPago+"' and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");
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
    ui->tableVentas->setRowCount(0);

    while(consultar.next())
      {
        //float total = consultar.value(0).toFloat();
        ui->tableVentas->insertRow(fila);

            for(int i=0; i<7; i++)
            {
                ui->tableVentas->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));

            }
            count++;
            fila++;
            //ui->mensajeVentas_3->setText("Por un total de: " + QString::number(total));
      }
    QString contador = QString::number(count);
    ui->mensajeVentas_2->setText("Hay " + contador + " Ventas/s Realizada/s");

}

void DialogVentas::sumarVentas()
{
    QString formaPago = ui->comboBoxFormaPago_2->currentText();
    QString dia = ui->cBoxDia_2->currentText();
    QString mes = ui->cBoxMes_2->currentText();
    QString anio = ui->cBoxAnio_2->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as total FROM ventas where formaPago='"+formaPago+"' and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeVentas_3->setText("Por un Total de: $" + QString::number(total));

        flag = 1;

        }



    if(flag == 1)
    {
        qDebug()<< "Sum has been doing Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible do that!!!";
        qDebug()<<"ERROR!"<< query.lastError();
        qDebug()<<query.lastQuery();
        qDebug()<<query.numRowsAffected();
    }

}

void DialogVentas::on_backToMenu_clicked()
{
    reject();
}

void DialogVentas::on_agregar_clicked()
{
    agregarVenta();
    cleanScreen();
}

void DialogVentas::on_buscar_clicked()
{
    listarVentas();
    sumarVentas();
}
