#include "dialoginscripcion.h"
#include "ui_dialoginscripcion.h"
#include <QDebug>
#include <time.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DialogInscripcion::DialogInscripcion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInscripcion)
{
    ui->setupUi(this);
    setWindowTitle("Ficha Alumnos");
}

DialogInscripcion::~DialogInscripcion()
{
    delete ui;
}

void DialogInscripcion::addInscription()
{
    Fecha fechaN;
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
    consulta.append("INSERT INTO personas ("
                    "nombreApellido,"
                    "dni,"
                    "fechaNacimiento,"
                    "edad,"
                    "direccion,"
                    "localidad,"
                    "telefono,"
                    "movil,"
                    "email,"
                    "observaciones,"
                    "nombrePariente,"
                    "parentezco,"
                    "telContacto"
                    ")"
                    "VALUES("
                    "'"+ui->nombre->text()+"',"
                    "'"+ui->dni->text()+"',"
                    "'"+ fnDia.rightJustified(2, '0') + "/" +fnMes.rightJustified(2, '0') + "/" + fnAnio.rightJustified(4, '0') +"',"
                    ""+age+","
                    "'"+ui->direccion->text()+"',"
                    "'"+ui->localidad->currentText()+"',"
                    "'"+ui->telefono->text()+"',"
                    "'"+ui->movil->text()+"',"
                    "'"+ui->mail->text()+"',"
                    "'"+ui->observaciones->toPlainText()+"',"
                    "'"+ui->nombreApellido->text()+"',"
                    "'"+ui->parentesco->currentText()+"',"
                    "'"+ui->telContacto->text()+"'"
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

void DialogInscripcion::clearScreen()
{
    ui->nombre->clear();
    ui->dni->clear();
    ui->dia->clear();
    ui->mes->clear();
    ui->anio->clear();
    ui->direccion->clear();
    ui->telefono->clear();
    ui->movil->clear();
    ui->mail->clear();
    ui->observaciones->clear();
    ui->nombreApellido->clear();
    ui->telContacto->clear();
}

int DialogInscripcion::calculoAntiguedad(Fecha fecha1)
{
    Fecha fecha2;
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

int DialogInscripcion::regularBisiesto(int anio)
{
    return ((anio%4 == 0 && anio%100 != 0) || (anio%400) == 0);
}

int DialogInscripcion::numeroBisiestos(int anio)
{
    return anio / 4 - anio / 100 + anio / 400;
}

int DialogInscripcion::diaDelAnio(Fecha fecha)
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





void DialogInscripcion::on_inscribir_clicked()
{
    addInscription();
    clearScreen();

}

void DialogInscripcion::on_cancelar_clicked()
{
    reject();
}
