#include "dialogfacturacion.h"
#include "ui_dialogfacturacion.h"

#include <QDebug>
#include <QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFile>
#include <QLatin1Char>
#include <QTextStream>
#include <QSqlRecord>
#include <QString>

DialogFacturacion::DialogFacturacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFacturacion)
{
    ui->setupUi(this);
    setWindowTitle("Facturacion");

    cargarComboBoxDocente();
    cargarComboBoxAlumno();
    listarTotaPagoDocente();
    listarCobroTotalAlumnos();
    listarHistorialCF();
    listarHistoricoIngresos();
    listarHistoricoEgresos();
   // listarPagos();
}

DialogFacturacion::~DialogFacturacion()
{
    delete ui;
}

void DialogFacturacion::agregarPagos()
{
    QString consulta;
    consulta.append("INSERT INTO pagos ("
                    "concepto,"
                    "monto,"
                    "dia,"
                    "mes,"
                    "anio,"
                    "descripcion"
                    ")"
                    "VALUES("
                    "'"+ui->concepto->currentText()+"',"
                    "'"+ui->montoPagado->text()+"',"
                    "'"+ui->comboBoxDia_2->currentText()+"',"
                    "'"+ui->mes->currentText()+"',"
                    "'"+ui->anio->currentText()+"',"
                    "'"+ui->observacion->toPlainText()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        ui->mensajePagos->setText("PAGO REGISTRADO EXITOSAMENTE!!!");
        qDebug() << "Register has been insert Succesfully";

    }

    else
    {
        ui->mensajePagos->setText("ERROR...NO SE HA PODIDO REALIZAR EL REGISTRO DEL PAGO");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< insertar.executedQuery();
        qDebug()<<"ERROR!"<< insertar.lastError();
    }
}

