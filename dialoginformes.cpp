#include "dialoginformes.h"
#include "ui_dialoginformes.h"


#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFile>
#include <QLatin1Char>
#include <QTextStream>
#include <QSqlRecord>
#include <QString>



DialogInformes::DialogInformes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInformes)
{
    ui->setupUi(this);
    setWindowTitle("Informes");

    listarInscriptos();
    listarActividades();
    listarPacks();
    listarStyles();
    listarDocentes();
    listarTipoActividad();
}

DialogInformes::~DialogInformes()
{
    delete ui;
}

void DialogInformes::listarInscriptos()
{
    QString consulta;
    consulta.append("SELECT * FROM personas");
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
    ui->tablePersonas->setRowCount(0);

    while(consultar.next())
      {
         ui->tablePersonas->insertRow(fila);

            for(int i=0; i<14; i++)
            {
                ui->tablePersonas->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));

            }
            count++;
            fila++;
      }
    QString contador = QString::number(count);
    ui->mensajeInscriptos->setText("Hay " + contador + " Inscripto/s");
}

void DialogInformes::listarActividades()
{
    QString consulta;
    consulta.append("SELECT * FROM actividades");
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
    ui->tableClases->setRowCount(0);

    while(consultar.next())
      {
         ui->tableClases->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableClases->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString contador = QString::number(count);
    ui->mensaje->setText("Hay " + contador + " Registro/s");
}

void DialogInformes::listarPacks()
{
    QString consulta;
    consulta.append("SELECT * FROM packs");
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
    ui->tablePacks->setRowCount(0);

    while(consultar.next())
      {
         ui->tablePacks->insertRow(fila);

            for(int i=0; i<1; i++)
            {
                ui->tablePacks->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajePacks->setText("Hay " + counter + " Registro/s");
}

void DialogInformes::listarStyles()
{
    QString consulta;
    consulta.append("SELECT * FROM stylos");
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
    ui->tableStyles->setRowCount(0);

    while(consultar.next())
      {
         ui->tableStyles->insertRow(fila);

            for(int i=0; i<1; i++)
            {
                ui->tableStyles->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeStyles->setText("Hay " + counter + " Registro/s");
}

void DialogInformes::listarDocentes()
{
    QString consulta;
    consulta.append("SELECT * FROM docentes");
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
    ui->tableDocentes->setRowCount(0);

    while(consultar.next())
      {
         ui->tableDocentes->insertRow(fila);

            for(int i=0; i<9; i++)
            {
                ui->tableDocentes->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));

            }
            count++;
            fila++;
      }
    QString contador = QString::number(count);
    ui->mensajeDocentes->setText("Hay " + contador + " Docente/s");
}

void DialogInformes::listarTipoActividad()
{
    QString consulta;
    consulta.append("SELECT * FROM tipoActividad");
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
    ui->tableTipoActividad->setRowCount(0);

    while(consultar.next())
      {
         ui->tableTipoActividad->insertRow(fila);

            for(int i=0; i<1; i++)
            {
                ui->tableTipoActividad->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString counter = QString::number(count);
    ui->mensajeTipoActividad->setText("Hay " + counter + " Tipo/s de Actividad/es");
}



void DialogInformes::on_pushButton_2_clicked()
{
    reject();
}

//EXPORT CSV
//=====================================================================


QString DialogInformes::escapedCSV(QString unexc)
{

    if (!unexc.contains(QLatin1Char(',')))
    {
       return unexc;
    }
    return '\"' + unexc.replace(QLatin1Char('\"'), QString("\"\"")) + '\"';
}


void DialogInformes::queryToCsvDocentes()
{

    QString name;
    name.append("SqlBase.sqlite");
    db.setDatabaseName(name);

    QString consulta;
    consulta.append("SELECT * FROM docentes");
    QSqlQuery consultar;
    consultar.prepare(consulta);
        QFile csvFile ("docentes.csv");

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
            ui->mensajeDocentes->setText("Archivo Exportado con Exito!!");
}

void DialogInformes::querytoCsvActividades()
{
    QString name;
    name.append("SqlBase.sqlite");
    db.setDatabaseName(name);

    QString consulta;
    consulta.append("SELECT * FROM actividades");
    QSqlQuery consultar;
    consultar.prepare(consulta);
        QFile csvFile ("actividades.csv");

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
            ui->mensaje->setText("Archivo Exportado con Exito!!");
}

void DialogInformes::queryToCsvIncripciones()
{
    QString name;
    name.append("SqlBase.sqlite");
    db.setDatabaseName(name);

    QString consulta;
    consulta.append("SELECT * FROM personas");
    QSqlQuery consultar;
    consultar.prepare(consulta);
        QFile csvFile ("personas.csv");

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
            ui->mensajeInscriptos->setText("Archivo Exportado con Exito!!");
}








//EXPORT CSV BUTTONS
//=====================================================================

void DialogInformes::on_exportCSV_clicked()
{
    queryToCsvDocentes();
}

void DialogInformes::on_exportCSV_2_clicked()
{
    querytoCsvActividades();
}

void DialogInformes::on_exportCSV_3_clicked()
{
    queryToCsvIncripciones();
}
