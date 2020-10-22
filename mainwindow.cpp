#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoglogin.h"
#include "dialogconnsuccess.h"
#include "dialogconnfailure.h"
#include "dialogmenu.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BreakTime");

    QString name;
    name.append("SqlBase.sqlite");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);

    if(db.open())
    {
        DialogConnSuccess SU;
        SU.exec();
        qDebug() << "Connection Succesfully";
    }

    else
    {
        DialogConnFailure warning;
        warning.exec();
        qDebug()<<"Connection ERROR!";
    }

    crearTablaPersonas();
    crearTablaUsuarios();
    crearTablaActividades();
    crearTablaPacks();
    crearTablaStylos();
    crearTablaPagos();
    crearTablaPagoDocentes();
    crearTablaTotalPagoDocentes();
    crearTablaDocentes();
    crearTablaDiasHorario();
    crearTablaTipoActividad();
    crearTablaCobroTotalesAlumnos();
    crearTablaCierreFinal();
    crearTablaPresentismo();
    crearTablaVentas();
    crearTablaIngresos();
    crearTablaEgresos();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::crearTablaPersonas()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS personas ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombreApellido VARCHAR(35) NOT NULL,"
                    "dni VARCHAR(9) NOT NULL,"
                    "fechaNacimiento INTEGER NOT NULL,"
                    "edad INTEGER NOT NULL,"
                    "direccion VARCHAR(40) NOT NULL,"
                    "localidad VARCHAR(20) NOT NULL,"
                    "telefono VARCHAR(10) NOT NULL,"
                    "movil VARCHAR(10) NOT NULL,"
                    "email VARCHAR(50) NOT NULL,"
                    "observaciones VARCHAR(255) NOT NULL,"
                    "nombrePariente VARCHAR(40) NOT NULL,"
                    "parentezco VARCHAR(10) NOT NULL,"
                    "telContacto VARCHAR(10) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       //ui->statusBar->showMessage("Table PERSONAS Already Exists or Creates Succesfully");
        qDebug() << "Table PERSONAS Already Exists or Creates Succesfully";
    }

    else
    {
        //ui->statusBar->showMessage("ERROR! Impossible Creates Table");
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaUsuarios()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS usuarios ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(40) NOT NULL,"
                    "password VARCHAR(16) NOT NULL,"
                    "nickname VARCHAR(16) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       //ui->statusBar->showMessage("Table USUARIOS Already Exists or Creates Succesfully");
        qDebug() << "Table USUARIOS Already Exists or Creates Succesfully";
    }

    else
    {
        //ui->statusBar->showMessage("ERROR! Impossible Creates Table");
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaActividades()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS actividades ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "actividad VARCHAR(50) NOT NULL,"
                    "nombreApellido VARCHAR(50) NOT NULL,"
                    "style VARCHAR(50) NOT NULL,"
                    "pack VARCHAR(20) NOT NULL,"
                    "dia VARCHAR(2) NOT NULL,"
                    "mes VARCHAR(15) NOT NULL,"
                    "anio VARCHAR(4) NOT NULL,"
                    "docente VARCHAR(50) NOT NULL,"
                    "valor FLOAT(6,2) NOT NULL,"
                    "formaPago VARCHAR(15) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       //ui->statusBar->showMessage("Table ACTIVIDADES Already Exists or Creates Succesfully");
        qDebug() << "Table ACTIVIDADES Already Exists or Creates Succesfully";
    }

    else
    {
        //ui->statusBar->showMessage("ERROR! Impossible Creates Table");
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaPacks()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS packs ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "descripcion VARCHAR(50) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       //ui->statusBar->showMessage("Table PACKS Already Exists or Creates Succesfully");
        qDebug() << "Table PACKS Already Exists or Creates Succesfully";
    }

    else
    {
        //ui->statusBar->showMessage("ERROR! Impossible Creates Table");
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaStylos()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS stylos ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "descripcion VARCHAR(50) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       //ui->statusBar->showMessage("Table STYLOS Already Exists or Creates Succesfully");
        qDebug() << "Table STYLOS Already Exists or Creates Succesfully";
    }

    else
    {
        //ui->statusBar->showMessage("ERROR! Impossible Creates Table");
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaPagos()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS pagos ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "concepto VARCHAR(15),"
                    "monto FLOAT(6,2),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(15),"
                    "anio VARCHAR(4),"
                    "descripcion VARCHAR(255),"
                    "total FLOAT(6,2)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table PAGOS Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaPagoDocentes()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS pagoDocentes ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombreApellido VARCHAR(30) NOT NULL,"
                    "monto FLOAT(6,2) NOT NULL,"
                    "dia VARCHAR(2) NOT NULL,"
                    "mes VARCHAR(15) NOT NULL,"
                    "anio VARCHAR(4) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table PAGO DOCENTES Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaTotalPagoDocentes()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS totalPagoDocentes ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "docente VARCHAR(30),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(15),"
                    "anio VARCHAR(4),"
                    "acum1 FLOAT(6,2),"
                    "acum2 FLOAT(6,2),"
                    "acum3 FLOAT(6,2),"
                    "acum4 FLOAT(6,2),"
                    "acum5 FLOAT(6,2),"
                    "acum6 FLOAT(6,2)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table TOTAL PAGO DOCENTES Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaDocentes()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS docentes ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombreApellido VARCHAR(35) NOT NULL,"
                    "dni VARCHAR(9) NOT NULL,"
                    "fechaNacimiento INTEGER NOT NULL,"
                    "edad INTEGER NOT NULL,"
                    "direccion VARCHAR(40) NOT NULL,"
                    "localidad VARCHAR(20) NOT NULL,"
                    "telefono VARCHAR(10) NOT NULL,"
                    "movil VARCHAR(10) NOT NULL,"
                    "email VARCHAR(50) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {
      qDebug() << "Table DOCENTES Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaDiasHorario()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS diasHorario ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "hora VARCHAR(5) NOT NULL,"
                    "dia VARCHAR(10) NOT NULL,"
                    "actividad VARCHAR(20) NOT NULL,"
                    "style VARCHAR(20) NOT NULL,"
                    "docente VARCHAR(40) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {
      qDebug() << "Table Dias Horarios Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaTipoActividad()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS tipoActividad ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "descripcion VARCHAR(20) NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {
      qDebug() << "Table Tipo Actividad Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaCobroTotalesAlumnos()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS totalCobroAlumnos ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "alumno VARCHAR(30),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(15),"
                    "anio VARCHAR(4),"
                    "acum1 FLOAT(6,2),"
                    "acum2 FLOAT(6,2),"
                    "acum3 FLOAT(6,2),"
                    "acum4 FLOAT(6,2),"
                    "acum5 FLOAT(6,2),"
                    "acum6 FLOAT(6,2)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table TOTAL COBRO ALUMNOS Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaCierreFinal()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS cierreFinal ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "cierre VARCHAR(15),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(15),"
                    "anio VARCHAR(4),"
                    "totalDiario FLOAT(6,2),"
                    "totalMensual FLOAT(6,2),"
                    "totalAnual FLOAT(6,2)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table TOTAL CIERRE FINAL Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaPresentismo()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS presentismo ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombreAlumno VARCHAR(15),"
                    "style VARCHAR(30),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(15),"
                    "anio VARCHAR(4),"
                    "observaciones VARCHAR(255)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table PRESENTISMO Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaVentas()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS ventas ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "concepto VARCHAR(25),"
                    "monto FLOAT(6,2),"
                    "formaPago VARCHAR(20),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(15),"
                    "anio VARCHAR(4),"
                    "observaciones VARCHAR(255)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table VENTAS Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaIngresos()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS ingresos ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "formaPago VARCHAR(20),"
                    "cierre VARCHAR(15),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(15),"
                    "anio VARCHAR(4),"
                    "totalDiario FLOAT(6,2),"
                    "totalMensual FLOAT(6,2),"
                    "totalAnual FLOAT(6,2)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table INGRESOS Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::crearTablaEgresos()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS egresos ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "cierre VARCHAR(15),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(15),"
                    "anio VARCHAR(4),"
                    "totalDiario FLOAT(6,2),"
                    "totalMensual FLOAT(6,2),"
                    "totalAnual FLOAT(6,2)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {

       qDebug() << "Table EGRESOS Already Exists or Creates Succesfully";
    }

    else
    {
        qDebug()<<"ERROR! Impossible Creates Table";
        qDebug()<<"ERROR!"<< crear.lastError();
    }
}

void MainWindow::on_pushButton_clicked()
{
    DialogLogin Lo;
    Lo.exec();
}
