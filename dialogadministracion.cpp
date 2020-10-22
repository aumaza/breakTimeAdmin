#include "dialogadministracion.h"
#include "ui_dialogadministracion.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QtSql/QSqlError>
#include <time.h>

DialogAdministracion::DialogAdministracion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAdministracion)
{
    ui->setupUi(this);
    setWindowTitle("Gestion de Datos");

    cargarComboBoxPack();
    cargarComboBoxStyles();
    cargarComoBoxDocente();
    cargarComboBoxNombreApellido();
    cargarComboBoxTipoActividad();
    cargarComboBoxId();
    listarActividades();

}

DialogAdministracion::~DialogAdministracion()
{
    delete ui;
}




//===========================================================================================================================
//METODOS PARA LA SOLAPA EDICION DE INSCRIPCIONES

void DialogAdministracion::buscarDNI()
{
    QString dni = ui->dni->text();
    QSqlQuery consultar;
    consultar.prepare("SELECT * from personas where dni='"+dni+"'");


    if(consultar.exec())
    {
        while(consultar.next())
        {
            ui->comboBoxNombreApellido->setCurrentIndex(ui->comboBoxNombreApellido->findText(consultar.value(1).toString()));
            ui->dni->setText(consultar.value(2).toString());
            ui->direccion->setText((consultar.value(5).toString()));
            ui->localidad->setCurrentIndex(ui->localidad->findText(consultar.value(6).toString()));
            ui->telefono->setText((consultar.value(7).toString()));
            ui->movil->setText(consultar.value(8).toString());
            ui->mail->setText((consultar.value(9).toString()));
            ui->observaciones->setPlainText((consultar.value(10).toString()));
            ui->nombreApellido->setText((consultar.value(11).toString()));
            ui->parentesco->setCurrentIndex(ui->parentesco->findText((consultar.value(12).toString())));
            ui->telContacto->setText((consultar.value(13).toString()));

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

void DialogAdministracion::buscarNombreApellido()
{
    QString nombre = ui->comboBoxNombreApellido->currentText();

    QSqlQuery consultar;
    consultar.prepare("SELECT * from personas where nombreApellido='"+nombre+"'");


    if(consultar.exec())
    {
        while(consultar.next())
        {
            ui->comboBoxNombreApellido->setCurrentIndex(ui->comboBoxNombreApellido->findText(consultar.value(1).toString()));
            ui->dni->setText(consultar.value(2).toString());
            ui->direccion->setText((consultar.value(5).toString()));
            ui->localidad->setCurrentIndex(ui->localidad->findText(consultar.value(6).toString()));
            ui->telefono->setText((consultar.value(7).toString()));
            ui->movil->setText(consultar.value(8).toString());
            ui->mail->setText((consultar.value(9).toString()));
            ui->observaciones->setPlainText((consultar.value(10).toString()));
            ui->nombreApellido->setText((consultar.value(11).toString()));
            ui->parentesco->setCurrentIndex(ui->parentesco->findText((consultar.value(12).toString())));
            ui->telContacto->setText((consultar.value(13).toString()));

        }
        qDebug() << "All registers are shown Succesfully";
        ui->mensaje->setText("REGISTRO ENCONTRADO!!!");
    }

    else
    {
        ui->mensaje->setText("REGISTRO INEXISTENTE!!");
        qDebug()<<"ERROR! Impossible show table registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }

}

void DialogAdministracion::editarPersona()
{
    QString nombre = ui->comboBoxNombreApellido->currentText();
    QString dni = ui->dni->text();
    QString direccion = ui->direccion->text();
    QString localidad = ui->localidad->currentText();
    QString telefono = ui->telefono->text();
    QString movil = ui->movil->text();
    QString email = ui->mail->text();
    QString observaciones = ui->observaciones->toPlainText();
    QString nombrePariente = ui->nombreApellido->text();
    QString parentezco = ui->parentesco->currentText();
    QString telContacto = ui->telContacto->text();


    aFecha fechaN;
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
    qry.prepare("UPDATE personas set nombreApellido='"+nombre+"',dni='"+dni+"', fechaNacimiento='"+ fnDia.rightJustified(2, '0') + "/" +fnMes.rightJustified(2, '0') + "/" + fnAnio.rightJustified(4, '0') +"', edad='"+age+"', direccion='"+direccion+"',localidad='"+localidad+"',telefono='"+telefono+"',movil='"+movil+"',email='"+email+"' ,observaciones='"+observaciones+"', nombrePariente='"+nombrePariente+"', parentezco='"+parentezco+"', telContacto='"+telContacto+"' where dni='"+dni+"'");


    if(qry.exec())
    {
        ui->mensaje->setText("ACTUALIZADO CON EXITO");
        qDebug() << "User has been update Succesfully";

    }

    else
    {
        qDebug()<<"ERROR! Impossible update...";
        qDebug()<<"ERROR!"<< qry.executedQuery();
        qDebug()<<"ERROR!"<< qry.lastError();
    }
}

void DialogAdministracion::cleanScreen()
{
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

void DialogAdministracion::borrarPersona()
{
    QString dni = ui->dni->text();

    QSqlQuery consultar;
    consultar.prepare("Delete from personas where dni='"+dni+"'");


    if(consultar.exec())
    {
        ui->mensaje->setText("REGISTRO ELIMINADO!!");
        qDebug() << "User has been deleted Succesfully";

    }

    else
    {
        ui->mensaje->setText("IMPOSIBLE ELIMINAR!!");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}


void DialogAdministracion::on_volver_clicked()
{
    reject();
}

void DialogAdministracion::on_buscarDNI_clicked()
{
    buscarDNI();
}

void DialogAdministracion::on_busquedaNombre_clicked()
{
    buscarNombreApellido();
}



void DialogAdministracion::on_modificar_clicked()
{
    editarPersona();
}

void DialogAdministracion::on_clean_clicked()
{
    cleanScreen();
}

void DialogAdministracion::on_eliminar_clicked()
{
    borrarPersona();
}

//==============================================================================================================================
//METODOS PARA LA SOLAPA ACTIVIDADES (GESTION DE CLASES)

void DialogAdministracion::buscarNombreAlumno()
{
    QString nombreAlumno = ui->comboBoxAlumno->currentText();

    QSqlQuery consultar;
    consultar.prepare("SELECT * from actividades where nombreApellido='"+nombreAlumno+"'");


    if(consultar.exec())
    {
        while(consultar.next())
        {
            ui->comboBoxTipoActividad->setCurrentIndex(ui->comboBoxTipoActividad->findText(consultar.value(1).toString()));
            ui->comboBoxAlumno->setCurrentIndex(ui->comboBoxAlumno->findText(consultar.value(2).toString()));
            ui->style->setCurrentIndex(ui->style->findText(consultar.value(3).toString()));
            ui->pack->setCurrentIndex(ui->pack->findText(consultar.value(4).toString()));
            ui->comboBoxDia->setCurrentIndex(ui->comboBoxDia->findText(consultar.value(5).toString()));
            ui->mes_3->setCurrentIndex(ui->mes_3->findText(consultar.value(6).toString()));
            ui->anio_3->setCurrentIndex(ui->anio_3->findText(consultar.value(7).toString()));
            ui->comboBoxDocente->setCurrentIndex(ui->comboBoxDocente->findText(consultar.value(8).toString()));
            ui->monto->setText(consultar.value(9).toString());
            ui->formaPago->setCurrentIndex(ui->formaPago->findText(consultar.value(10).toString()));

        }
        qDebug() << "All registers are shown Succesfully";
        ui->message->setText("REGISTRO ENCONTRADO!!!");
    }

    else
    {
        ui->message->setText("REGISTRO INEXISTENTE!!");
        qDebug()<<"ERROR! Impossible show table registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAdministracion::buscarActividad()
{
    QString actividad = ui->comboBoxTipoActividad->currentText();

    QSqlQuery consultar;
    consultar.prepare("SELECT * from actividades where actividad='"+actividad+"'");


    if(consultar.exec())
    {
        while(consultar.next())
        {
            ui->comboBoxTipoActividad->setCurrentIndex(ui->comboBoxTipoActividad->findText(consultar.value(1).toString()));
            ui->comboBoxAlumno->setCurrentIndex(ui->comboBoxAlumno->findText(consultar.value(2).toString()));
            ui->style->setCurrentIndex(ui->style->findText(consultar.value(3).toString()));
            ui->pack->setCurrentIndex(ui->pack->findText(consultar.value(4).toString()));
            ui->comboBoxDia->setCurrentIndex(ui->comboBoxDia->findText(consultar.value(5).toString()));
            ui->mes_3->setCurrentIndex(ui->mes_3->findText(consultar.value(6).toString()));
            ui->anio_3->setCurrentIndex(ui->anio_3->findText(consultar.value(7).toString()));
            ui->comboBoxDocente->setCurrentIndex(ui->comboBoxDocente->findText(consultar.value(8).toString()));
            ui->monto->setText(consultar.value(9).toString());
            ui->formaPago->setCurrentIndex(ui->formaPago->findText(consultar.value(10).toString()));

        }

        qDebug() << "All registers are shown Succesfully";
        ui->message->setText("REGISTRO ENCONTRADO!!!");
    }

    else
    {
        ui->message->setText("REGISTRO INEXISTENTE!!");
        qDebug()<<"ERROR! Impossible show table registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAdministracion::cargarComboBoxPack()
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

void DialogAdministracion::cargarComboBoxStyles()
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
        ui->styles->setModel(model);
        ui->styles_2->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAdministracion::cargarComoBoxDocente()
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

void DialogAdministracion::cargarComboBoxNombreApellido()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT nombreApellido FROM personas");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->comboBoxNombreApellido->setModel(model);
        ui->comboBoxAlumno->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAdministracion::cargarComboBoxTipoActividad()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT descripcion FROM tipoActividad");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->comboBoxTipoActividad->setModel(model);
        ui->comboBoxTipoActividad_1->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAdministracion::cargarComboBoxId()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString consulta;
    consulta.append("SELECT id FROM actividades");
    QSqlQuery consultar;
    consultar.prepare(consulta);


    if(consultar.exec())
    {
        model->setQuery(consultar);
        ui->comboBoxId->setModel(model);
        qDebug() << "All registers are loaded Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible loaded registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAdministracion::editarActividades()
{

    QString id = ui->comboBoxId->currentText();
    QString actividad = ui->comboBoxTipoActividad->currentText();
    QString nombreAlumno = ui->comboBoxAlumno->currentText();
    QString style = ui->style->currentText();
    QString pack = ui->pack->currentText();
    QString dia = ui->comboBoxDia->currentText();
    QString mes = ui->mes_3->currentText();
    QString anio = ui->anio_3->currentText();
    QString docente = ui->comboBoxDocente->currentText();
    QString valor = ui->monto->text();
    QString formaPago = ui->formaPago->currentText();

    QSqlQuery qry;
    qry.prepare("UPDATE actividades set actividad='"+actividad+"',nombreApellido='"+nombreAlumno+"',style='"+style+"',pack='"+pack+"',dia='"+dia+"', mes='"+mes+"',anio='"+anio+"', docente='"+docente+"',valor='"+valor+"',formaPago='"+formaPago+"' where id='"+id+"'");
    //insertar.prepare(consulta);

    if(qry.exec())
    {
        ui->message->setText("REGISTRO ACTUALIZADO EXITOSAMENTE");
        qDebug() << "User has been update Succesfully";

    }

    else
    {
        qDebug()<<"ERROR! Impossible update...";
        qDebug()<<"ERROR!"<< qry.executedQuery();
        qDebug()<<"ERROR!"<< qry.lastError();
    }
}

void DialogAdministracion::borrarActividad()
{
    QString id = ui->comboBoxId->currentText();

    QSqlQuery consultar;
    consultar.prepare("Delete from actividades where id='"+id+"'");


    if(consultar.exec())
    {
        ui->message->setText("REGISTRO ELIMINADO!!");
        qDebug() << "User has been deleted Succesfully";

    }

    else
    {
        ui->message->setText("IMPOSIBLE ELIMINAR!!");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAdministracion::cleanScreen2()
{
        ui->comboBoxTipoActividad->clear();
        ui->style->clear();
        ui->pack->clear();
        ui->monto->clear();
        ui->formaPago->clear();
}

void DialogAdministracion::listarActividades()
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
    ui->tableAct->setRowCount(0);

    while(consultar.next())
      {
         ui->tableAct->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableAct->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString contador = QString::number(count);
    ui->message->setText("Hay " + contador + " Registro/s");
}


void DialogAdministracion::on_search2_clicked()
{
    buscarNombreAlumno();
}

void DialogAdministracion::on_search_clicked()
{
    buscarActividad();
}

void DialogAdministracion::on_mod_clicked()
{
    editarActividades();
}

void DialogAdministracion::on_erase_clicked()
{
    borrarActividad();
    cleanScreen2();
}

void DialogAdministracion::on_cleanScreen_clicked()
{
    cleanScreen2();
}

//METODOS PARA SOLAPA BUSQUEDA DE ACTIVIDADES

void DialogAdministracion::buscarActividades()
{
    QString actividad = ui->comboBoxTipoActividad_1->currentText();

    QString consulta;
    consulta.append("SELECT * FROM actividades where actividad='"+actividad+"'");
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
    int count= 0;
    int fila = 0;
    ui->tableActividades->setRowCount(0);

    while(consultar.next())
      {
         ui->tableActividades->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tableActividades->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString contador = QString::number(count);
    ui->mensajeActividades->setText("Hay " + contador + " Actividad/es en Curso");
}

void DialogAdministracion::buscarAlumno()
{
    QString alumno = ui->alumno->text();

    QString consulta;
    consulta.append("SELECT * FROM actividades where nombreApellido='"+alumno+"'");
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
    QString contador = QString::number(count);
    ui->mensajeAlumnos->setText("Inscripto en " + contador + " Actividad/es");
}

void DialogAdministracion::buscarAlummo2()
{
    QString alumno = ui->nombreAlumno->text();

    QString consulta;
    consulta.append("SELECT * FROM actividades where nombreApellido='"+alumno+"'");
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
    ui->tablePresentismo->setRowCount(0);

    while(consultar.next())
      {
         ui->tablePresentismo->insertRow(fila);

            for(int i=0; i<10; i++)
            {
                ui->tablePresentismo->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString contador = QString::number(count);
    ui->mensajePresentismo->setText("Inscripto en " + contador + " Actividad/es");
}

void DialogAdministracion::cargarPresentismo()
{
    QString consulta;
    consulta.append("INSERT INTO presentismo ("
                    "nombreAlumno,"
                    "style,"
                    "dia,"
                    "mes,"
                    "anio,"
                    "observaciones"
                    ")"
                    "VALUES("
                    "'"+ui->lineEditAlumno->text()+"',"
                    "'"+ui->styles->currentText()+"',"
                    "'"+ui->comboBoxDia_2->currentText()+"',"
                    "'"+ui->mes_4->currentText()+"',"
                    "'"+ui->anio_4->currentText()+"',"
                    "'"+ui->observaciones_2->toPlainText()+"'"
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

    if(insertar.exec())
    {
        ui->mensajePresentismo->setText("REGISTRO AGREGADO CON EXITO!!!");
        qDebug() << "Register has been insert Succesfully";

    }

    else
    {
        ui->mensajePresentismo->setText("ERROR...NO SE HA PODIDO AGREGAR EL REGISTRO");
        qDebug()<<"ERROR! Impossible insert...";
        qDebug()<<"ERROR!"<< insertar.executedQuery();
        qDebug()<<"ERROR!"<< insertar.lastError();
    }
}

void DialogAdministracion::clearPresentismo()
{
    ui->lineEditAlumno->clear();
}

void DialogAdministracion::listarPresentismoAlumno()
{
   QString nombre = ui->nombreAlumno_2->text();

    QString consulta;
    consulta.append("SELECT * FROM presentismo where nombreAlumno='"+nombre+"'");
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
    ui->tableHisPres->setRowCount(0);

    while(consultar.next())
      {
         ui->tableHisPres->insertRow(fila);

            for(int i=0; i<6; i++)
            {
                ui->tableHisPres->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
            }
            count++;
            fila++;
    }
    QString contador = QString::number(count);
    ui->mensajeHisPre->setText("Hay " + contador + " Presente/s");
}

void DialogAdministracion::listarPresentismoStyle()
{
    QString style = ui->styles_2->currentText();

     QString consulta;
     consulta.append("SELECT * FROM presentismo where style='"+style+"'");
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
     ui->tableHisPres->setRowCount(0);

     while(consultar.next())
       {
          ui->tableHisPres->insertRow(fila);

             for(int i=0; i<6; i++)
             {
                 ui->tableHisPres->setItem(fila,i,new QTableWidgetItem(consultar.value(i+1).toByteArray().constData()));
             }
             count++;
             fila++;
     }
     QString contador = QString::number(count);
     ui->mensajeHisPre->setText("Hay " + contador + " Presente/s");
}

void DialogAdministracion::on_buscar_2_clicked()
{
    buscarActividades();
}



void DialogAdministracion::on_search_3_clicked()
{
    buscarAlumno();
}



void DialogAdministracion::on_comboBoxId_currentIndexChanged()
{
    QString id = ui->comboBoxId->currentText();

    QSqlQuery consultar;
    consultar.prepare("SELECT * from actividades where id='"+id+"'");


    if(consultar.exec())
    {
        while(consultar.next())
        {
            ui->comboBoxTipoActividad->setCurrentIndex(ui->comboBoxTipoActividad->findText(consultar.value(1).toString()));
            ui->comboBoxAlumno->setCurrentIndex(ui->comboBoxAlumno->findText(consultar.value(2).toString()));
            ui->style->setCurrentIndex(ui->style->findText(consultar.value(3).toString()));
            ui->pack->setCurrentIndex(ui->pack->findText(consultar.value(4).toString()));
            ui->comboBoxDia->setCurrentIndex(ui->comboBoxDia->findText(consultar.value(5).toString()));
            ui->mes_3->setCurrentIndex(ui->mes_3->findText(consultar.value(6).toString()));
            ui->anio_3->setCurrentIndex(ui->anio_3->findText(consultar.value(7).toString()));
            ui->comboBoxDocente->setCurrentIndex(ui->comboBoxDocente->findText(consultar.value(8).toString()));
            ui->monto->setText(consultar.value(9).toString());
            ui->formaPago->setCurrentIndex(ui->formaPago->findText(consultar.value(10).toString()));

        }

        qDebug() << "All registers are shown Succesfully";
        ui->message->setText("REGISTRO ENCONTRADO!!!");
    }

    else
    {
        ui->message->setText("REGISTRO INEXISTENTE!!");
        qDebug()<<"ERROR! Impossible show table registers...";
        qDebug()<<"ERROR!"<< consultar.lastError();
    }
}

void DialogAdministracion::on_searchAlumno_clicked()
{
   buscarAlummo2();
}

void DialogAdministracion::on_presente_clicked()
{
    cargarPresentismo();
    clearPresentismo();
}

void DialogAdministracion::on_searchAlumno_2_clicked()
{
    listarPresentismoAlumno();
}

void DialogAdministracion::on_searchStyles_clicked()
{
    listarPresentismoStyle();
}


//FUNCIONES CALCULO DE ANTIGUEDAD
//===================================================================

int DialogAdministracion::calculoAntiguedad(aFecha fecha1)
{
    aFecha fecha2;
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

int DialogAdministracion::regularBisiesto(int anio)
{
    return ((anio%4 == 0 && anio%100 != 0) || (anio%400) == 0);
}

int DialogAdministracion::numeroBisiestos(int anio)
{
    return anio / 4 - anio / 100 + anio / 400;
}

int DialogAdministracion::diaDelAnio(aFecha fecha)
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


