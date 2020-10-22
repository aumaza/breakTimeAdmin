#include "dialogaltadocente.h"
#include "ui_dialogaltadocente.h"
#include <QDebug>
#include <time.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DialogAltaDocente::DialogAltaDocente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAltaDocente)
{
    ui->setupUi(this);
    setWindowTitle("Alta de Docentes");
}

DialogAltaDocente::~DialogAltaDocente()
{
    delete ui;
}




//AGREGAR DOCENTE
//=========================================================================
void DialogAltaDocente::addDocente()
{
    eFecha fechaN;
    QString fnDia = ui->dia->text();
    fechaN.dia = fnDia.toInt();
    QString fnMes = ui->mes->text();
    fechaN.mes = fnMes.toInt();
    QString fnAnio = ui->anio->text();
    fechaN.anio = fnAnio.toInt();

    int edad = calculoAntiguedad(fechaN);
    qDebug()<<edad;

    QString age = QString::number(edad);


    QString consulta;
    consulta.append("INSERT INTO docentes ("
                    "nombreApellido,"
                    "dni,"
                    "fechaNacimiento,"
                    "edad,"
                    "direccion,"
                    "localidad,"
                    "telefono,"
                    "movil,"
                    "email"
                    ")"
                    "VALUES("
                    "'"+ui->nompreApellido->text()+"',"
                    "'"+ui->dni->text()+"',"
                    "'"+ fnDia.rightJustified(2, '0') + "/" +fnMes.rightJustified(2, '0') + "/" + fnAnio.rightJustified(4, '0') +"',"
                    ""+age+","
                    "'"+ui->direccion->text()+"',"
                    "'"+ui->localidad->currentText()+"',"
                    "'"+ui->telefono->text()+"',"
                    "'"+ui->movil->text()+"',"
                    "'"+ui->email->text()+"'"
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

void DialogAltaDocente::cleanScreen()
{
    ui->nompreApellido->clear();
    ui->dni->clear();
    ui->dia->clear();
    ui->mes->clear();
    ui->anio->clear();
    ui->direccion->clear();
    ui->telefono->clear();
    ui->movil->clear();
    ui->email->clear();

}

void DialogAltaDocente::nuevaBusqueda()
{
    ui->nompreApellido->clear();
    ui->dni->clear();
    ui->dia->clear();
    ui->mes->clear();
    ui->anio->clear();
    ui->direccion->clear();
    ui->telefono->clear();
    ui->movil->clear();
    ui->email->clear();
    ui->mensaje->clear();
}

void DialogAltaDocente::buscarDocente()
{
    QString nombreApellido = ui->nompreApellido->text();
    QSqlQuery consultar;
    consultar.prepare("SELECT * from docentes where nombreApellido='"+nombreApellido+"'");

    int flag = 0;

    if(consultar.exec())
    {
        while(consultar.next())
        {
            ui->nompreApellido->setText(consultar.value(1).toString());
            ui->dni->setText(consultar.value(2).toString());
            ui->direccion->setText((consultar.value(5).toString()));
            ui->localidad->setCurrentIndex(ui->localidad->findText(consultar.value(6).toString()));
            ui->telefono->setText((consultar.value(7).toString()));
            ui->movil->setText(consultar.value(8).toString());
            ui->email->setText((consultar.value(9).toString()));
            flag = 1;

        }

        if(flag == 1)
        {
           qDebug() << "All registers are shown Succesfully";
           ui->mensaje->setText("REGISTRO ENCONTRADO!!!");
        }

        else
        {
           ui->mensaje->setText("REGISTRO INEXISTENTE!!");
           qDebug()<<"REGISTRO INEXISTENTE!!";
        }
    }
}

void DialogAltaDocente::editarDocente()
{
    QString nombre = ui->nompreApellido->text();
    QString dni = ui->dni->text();
    QString direccion = ui->direccion->text();
    QString localidad = ui->localidad->currentText();
    QString telefono = ui->telefono->text();
    QString movil = ui->movil->text();
    QString email = ui->email->text();

    eFecha fechaN;
    QString fnDia = ui->dia->text();
    fechaN.dia = fnDia.toInt();
    QString fnMes = ui->mes->text();
    fechaN.mes = fnMes.toInt();
    QString fnAnio = ui->anio->text();
    fechaN.anio = fnAnio.toInt();

    int edad = calculoAntiguedad(fechaN);
    qDebug()<<edad;

    QString age = QString::number(edad);

    QSqlQuery qry;
    qry.prepare("UPDATE docentes set nombreApellido='"+nombre+"',dni='"+dni+"', fechaNacimiento='"+ fnDia.rightJustified(2, '0') + "/" +fnMes.rightJustified(2, '0') + "/" + fnAnio.rightJustified(4, '0') +"', edad='"+age+"', direccion='"+direccion+"',localidad='"+localidad+"',telefono='"+telefono+"',movil='"+movil+"',email='"+email+"' where nombreApellido='"+nombre+"'");

    if(qry.exec())
    {
        ui->mensaje->setText("REGISTRO ACTUALIZADO EXITOSAMENTE");
        qDebug() << "User has been update Succesfully";

    }

    else
    {
        qDebug()<<"ERROR! Impossible update...";
        qDebug()<<"ERROR!"<< qry.executedQuery();
        qDebug()<<"ERROR!"<< qry.lastError();
    }
}

void DialogAltaDocente::borrarDocente()
{
    QString nombre = ui->nompreApellido->text();

    QSqlQuery consultar;
    consultar.prepare("Delete from docentes where nombreApellido='"+nombre+"'");


    if(consultar.exec())
    {
        ui->mensaje->setText("REGISTRO ELIMINADO!!");
        qDebug() << "User has been deleted Succesfully";

    }

    else
    {
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}



//METODOS CALCULO EDAD
//=========================================================================
int DialogAltaDocente::calculoAntiguedad(eFecha fecha1)
{
    eFecha fecha2;
    int difDias = 0;
    int anios = 0;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);

    fecha2.dia = tm->tm_mday;
    fecha2.mes = tm->tm_mon+1;
    fecha2.anio = 1900+tm->tm_year;

    // Cálculo del intervalo fecha1 -> fecha2
    // no se tienen en cuenta los años en este punto porque la corrección se realiza después


    difDias = diaDelAnio( fecha2 ) - diaDelAnio( fecha1 );

    if( fecha1.anio != fecha2.anio )
    {
        // Días por los años completos
        difDias += (fecha2.anio - fecha1.anio - 1) * 365;
        difDias += numeroBisiestos(fecha2.anio - 1) - numeroBisiestos(fecha1.anio);

        // Cálculo correspondiente al intervalo fecha1 -> fin año fecha1
        fecha1.dia = 31;
        fecha1.mes = 12;
        difDias += diaDelAnio( fecha1 );
        anios = difDias / 365;
    }

    return anios;
}

int DialogAltaDocente::regularBisiesto(int anio)
{
    return ((anio%4 == 0 && anio%100 != 0) || (anio%400) == 0);
}

int DialogAltaDocente::numeroBisiestos(int anio)
{
    return anio / 4 - anio / 100 + anio / 400;
}

int DialogAltaDocente::diaDelAnio(eFecha fecha)
{
    int tot_dias[] = { 00,31,28,31,30,31,30,31,31,30,31,30,31 };

    int dias = fecha.dia;
    int mes;

    for( mes = 1; mes < fecha.mes; ++mes )
    {
        dias += tot_dias[mes];

        if( fecha.mes > 2 )
        {
            dias += regularBisiesto( fecha.anio );
        }
    }
    return dias;
}



//BUTTONS
//=========================================================================

void DialogAltaDocente::on_back_clicked()
{
    reject();
}

void DialogAltaDocente::on_pushButton_5_clicked()
{
    addDocente();
    cleanScreen();
}

void DialogAltaDocente::on_editar_clicked()
{
    editarDocente();
    cleanScreen();
}

void DialogAltaDocente::on_buscar_clicked()
{
    buscarDocente();
}

void DialogAltaDocente::on_nuevaBusqueda_clicked()
{
    nuevaBusqueda();
}

void DialogAltaDocente::on_borrar_clicked()
{
    borrarDocente();
    cleanScreen();
}