void DialogFacturacion::listarPagos()
{
    QString consulta;
    consulta.append("SELECT * FROM pagos");
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
    ui->tableCierrePagos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableCierrePagos->insertRow(fila);

            for(int i=0; i<7; i++)
            {
                ui->tableCierrePagos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCierrePagos1->setText("Se cargaron " + counter + " Concepto/s");
}

void DialogFacturacion::buscarPagoMesAnio()
{
    QString mes = ui->mes_5->currentText();
    QString anio = ui->anio_5->currentText();

    QString consulta;
    consulta.append("SELECT * FROM pagos where mes='"+mes+"' and anio='"+anio+"'");
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
    ui->tableCierrePagos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableCierrePagos->insertRow(fila);

            for(int i=0; i<7; i++)
            {
                ui->tableCierrePagos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCierrePagos1->setText("Hay " + counter + " Registros");
}

void DialogFacturacion::buscarPagoAnios()
{
    QString anio = ui->anio_5->currentText();

    QString consulta;
    consulta.append("SELECT * FROM pagos where anio='"+anio+"'");
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
    ui->tableCierrePagos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableCierrePagos->insertRow(fila);

            for(int i=0; i<7; i++)
            {
                ui->tableCierrePagos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCierrePagos1->setText("Hay " + counter + " Registros");
}



void DialogFacturacion::agregarPagosDocentes()
{
    QString consulta;
    consulta.append("INSERT INTO pagoDocentes ("
                    "nombreApellido,"
                    "monto,"
                    "dia,"
                    "mes,"
                    "anio"
                    ")"
                    "VALUES("
                    "'"+ui->comboBoxDocente->currentText()+"',"
                    "'"+ui->montoPagado_2->text()+"',"
                    "'"+ui->comboBoxDia->currentText()+"',"
                    "'"+ui->mes_2->currentText()+"',"
                    "'"+ui->anio_2->currentText()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        ui->mensajeDocente->setText("PAGO DOCENTE REGISTRADO EXITOSAMENTE!!!");
        qDebug() << "Register has been insert Succesfully";

    }

    else
    {
        ui->mensajeDocente->setText("ERROR...NO SE HA PODIDO REALIZAR EL REGISTRO DEL PAGO");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< insertar.executedQuery();
        qDebug()<<"ERROR!"<< insertar.lastError();
    }
}

void DialogFacturacion::cleanScreen()
{
    ui->montoPagado->clear();
}

void DialogFacturacion::cargarComboBoxDocente()
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
        ui->comboBoxDocente_2->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}



void DialogFacturacion::listarTotaPagoDocente()
{
    QString consulta;
    consulta.append("SELECT * FROM totalPagoDocentes");
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
    ui->tableTotalPagoDocentes->setRowCount(0);

    while(consultar.next())
      {
         ui->tableTotalPagoDocentes->insertRow(fila);

            for(int i=0; i<11; i++)
            {
                ui->tableTotalPagoDocentes->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeTotalPagos->setText("Se realizaron " + counter + " Pago/s");
}


void DialogFacturacion::on_backmenu_clicked()
{
    reject();
}

void DialogFacturacion::on_agregar_clicked()
{
    agregarPagos();
    cleanScreen();
}

void DialogFacturacion::on_agregar_2_clicked()
{
    agregarPagosDocentes();
    ui->montoPagado_2->clear();
}


//SEARCHS
//====================================================================================================

void DialogFacturacion::buscarDocente()
{
    QString nombre = ui->comboBoxDocente_2->currentText();

    QString consulta;
    consulta.append("SELECT * FROM pagoDocentes where nombreApellido='"+nombre+"'");
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
    ui->tableLiqDocentes->setRowCount(0);

    while(consultar.next())
      {
         ui->tableLiqDocentes->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableLiqDocentes->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajePagos_2->setText("Hay " + counter + " Registros");
}

void DialogFacturacion::buscarDocenteDiaMesAnio()
{
    QString nombre = ui->comboBoxDocente_2->currentText();
    QString dia = ui->comboBoxDia_3->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QString consulta;
    consulta.append("SELECT * FROM pagoDocentes where nombreApellido='"+nombre+"'and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");
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
    ui->tableLiqDocentes->setRowCount(0);

    while(consultar.next())
      {
         ui->tableLiqDocentes->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableLiqDocentes->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajePagos_2->setText("Hay " + counter + " Registros");
}

void DialogFacturacion::buscarDocenteMesAnio()
{
    QString nombre = ui->comboBoxDocente_2->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QString consulta;
    consulta.append("SELECT * FROM pagoDocentes where nombreApellido='"+nombre+"' and mes='"+mes+"' and anio='"+anio+"'");
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
    ui->tableLiqDocentes->setRowCount(0);

    while(consultar.next())
      {
         ui->tableLiqDocentes->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableLiqDocentes->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajePagos_2->setText("Hay " + counter + " Registros");
}

void DialogFacturacion::buscarDiaMesAnio()
{
    QString dia = ui->comboBoxDia_3->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QString consulta;
    consulta.append("SELECT * FROM pagoDocentes where dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");
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
    ui->tableLiqDocentes->setRowCount(0);

    while(consultar.next())
      {
         ui->tableLiqDocentes->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableLiqDocentes->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajePagos_2->setText("Hay " + counter + " Registros");
}

void DialogFacturacion::buscarMesAnio()
{
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QString consulta;
    consulta.append("SELECT * FROM pagoDocentes where mes='"+mes+"' and anio='"+anio+"'");
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
    ui->tableLiqDocentes->setRowCount(0);

    while(consultar.next())
      {
         ui->tableLiqDocentes->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableLiqDocentes->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajePagos_2->setText("Hay " + counter + " Registros");
}

void DialogFacturacion::buscarAnio()
{
    QString anio = ui->anio_3->currentText();

    QString consulta;
    consulta.append("SELECT * FROM pagoDocentes where anio='"+anio+"'");
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
    ui->tableLiqDocentes->setRowCount(0);

    while(consultar.next())
      {
         ui->tableLiqDocentes->insertRow(fila);

            for(int i=0; i<5; i++)
            {
                ui->tableLiqDocentes->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajePagos_2->setText("Hay " + counter + " Registros");
}



//SUMAS PARA DOCENTES
//====================================================================================================


void DialogFacturacion::sumarDocente()
{
    QString nombreDoc = ui->comboBoxDocente_2->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum2 FROM pagoDocentes where nombreApellido='"+nombreDoc+"'");

        int flag = 0;
       while(query.next())
        {
        float acum2 = query.value(0).toFloat();
        query.exec("INSERT INTO totalPagoDocentes (docente,acum2)"
                   "VALUES('"+nombreDoc+"'," + QString::number(acum2) + ')');

        flag = 1;

        }



    if(flag == 1)
    {
        ui->mensajePagos_3->setText("GUARDADO EXITOSO!!");
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

void DialogFacturacion::sumarDiaMesAnio()
{
    QString dia = ui->comboBoxDia_3->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum4 FROM pagoDocentes where dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum4 = query.value(0).toFloat();
        query.exec("INSERT INTO totalPagoDocentes (dia,mes,anio,acum5)"
                   "VALUES('"+dia+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(acum4) + ')');

        flag = 1;

        }



    if(flag == 1)
    {
        ui->mensajePagos_3->setText("GUARDADO EXITOSO!!");
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

void DialogFacturacion::sumarMesAnio()
{
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum5 FROM pagoDocentes where mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum5 = query.value(0).toFloat();
        query.exec("INSERT INTO totalPagoDocentes (mes,anio,acum5)"
                   "VALUES('"+mes+"'," "'"+anio+"'," + QString::number(acum5) + ')');

        flag = 1;

        }



    if(flag == 1)
    {
        ui->mensajePagos_3->setText("GUARDADO EXITOSO!!");
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

void DialogFacturacion::sumarDocDiaMesAnio()
{
    QString nombreDoc = ui->comboBoxDocente_2->currentText();
    QString dia = ui->comboBoxDia_3->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum1 FROM pagoDocentes where nombreApellido='"+nombreDoc+"' and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum1 = query.value(0).toFloat();
        query.exec("INSERT INTO totalPagoDocentes (docente,dia,mes,anio,acum1)"
                   "VALUES('"+nombreDoc+"'," "'"+dia+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(acum1) + ')');

        flag = 1;

        }



    if(flag == 1)
    {
        ui->mensajePagos_3->setText("GUARDADO EXITOSO!!");
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

void DialogFacturacion::sumarDocMesAnio()
{
    QString nombreDoc = ui->comboBoxDocente_2->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum3 FROM pagoDocentes where nombreApellido='"+nombreDoc+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum3 = query.value(0).toFloat();
        query.exec("INSERT INTO totalPagoDocentes (docente,mes,anio,acum3)"
                   "VALUES('"+nombreDoc+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(acum3) + ')');

        flag = 1;

        }



    if(flag == 1)
    {
        ui->mensajePagos_3->setText("GUARDADO EXITOSO!!");
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

void DialogFacturacion::sumarAnios()
{

    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum6 FROM pagoDocentes where anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum6 = query.value(0).toFloat();
        query.exec("INSERT INTO totalPagoDocentes (anio,acum6)"
                   "VALUES('"+anio+"'," + QString::number(acum6) + ')');
        //ui->mensajePagos_3->setText("Total: $" + QString::number(acum6));
        flag = 1;

        }



    if(flag == 1)
    {
        ui->mensajePagos_3->setText("GUARDADO EXITOSO!!");
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

void DialogFacturacion::muestraSumaDocente()
{
    QString nombreDoc = ui->comboBoxDocente_2->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum2 FROM pagoDocentes where nombreApellido='"+nombreDoc+"'");

        int flag = 0;
       while(query.next())
        {
        float acum2 = query.value(0).toFloat();
        ui->mensajePagos_3->setText("Total: $" + QString::number(acum2));

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

void DialogFacturacion::muestraDocDiaMesAnio()
{
    QString nombreDoc = ui->comboBoxDocente_2->currentText();
    QString dia = ui->comboBoxDia_3->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum1 FROM pagoDocentes where nombreApellido='"+nombreDoc+"' and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum1 = query.value(0).toFloat();
        ui->mensajePagos_3->setText("Total: $" + QString::number(acum1));

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

void DialogFacturacion::muestraDocMesAnio()
{
    QString nombreDoc = ui->comboBoxDocente_2->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum3 FROM pagoDocentes where nombreApellido='"+nombreDoc+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum3 = query.value(0).toFloat();
        ui->mensajePagos_3->setText("Total: $" + QString::number(acum3));
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

void DialogFacturacion::muestraDiaMesAnio()
{
    QString dia = ui->comboBoxDia_3->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum4 FROM pagoDocentes where dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum4 = query.value(0).toFloat();
        ui->mensajePagos_3->setText("Total: $" + QString::number(acum4));

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

void DialogFacturacion::muestraMesAnio()
{
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum5 FROM pagoDocentes where mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum5 = query.value(0).toFloat();
         ui->mensajePagos_3->setText("Total: $" + QString::number(acum5));

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


void DialogFacturacion::muestraAnios()
{

    QString anio = ui->anio_3->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as acum6 FROM pagoDocentes where anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum6 = query.value(0).toFloat();
        ui->mensajePagos_3->setText("Total: $" + QString::number(acum6));
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

void DialogFacturacion::listarCobroTotalAlumnos()
{
    QString consulta;
    consulta.append("SELECT * FROM totalCobroAlumnos");
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
    ui->tableTotalCobroAlumnos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableTotalCobroAlumnos->insertRow(fila);

            for(int i=0; i<11; i++)
            {
                ui->tableTotalCobroAlumnos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeListaAlumnos->setText("Hay " + counter + " Registro/s");
}




//BUTTONS PARA PAGO A DOCENTES
//====================================================================================================

void DialogFacturacion::on_filtroDocente_clicked()
{
    buscarDocente();
    muestraSumaDocente();
}


void DialogFacturacion::on_filtroDocMesAnio_clicked()
{
    buscarDocenteDiaMesAnio();
    muestraDocDiaMesAnio();
}

void DialogFacturacion::on_filtroMesAnio_clicked()
{
    buscarMesAnio();
    muestraMesAnio();
}

void DialogFacturacion::on_filtroAnio_clicked()
{
    buscarAnio();
    muestraAnios();
}

void DialogFacturacion::on_filtroDiaMesAnio_clicked()
{
    buscarDiaMesAnio();
    muestraDiaMesAnio();
}

void DialogFacturacion::on_pushButton_2_clicked()
{
    buscarDocenteMesAnio();
    muestraMesAnio();
}

//METODOS PESTAÑA COBRO ALUMNOS
//=================================================================

void DialogFacturacion::cargarComboBoxAlumno()
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


void DialogFacturacion::buscarAlumno()
{
    QString nombre = ui->comboBoxAlumno->currentText();

    QString consulta;
    consulta.append("SELECT * FROM actividades where nombreApellido='"+nombre+"'");
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
    ui->tableAlumnos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableAlumnos->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableAlumnos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCobros->setText("Hay " + counter + " Registro/s");
}

void DialogFacturacion::buscarAlumnoDiaMesAnio()
{
    QString nombre = ui->comboBoxAlumno->currentText();
    QString dia = ui->comboBoxDia_4->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QString consulta;
    consulta.append("SELECT * FROM actividades where nombreApellido='"+nombre+"' and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'" );
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
    ui->tableAlumnos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableAlumnos->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableAlumnos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCobros->setText("Hay " + counter + " Registro/s");
}

void DialogFacturacion::buscarAlumnoMesAnio()
{
    QString nombre = ui->comboBoxAlumno->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QString consulta;
    consulta.append("SELECT * FROM actividades where nombreApellido='"+nombre+"' and mes='"+mes+"' and anio='"+anio+"'" );
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
    ui->tableAlumnos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableAlumnos->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableAlumnos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCobros->setText("Hay " + counter + " Registro/s");
}

void DialogFacturacion::buscarDiaMesAnioA()
{
    QString dia = ui->comboBoxDia_4->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QString consulta;
    consulta.append("SELECT * FROM actividades where dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'" );
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
    ui->tableAlumnos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableAlumnos->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableAlumnos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCobros->setText("Hay " + counter + " Registro/s");
}

void DialogFacturacion::buscarMesAnioA()
{
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QString consulta;
    consulta.append("SELECT * FROM actividades where mes='"+mes+"' and anio='"+anio+"'" );
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
    ui->tableAlumnos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableAlumnos->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableAlumnos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCobros->setText("Hay " + counter + " Registro/s");
}

void DialogFacturacion::buscarAnioA()
{
    QString anio = ui->anio_4->currentText();

    QString consulta;
    consulta.append("SELECT * FROM actividades where anio='"+anio+"'" );
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
    ui->tableAlumnos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableAlumnos->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableAlumnos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCobros->setText("Hay " + counter + " Registro/s");
}



//SUMAS ALUMNOS
//====================================================================

void DialogFacturacion::sumarAlumno()
{
    QString nombreDoc = ui->comboBoxAlumno->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as total FROM actividades where nombreApellido='"+nombreDoc+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeCobros_1->setText("Total abonado: $" + QString::number(total));

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

void DialogFacturacion::sumarAlumnoDiaMesAnio()
{
    QString nombreDoc = ui->comboBoxAlumno->currentText();
    QString dia = ui->comboBoxDia_4->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as total FROM actividades where nombreApellido='"+nombreDoc+"' and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeCobros_1->setText("Total abonado: $" + QString::number(total));

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

void DialogFacturacion::sumarAlumnoMesAnio()
{
    QString nombreDoc = ui->comboBoxAlumno->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as total FROM actividades where nombreApellido='"+nombreDoc+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeCobros_1->setText("Total abonado: $" + QString::number(total));

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

void DialogFacturacion::sumarDiaMesAnioA()
{
    QString dia = ui->comboBoxDia_4->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as total FROM actividades where dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeCobros_1->setText("Total abonado: $" + QString::number(total));

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

void DialogFacturacion::sumarMesAnioA()
{
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as total FROM actividades where mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeCobros_1->setText("Total abonado: $" + QString::number(total));

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

void DialogFacturacion::sumarAnioA()
{
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as total FROM actividades where anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeCobros_1->setText("Total abonado: $" + QString::number(total));

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

//PERSISTENCIA SUMA ALUMNOS
//===================================================================

void DialogFacturacion::guardarSumaAlumno()
{
    QString nombreDoc = ui->comboBoxAlumno->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as acum1 FROM actividades where nombreApellido='"+nombreDoc+"'");

        int flag = 0;
       while(query.next())
        {
        float acum1 = query.value(0).toFloat();
        query.exec("INSERT INTO totalCobroAlumnos (alumno,acum1)"
                   "VALUES('"+nombreDoc+"'," + QString::number(acum1) + ')');
        ui->mensajeCobros_1->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::guardarSumaAluDiaMesAnio()
{
    QString nombreDoc = ui->comboBoxAlumno->currentText();
    QString dia = ui->comboBoxDia_4->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as acum2 FROM actividades where nombreApellido='"+nombreDoc+"' and dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum2 = query.value(0).toFloat();
        query.exec("INSERT INTO totalCobroAlumnos (alumno,dia,mes,anio,acum2)"
                   "VALUES('"+nombreDoc+"'," "'"+dia+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(acum2) + ')');
        ui->mensajeCobros_1->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::guardarSumaAluMesAnio()
{
    QString nombreDoc = ui->comboBoxAlumno->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as acum3 FROM actividades where nombreApellido='"+nombreDoc+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum3 = query.value(0).toFloat();
        query.exec("INSERT INTO totalCobroAlumnos (alumno,mes,anio,acum3)"
                   "VALUES('"+nombreDoc+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(acum3) + ')');
        ui->mensajeCobros_1->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::guardarDiaMesAnio()
{
    QString dia = ui->comboBoxDia_4->currentText();
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as acum4 FROM actividades where dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum4 = query.value(0).toFloat();
        query.exec("INSERT INTO totalCobroAlumnos (dia,mes,anio,acum4)"
                   "VALUES('"+dia+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(acum4) + ')');
        ui->mensajeCobros_1->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::guardarMesAnio()
{
    QString mes = ui->mes_4->currentText();
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as acum5 FROM actividades where mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum5 = query.value(0).toFloat();
        query.exec("INSERT INTO totalCobroAlumnos (mes,anio,acum5)"
                   "VALUES('"+mes+"'," "'"+anio+"'," + QString::number(acum5) + ')');
        ui->mensajeCobros_1->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::guardarAnio()
{
    QString anio = ui->anio_4->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(valor) as acum6 FROM actividades where anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float acum6 = query.value(0).toFloat();
        query.exec("INSERT INTO totalCobroAlumnos (anio,acum6)"
                   "VALUES('"+anio+"'," + QString::number(acum6) + ')');
        ui->mensajeCobros_1->setText("GUARDADO EXITOSO!!");

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





//BUTTONS FOR COBRO ALUMNOS
//====================================================================

void DialogFacturacion::on_filtroAlumno_clicked()
{
    buscarAlumno();
    sumarAlumno();
}

void DialogFacturacion::on_filtroAluDiaMesAnio_clicked()
{
    buscarAlumnoDiaMesAnio();
    sumarAlumnoDiaMesAnio();
}

void DialogFacturacion::on_filtroAluMesAnio_clicked()
{
    buscarAlumnoMesAnio();
    sumarAlumnoMesAnio();
}

void DialogFacturacion::on_filtroDiaMesAnio_2_clicked()
{
    buscarDiaMesAnioA();
    sumarDiaMesAnioA();
}

void DialogFacturacion::on_filtroMesAnio_2_clicked()
{
    buscarMesAnioA();
    sumarMesAnioA();
}

void DialogFacturacion::on_filtroAnio_2_clicked()
{
    buscarAnioA();
    sumarAnioA();
}

//PERSISTENCIA PAGO DOCENTES
//==================================================================

void DialogFacturacion::on_GuardarD1_clicked()
{
    sumarDocente();
}

void DialogFacturacion::on_GuardarD2_clicked()
{
    sumarDocDiaMesAnio();
}

void DialogFacturacion::on_GuardarD3_clicked()
{
    sumarDocMesAnio();
}

void DialogFacturacion::on_GuardarD4_clicked()
{
    sumarDiaMesAnio();
}

void DialogFacturacion::on_GuardarD5_clicked()
{
    sumarMesAnio();
}

void DialogFacturacion::on_GuardarD6_clicked()
{
    sumarAnios();
}

//BOTONES PERSISTENCIA COBRO ALUMNOS
//===================================================================

void DialogFacturacion::on_GuardarA1_clicked()
{
    guardarSumaAlumno();
}

void DialogFacturacion::on_GuardarA2_clicked()
{
    guardarSumaAluDiaMesAnio();
}

void DialogFacturacion::on_GuardarA3_clicked()
{
    guardarSumaAluMesAnio();
}

void DialogFacturacion::on_GuardarA4_clicked()
{
    guardarDiaMesAnio();
}

void DialogFacturacion::on_GuardarA5_clicked()
{
    guardarMesAnio();
}

void DialogFacturacion::on_GuardarA6_clicked()
{
    guardarAnio();
}

//BUSQUEDA PARA PAGOS

void DialogFacturacion::on_filtrarMesAnioP_clicked()
{
    buscarPagoMesAnio();
    sumarPagosMesAnio();
}

void DialogFacturacion::on_filtrarAnioP_clicked()
{
    buscarPagoAnios();
    sumarPagosAnio();
}

//SUMATORIA PAGOS

void DialogFacturacion::sumarPagosMesAnio()
{
    //QString cierre = ui->comboBoxCierre->currentText();
    QString mes = ui->mes_5->currentText();
    QString anio = ui->anio_5->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as total FROM pagos where mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeCierrePagos2->setText("Total Pagado: $" + QString::number(total));

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

void DialogFacturacion::sumarPagosAnio()
{
    QString anio = ui->anio_5->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as total FROM pagos where anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        ui->mensajeCierrePagos2->setText("Total Pagado: $" + QString::number(total));

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


//GUARDAR CIERRE DE PAGOS
//==========================================

void DialogFacturacion::guardarPagosMesAnio()
{
    QString cierre = ui->comboBoxCierre->currentText();
    QString mes = ui->mes_5->currentText();
    QString anio = ui->anio_5->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as total FROM pagos where mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        query.exec("INSERT INTO pagos (concepto,mes,anio,total)"
                   "VALUES('"+cierre+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(total) + ')');
        ui->mensajeCierrePagos2->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::guardarPagosAnio()
{
    QString cierre = ui->comboBoxCierre->currentText();
    QString anio = ui->anio_5->currentText();

    QSqlQuery query;
    query.exec("SELECT sum(monto) as total FROM pagos where anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float total = query.value(0).toFloat();
        query.exec("INSERT INTO pagos (concepto,anio,total)"
                   "VALUES('"+cierre+"'," "'"+anio+"'," + QString::number(total) + ')');
        ui->mensajeCierrePagos2->setText("GUARDADO EXITOSO!!");

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

//PERSISTENCIA CIERRE PAGOS
//==================================================================

void DialogFacturacion::on_guardarP1_clicked()
{
    guardarPagosMesAnio();
}

void DialogFacturacion::on_guardarP2_clicked()
{
    guardarPagosAnio();
}


//FUNCIONES CIERRE FINAL
//===================================================================

void DialogFacturacion::filtrarDiaMesAnio()
{
    QString cierre = ui->comboBoxCierreCierreFinal->currentText();
    QString dia = ui->comboBoxDiaCierreFinal->currentText();
    QString mes = ui->comboBoxMesCierreFinal->currentText();
    QString anio = ui->comboBoxAnioCierreFinal->currentText();

    QSqlQuery query;
    query.exec("SELECT I.totalDiario - E.totalDiario AS totalDiario FROM ingresos I, egresos E where I.cierre='"+cierre+"' and I.dia='"+dia+"' and I.mes='"+mes+"' and I.anio='"+anio+"' and  E.cierre='"+cierre+"' and E.dia='"+dia+"' and E.mes='"+mes+"' and E.anio='"+anio+"'");


        int flag = 0;
       while(query.next())
        {
        float totalDiario = query.value(0).toFloat();
        ui->mensajeCierreFinal1->setText("Monto Total de Cierre Diario: $" + QString::number(totalDiario));

        flag = 1;

        }



    if(flag == 1)
    {
        qDebug()<<query.lastQuery();
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

void DialogFacturacion::filtrarMesAnio()
{
    QString cierre = ui->comboBoxCierreCierreFinal->currentText();
    QString mes = ui->comboBoxMesCierreFinal->currentText();
    QString anio = ui->comboBoxAnioCierreFinal->currentText();

    QSqlQuery query;
    query.exec("SELECT I.totalMensual - E.totalMensual AS totalMensual FROM ingresos I, egresos E where I.cierre='"+cierre+"' and I.mes='"+mes+"' and I.anio='"+anio+"' and  E.cierre='"+cierre+"' and E.mes='"+mes+"' and E.anio='"+anio+"'");


        int flag = 0;
       while(query.next())
        {
        float totalMensual = query.value(0).toFloat();
        ui->mensajeCierreFinal1->setText("Monto Total de Cierre Mensual: $" + QString::number(totalMensual));

        flag = 1;

        }



    if(flag == 1)
    {
        qDebug()<<query.lastQuery();
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

void DialogFacturacion::filtrarAnio()
{
    QString cierre = ui->comboBoxCierreCierreFinal->currentText();
    QString anio = ui->comboBoxAnioCierreFinal->currentText();

    QSqlQuery query;
    query.exec("SELECT I.totalAnual - E.totalAnual AS totalAnual FROM ingresos I, egresos E where I.cierre='"+cierre+"' and I.anio='"+anio+"' and  E.cierre='"+cierre+"' and E.anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalAnual = query.value(0).toFloat();
        ui->mensajeCierreFinal1->setText("Monto Total de Cierre Anual: $" + QString::number(totalAnual));

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



void DialogFacturacion::on_filtroDiaMesAnioCF_clicked()
{
    filtrarDiaMesAnio();
}


void DialogFacturacion::on_filtroMesAnioCF_clicked()
{
    filtrarMesAnio();
}

void DialogFacturacion::on_filtrarAnioCF_clicked()
{
    filtrarAnio();
}


//PERSISTENCIA CIERRE FINAL
//=====================================================================

void DialogFacturacion::guardarDiaMesAnioCF()
{
    QString cierre = ui->comboBoxCierreCierreFinal->currentText();
    QString dia = ui->comboBoxDiaCierreFinal->currentText();
    QString mes = ui->comboBoxMesCierreFinal->currentText();
    QString anio = ui->comboBoxAnioCierreFinal->currentText();

    QSqlQuery query;
    query.exec("SELECT I.totalDiario - E.totalDiario AS totalDiario FROM ingresos I, egresos E where I.cierre='"+cierre+"' and I.dia='"+dia+"' and I.mes='"+mes+"' and I.anio='"+anio+"' and  E.cierre='"+cierre+"' and E.dia='"+dia+"' and E.mes='"+mes+"' and E.anio='"+anio+"'");

        int flag = 0;

        while(query.next())
        {
        float totalDiario = query.value(0).toFloat();
        ui->mensajeCierreFinal2->setText("Monto Total de Cierre Diario: $" + QString::number(totalDiario));
        qDebug()<<  QString::number(totalDiario);

        query.exec("INSERT INTO cierreFinal (cierre,dia,mes,anio,totalDiario)"
                   "VALUES('"+cierre+"'," "'"+dia+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(totalDiario) + ')');
        ui->mensajeCierreFinal1->setText("GUARDADO EXITOSO!!");

        flag = 1;

        }

    if(flag == 1)
    {
        //qDebug()<<  QString::number(totalDiario);
        qDebug()<< query.lastQuery();
        qDebug()<< "Save Success!!";
    }

    else
    {
        qDebug()<<"ERROR! Impossible do that!!!";
        qDebug()<<"ERROR!"<< query.lastError();
        qDebug()<<query.lastQuery();
        qDebug()<<query.numRowsAffected();
    }
}

void DialogFacturacion::guardarMesAnioCF()
{
    QString cierre = ui->comboBoxCierreCierreFinal->currentText();
    QString mes = ui->comboBoxMesCierreFinal->currentText();
    QString anio = ui->comboBoxAnioCierreFinal->currentText();

    QSqlQuery query;
    query.exec("SELECT I.totalMensual - E.totalMensual AS totalMensual FROM ingresos I, egresos E where I.cierre='"+cierre+"' and I.mes='"+mes+"' and I.anio='"+anio+"' and  E.cierre='"+cierre+"' and E.mes='"+mes+"' and E.anio='"+anio+"'");

        int flag = 0;

        while(query.next())
        {
        float totalMensual = query.value(0).toFloat();
        ui->mensajeCierreFinal2->setText("Monto Total de Cierre Mensual: $" + QString::number(totalMensual));
        qDebug()<<  QString::number(totalMensual);

        query.exec("INSERT INTO cierreFinal (cierre,mes,anio,totalMensual)"
                   "VALUES('"+cierre+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(totalMensual) + ')');
        ui->mensajeCierreFinal1->setText("GUARDADO EXITOSO!!");

        flag = 1;

        }

    if(flag == 1)
    {
        //qDebug()<<  QString::number(totalMensual);
        qDebug()<< query.lastQuery();
        qDebug()<< "Save Success!!";
    }

    else
    {
        qDebug()<<"ERROR! Impossible do that!!!";
        qDebug()<<"ERROR!"<< query.lastError();
        qDebug()<<query.lastQuery();
        qDebug()<<query.numRowsAffected();
    }
}

void DialogFacturacion::guardarAnioCF()
{
    QString cierre = ui->comboBoxCierreCierreFinal->currentText();
    QString anio = ui->comboBoxAnioCierreFinal->currentText();

    QSqlQuery query;
    query.exec("SELECT I.totalAnual - E.totalAnual AS totalAnual FROM ingresos I, egresos E where I.cierre='"+cierre+"' and I.anio='"+anio+"' and  E.cierre='"+cierre+"' and E.anio='"+anio+"'");

        int flag = 0;

       while(query.next())
        {
        float totalAnual = query.value(0).toFloat();
        ui->mensajeCierreFinal2->setText("Monto Total de Cierre Anual: $" + QString::number(totalAnual));

        query.exec("INSERT INTO cierreFinal (cierre,anio,totalAnual)"
                     "VALUES('"+cierre+"'," "'"+anio+"'," + QString::number(totalAnual) + ')');

        ui->mensajeCierreFinal1->setText("GUARDADO EXITOSO!!");

        flag = 1;

        }

    if(flag == 1)
    {
        qDebug()<< "Save Success!!";
    }

    else
    {
        qDebug()<<"ERROR! Impossible do that!!!";
        qDebug()<<"ERROR!"<< query.lastError();
        qDebug()<<query.lastQuery();
        qDebug()<<query.numRowsAffected();
    }
}

void DialogFacturacion::listarHistorialCF()
{
    QString consulta;
    consulta.append("SELECT * FROM cierreFinal");
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
    ui->tableHistorialCF->setRowCount(0);

    while(consultar.next())
      {
         ui->tableHistorialCF->insertRow(fila);

            for(int i=0; i<7; i++)
            {
                ui->tableHistorialCF->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeCierreFinal2->setText("Hay " + counter + " Registro/s en el Historial");
}

//METODOS PARA EXPORTAR A CSV
//========================================================================

QString DialogFacturacion::escapedCSV(QString unexc)
{

        if (!unexc.contains(QLatin1Char(',')))
        {
           return unexc;
        }
        return '\"' + unexc.replace(QLatin1Char('\"'), QString("\"\"")) + '\"';
}

void DialogFacturacion::queryToCSVLiqDoc()
{
    QString name;
    name.append("SqlBase.sqlite");
    db.setDatabaseName(name);

    QString consulta;
    consulta.append("SELECT * FROM pagoDocentes");
    QSqlQuery consultar;
    consultar.prepare(consulta);
        QFile csvFile ("LiquidacionDocentes.csv");

        if (!csvFile.open(QFile::WriteOnly | QFile::Text))
        {
            qDebug("failed to open csv file");
            return;
        }

        if (!consultar.exec())
        {
            qDebug("failed to run query");
        }

        QTextStream outStream(&csvFile);
            outStream.setCodec("UTF-8");

            while (consultar.next())
            {
                const QSqlRecord record = consultar.record();

                for (int i=0, recCount = record.count() ; i<recCount ; ++i)
                {
                    if (i>0)
                        outStream << ',';
                    outStream << escapedCSV(record.value(i).toString());
                }
                outStream << '\n';
            }
            ui->mensajePagos_3->setText("Archivo Exportado con Exito!!");
}






//PERSINTENCIA BUTTONS
//========================================================================

void DialogFacturacion::on_guardarDiaMesAnioCF_clicked()
{
    guardarDiaMesAnioCF();
}

void DialogFacturacion::on_guardarMesAnioCF_clicked()
{
    guardarMesAnioCF();
}

void DialogFacturacion::on_guardarAnioCF_clicked()
{
    guardarAnioCF();
}

//EXPORT CSV BUTTONS
//=========================================================================

void DialogFacturacion::on_exportCSVLiqDoc_clicked()
{
    queryToCSVLiqDoc();
}



//INGRESOS
//==========================================================================

void DialogFacturacion::filtrarDiaMesAnioIngresos()
{
    QString formaPago = ui->comboBoxFPagoIngresos->currentText();
    QString dia = ui->comboBoxDiaIngresos->currentText();
    QString mes = ui->comboBoxMesIngresos->currentText();
    QString anio = ui->comboBoxAnioIngresos->currentText();

    QSqlQuery query;
    query.exec("select sum (valor) as totalDiario from (select dia, mes, anio, valor, formaPago from actividades union select dia, mes, anio, monto valor, formaPago from ventas) where formaPago='"+formaPago+"' and dia='"+dia+"'and mes='"+mes+"'and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalDiario = query.value(0).toFloat();
        ui->mensajeIngresosB->setText("Total Ingreso Diario: $" + QString::number(totalDiario));

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

void DialogFacturacion::filtrarMesAnioIngresos()
{
    QString formaPago = ui->comboBoxFPagoIngresos->currentText();
    QString mes = ui->comboBoxMesIngresos->currentText();
    QString anio = ui->comboBoxAnioIngresos->currentText();

    QSqlQuery query;
    query.exec("select sum (valor) as totalMensual from (select mes, anio, valor, formaPago from actividades union select mes, anio, monto valor, formaPago from ventas) where formaPago='"+formaPago+"' and mes='"+mes+"'and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalMensual = query.value(0).toFloat();
        ui->mensajeIngresosB->setText("Total Ingreso Mensual: $" + QString::number(totalMensual));

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

void DialogFacturacion::filtrarAnioIngresos()
{
    QString formaPago = ui->comboBoxFPagoIngresos->currentText();
    QString anio = ui->comboBoxAnioIngresos->currentText();

    QSqlQuery query;
    query.exec("select sum (valor) as totalAnual from (select anio, valor, formaPago from actividades union select anio, monto valor, formaPago from ventas) where formaPago='"+formaPago+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalAnual = query.value(0).toFloat();
        ui->mensajeIngresosB->setText("Total Ingreso Anual: $" + QString::number(totalAnual));

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

//GUARDAR INGRESOS
//================================================================================
void DialogFacturacion::guardarDiaMesAnioIngresos()
{
    QString formaPago = ui->comboBoxFPagoIngresos->currentText();
    QString cierre = ui->comboBoxCierreIngresos->currentText();
    QString dia = ui->comboBoxDiaIngresos->currentText();
    QString mes = ui->comboBoxMesIngresos->currentText();
    QString anio = ui->comboBoxAnioIngresos->currentText();

    QSqlQuery query;
    query.exec("select sum (valor) as totalDiario from (select dia, mes, anio, valor, formaPago from actividades union select dia, mes, anio, monto valor, formaPago from ventas) where formaPago='"+formaPago+"' and dia='"+dia+"'and mes='"+mes+"'and anio='"+anio+"'");

        int flag = 0;

        while(query.next())
        {
        float totalDiario = query.value(0).toFloat();
        ui->mensajeIngresosB->setText("Total Ingreso Diario: $" + QString::number(totalDiario));
        qDebug()<<  QString::number(totalDiario);

        query.exec("INSERT INTO ingresos (formaPago,cierre,dia,mes,anio,totalDiario)"
                   "VALUES('"+formaPago+"'," "'"+cierre+"'," "'"+dia+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(totalDiario) + ')');
        ui->mensajeIngresosA->setText("GUARDADO EXITOSO!!");

        flag = 1;

        }

    if(flag == 1)
    {
        //qDebug()<<  QString::number(totalFinal);
        qDebug()<< query.lastQuery();
        qDebug()<< "Save Success!!";
    }

    else
    {
        qDebug()<<"ERROR! Impossible do that!!!";
        qDebug()<<"ERROR!"<< query.lastError();
        qDebug()<<query.lastQuery();
        qDebug()<<query.numRowsAffected();
    }
}

void DialogFacturacion::guardarMesAnioIngresos()
{
    QString formaPago = ui->comboBoxFPagoIngresos->currentText();
    QString cierre = ui->comboBoxCierreIngresos->currentText();
    QString mes = ui->comboBoxMesIngresos->currentText();
    QString anio = ui->comboBoxAnioIngresos->currentText();

    QSqlQuery query;
    query.exec("select sum (valor) as totalMensual from (select mes, anio, valor, formaPago from actividades union select mes, anio, monto valor, formaPago from ventas) where formaPago='"+formaPago+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;

        while(query.next())
        {
        float totalMensual = query.value(0).toFloat();
        ui->mensajeIngresosB->setText("Total Ingreso Mensual: $" + QString::number(totalMensual));
        qDebug()<<  QString::number(totalMensual);

        query.exec("INSERT INTO ingresos (formaPago,cierre,mes,anio,totalMensual)"
                   "VALUES('"+formaPago+"'," "'"+cierre+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(totalMensual) + ')');
        ui->mensajeIngresosA->setText("GUARDADO EXITOSO!!");

        flag = 1;

        }

    if(flag == 1)
    {
        //qDebug()<<  QString::number(totalFinal);
        qDebug()<< query.lastQuery();
        qDebug()<< "Save Success!!";
    }

    else
    {
        qDebug()<<"ERROR! Impossible do that!!!";
        qDebug()<<"ERROR!"<< query.lastError();
        qDebug()<<query.lastQuery();
        qDebug()<<query.numRowsAffected();
    }
}

void DialogFacturacion::guardarAnioIngresos()
{
    QString formaPago = ui->comboBoxFPagoIngresos->currentText();
    QString cierre = ui->comboBoxCierreIngresos->currentText();
    QString anio = ui->comboBoxAnioIngresos->currentText();

    QSqlQuery query;
    query.exec("select sum (valor) as totalAnual from (select anio, valor, formaPago from actividades union select anio, monto valor, formaPago from ventas) where formaPago='"+formaPago+"' and anio='"+anio+"'");

        int flag = 0;

        while(query.next())
        {
        float totalAnual = query.value(0).toFloat();
        ui->mensajeIngresosB->setText("Total Ingreso Anual: $" + QString::number(totalAnual));
        qDebug()<<  QString::number(totalAnual);

        query.exec("INSERT INTO ingresos (formaPago,cierre,anio,totalAnual)"
                   "VALUES('"+formaPago+"'," "'"+cierre+"'," "'"+anio+"'," + QString::number(totalAnual) + ')');
        ui->mensajeIngresosA->setText("GUARDADO EXITOSO!!");

        flag = 1;

        }

    if(flag == 1)
    {
        //qDebug()<<  QString::number(totalFinal);
        qDebug()<< query.lastQuery();
        qDebug()<< "Save Success!!";
    }

    else
    {
        qDebug()<<"ERROR! Impossible do that!!!";
        qDebug()<<"ERROR!"<< query.lastError();
        qDebug()<<query.lastQuery();
        qDebug()<<query.numRowsAffected();
    }
}

void DialogFacturacion::listarHistoricoIngresos()
{
    QString consulta;
    consulta.append("SELECT * FROM ingresos");
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
    ui->tableIngresos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableIngresos->insertRow(fila);

            for(int i=0; i<8; i++)
            {
                ui->tableIngresos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeIngresosA->setText("Hay " + counter + " Registro/s en el Historial");
}



//FILTROS INGRESOS BOTONES
//=================================================================================

void DialogFacturacion::on_filtrarDMAingresos_clicked()
{
    filtrarDiaMesAnioIngresos();
}

void DialogFacturacion::on_filtrarMAingresos_clicked()
{
    filtrarMesAnioIngresos();
}

void DialogFacturacion::on_FiltrarAingresos_clicked()
{
    filtrarAnioIngresos();
}

//PERSISTENCIA INGRESOS BUTTONS
//===================================================================================

void DialogFacturacion::on_guardarDMAingresos_clicked()
{
    guardarDiaMesAnioIngresos();
}


void DialogFacturacion::on_guardarDMingresos_clicked()
{
    guardarMesAnioIngresos();
}

void DialogFacturacion::on_guardarAingresos_clicked()
{
    guardarAnioIngresos();
}


//EGRESOS
//===================================================================================


void DialogFacturacion::filtrarDiaMesAnioEgresos()
{
    QString dia = ui->comboBoxDiaEgresos->currentText();
    QString mes = ui->comboBoxMesEgresos->currentText();
    QString anio = ui->comboBoxAnioEgresos->currentText();

    QSqlQuery query;
    query.exec("select sum (monto) as totalDiario from (select dia, mes, anio, monto from pagoDocentes union all select dia, mes, anio, monto monto from pagos) where dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalDiario = query.value(0).toFloat();
        ui->mensajeEgresosB->setText("Total Egreso Diario: $" + QString::number(totalDiario));

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

void DialogFacturacion::filtrarMesAnioEgresos()
{
    QString mes = ui->comboBoxMesEgresos->currentText();
    QString anio = ui->comboBoxAnioEgresos->currentText();

    QSqlQuery query;
    query.exec("select sum (monto) as totalMensual from (select mes, anio, monto from pagoDocentes union all select mes, anio, monto monto from pagos) where mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalMensual = query.value(0).toFloat();
        ui->mensajeEgresosB->setText("Total Egreso Mensual: $" + QString::number(totalMensual));

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

void DialogFacturacion::filtrarAnioEgresos()
{
    QString anio = ui->comboBoxAnioEgresos->currentText();

    QSqlQuery query;
    query.exec("select sum (monto) as totalAnual from (select anio, monto from pagoDocentes union all select anio, monto monto from pagos) where anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalAnual = query.value(0).toFloat();
        ui->mensajeEgresosB->setText("Total Egreso Anual: $" + QString::number(totalAnual));

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

void DialogFacturacion::guardarDiaMesAnioEgresos()
{
    QString cierre = ui->comboBoxCierreEgresos->currentText();
    QString dia = ui->comboBoxDiaEgresos->currentText();
    QString mes = ui->comboBoxMesEgresos->currentText();
    QString anio = ui->comboBoxAnioEgresos->currentText();

    QSqlQuery query;
    query.exec("select sum (monto) as totalDiario from (select dia, mes, anio, monto from pagoDocentes union all select dia, mes, anio, monto monto from pagos) where dia='"+dia+"' and mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalDiario = query.value(0).toFloat();
        ui->mensajeEgresosB->setText("Total Egreso Diario: $" + QString::number(totalDiario));

        query.exec("INSERT INTO egresos (cierre,dia,mes,anio,totalDiario)"
                   "VALUES('"+cierre+"'," "'"+dia+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(totalDiario) + ')');
        ui->mensajeEgresosA->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::guardarMesAnioEgresos()
{
    QString cierre = ui->comboBoxCierreEgresos->currentText();
    QString mes = ui->comboBoxMesEgresos->currentText();
    QString anio = ui->comboBoxAnioEgresos->currentText();

    QSqlQuery query;
    query.exec("select sum (monto) as totalMensual from (select mes, anio, monto from pagoDocentes union all select mes, anio, monto monto from pagos) where mes='"+mes+"' and anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalMensual = query.value(0).toFloat();
        ui->mensajeEgresosB->setText("Total Egreso Mensual: $" + QString::number(totalMensual));

        query.exec("INSERT INTO egresos (cierre,mes,anio,totalMensual)"
                   "VALUES('"+cierre+"'," "'"+mes+"'," "'"+anio+"'," + QString::number(totalMensual) + ')');
        ui->mensajeEgresosA->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::guardarAnioEgresos()
{
    QString cierre = ui->comboBoxCierreEgresos->currentText();
    QString anio = ui->comboBoxAnioEgresos->currentText();

    QSqlQuery query;
    query.exec("select sum (monto) as totalAnual from (select anio, monto from pagoDocentes union all select anio, monto monto from pagos) where anio='"+anio+"'");

        int flag = 0;
       while(query.next())
        {
        float totalAnual = query.value(0).toFloat();
        ui->mensajeEgresosB->setText("Total Egreso Anual: $" + QString::number(totalAnual));

        query.exec("INSERT INTO egresos (cierre,anio,totalAnual)"
                   "VALUES('"+cierre+"'," "'"+anio+"'," + QString::number(totalAnual) + ')');
        ui->mensajeEgresosA->setText("GUARDADO EXITOSO!!");

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

void DialogFacturacion::listarHistoricoEgresos()
{
    QString consulta;
    consulta.append("SELECT * FROM egresos");
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
    ui->tableEgresos->setRowCount(0);

    while(consultar.next())
      {
         ui->tableEgresos->insertRow(fila);

            for(int i=0; i<7; i++)
            {
                ui->tableEgresos->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeEgresosA->setText("Hay " + counter + " Registro/s en el Historial");
}




//FILTRO BOTONES EGRESOS
//=====================================================================================

void DialogFacturacion::on_filtrarDMAEgresos_clicked()
{
    filtrarDiaMesAnioEgresos();
}

void DialogFacturacion::on_filtrarMAEgresos_clicked()
{
    filtrarMesAnioEgresos();
}

void DialogFacturacion::on_FiltrarAEgresos_clicked()
{
    filtrarAnioEgresos();
}

void DialogFacturacion::on_guardarDMAEgresos_clicked()
{
   guardarDiaMesAnioEgresos();
}

void DialogFacturacion::on_guardarDMEgresos_clicked()
{
    guardarMesAnioEgresos();
}

void DialogFacturacion::on_guardarAEgresos_clicked()
{
    guardarAnioEgresos();
}




