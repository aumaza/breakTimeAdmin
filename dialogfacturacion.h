#ifndef DIALOGFACTURACION_H
#define DIALOGFACTURACION_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

namespace Ui {
class DialogFacturacion;
}

class DialogFacturacion : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogFacturacion(QWidget *parent = 0);
    ~DialogFacturacion();

    //PAGOS
    void agregarPagos();
    void listarPagos();
    void buscarPagoMesAnio();
    void buscarPagoAnios();
    void sumarPagosMesAnio();
    void sumarPagosAnio();
    void guardarPagosMesAnio();
    void guardarPagosAnio();


    void agregarPagosDocentes();
    void cleanScreen();
    void cargarComboBoxDocente();
    void cargarComboDocente();
    void cargarComboBoxAlumno();
    void listarTotaPagoDocente();

    //BUSQUEDAS
    void buscarDocente();
    void buscarDocenteDiaMesAnio();
    void buscarDocenteMesAnio();
    void buscarDiaMesAnio();
    void buscarMesAnio();
    void buscarAnio();

    void buscarAlumno();
    void buscarAlumnoDiaMesAnio();
    void buscarAlumnoMesAnio();
    void buscarDiaMesAnioA();
    void buscarMesAnioA();
    void buscarAnioA();


    //SUMAS DOCENTE
    void sumarDocente();
    void sumarDiaMesAnio();
    void sumarMesAnio();
    void sumarDocDiaMesAnio();
    void sumarDocMesAnio();
    void sumarAnios();

    //MUESTRA SUMAS DOCENTE
    void muestraSumaDocente();
    void muestraDocDiaMesAnio();
    void muestraDocMesAnio();
    void muestraDiaMesAnio();
    void muestraMesAnio();
    void muestraAnios();
    void listarCobroTotalAlumnos();

    //SUMA ALUMNOS
    void sumarAlumno();
    void sumarAlumnoDiaMesAnio();
    void sumarAlumnoMesAnio();
    void sumarDiaMesAnioA();
    void sumarMesAnioA();
    void sumarAnioA();

    //GUARDAR SUMAS ALUMNOS
    void guardarSumaAlumno();
    void guardarSumaAluDiaMesAnio();
    void guardarSumaAluMesAnio();
    void guardarDiaMesAnio();
    void guardarMesAnio();
    void guardarAnio();

    //INGRESOS
    void filtrarDiaMesAnioIngresos();
    void filtrarMesAnioIngresos();
    void filtrarAnioIngresos();
    void guardarDiaMesAnioIngresos();
    void guardarMesAnioIngresos();
    void guardarAnioIngresos();
    void listarHistoricoIngresos();

    //EGRESOS
    void filtrarDiaMesAnioEgresos();
    void filtrarMesAnioEgresos();
    void filtrarAnioEgresos();
    void guardarDiaMesAnioEgresos();
    void guardarMesAnioEgresos();
    void guardarAnioEgresos();
    void listarHistoricoEgresos();

    //CIERRE FINAL
    void filtrarDiaMesAnio();
    void filtrarMesAnio();
    void filtrarAnio();
    void guardarDiaMesAnioCF();
    void guardarMesAnioCF();
    void guardarAnioCF();
    void listarHistorialCF();

    //METODOS
    QString escapedCSV(QString unexc);
    void queryToCSVLiqDoc();

    
private slots:
    void on_backmenu_clicked();

    void on_agregar_clicked();

    void on_agregar_2_clicked();

    void on_filtroDocente_clicked();

    void on_filtroDocMesAnio_clicked();

    void on_filtroMesAnio_clicked();

    void on_filtroAnio_clicked();

    void on_filtroDiaMesAnio_clicked();

    void on_pushButton_2_clicked();

    void on_filtroAlumno_clicked();

    void on_filtroAluDiaMesAnio_clicked();

    void on_filtroAluMesAnio_clicked();

    void on_filtroDiaMesAnio_2_clicked();

    void on_filtroMesAnio_2_clicked();

    void on_filtroAnio_2_clicked();

    void on_GuardarD1_clicked();

    void on_GuardarD2_clicked();

    void on_GuardarD3_clicked();

    void on_GuardarD4_clicked();

    void on_GuardarD5_clicked();

    void on_GuardarD6_clicked();

    void on_GuardarA1_clicked();

    void on_GuardarA2_clicked();

    void on_GuardarA3_clicked();

    void on_GuardarA4_clicked();

    void on_GuardarA5_clicked();

    void on_GuardarA6_clicked();

    void on_filtrarMesAnioP_clicked();

    void on_filtrarAnioP_clicked();

    void on_guardarP1_clicked();

    void on_guardarP2_clicked();

    void on_filtroMesAnioCF_clicked();

    void on_filtrarAnioCF_clicked();

    void on_guardarMesAnioCF_clicked();

    void on_guardarAnioCF_clicked();

    void on_exportCSVLiqDoc_clicked();

    void on_filtrarDMAingresos_clicked();

    void on_filtrarMAingresos_clicked();

    void on_FiltrarAingresos_clicked();

    void on_guardarDMAingresos_clicked();

    void on_guardarDMingresos_clicked();

    void on_guardarAingresos_clicked();

    void on_filtrarDMAEgresos_clicked();

    void on_filtrarMAEgresos_clicked();

    void on_FiltrarAEgresos_clicked();

    void on_guardarDMAEgresos_clicked();

    void on_guardarDMEgresos_clicked();

    void on_guardarAEgresos_clicked();

    void on_filtroDiaMesAnioCF_clicked();

    void on_guardarDiaMesAnioCF_clicked();

private:
    Ui::DialogFacturacion *ui;
    QSqlDatabase db;
};

#endif // DIALOGFACTURACION_H
