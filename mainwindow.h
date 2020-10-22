#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void crearTablaPersonas();
    void crearTablaUsuarios();
    void crearTablaActividades();
    void crearTablaPacks();
    void crearTablaStylos();
    void crearTablaPagos();
    void crearTablaPagoDocentes();
    void crearTablaTotalPagoDocentes();
    void crearTablaDocentes();
    void crearTablaDiasHorario();
    void crearTablaTipoActividad();
    void crearTablaCobroTotalesAlumnos();
    void crearTablaCierreFinal();
    void crearTablaPresentismo();
    void crearTablaVentas();
    void crearTablaIngresos();
    void crearTablaEgresos();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
