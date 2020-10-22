#ifndef DIALOGADMINISTRACION_H
#define DIALOGADMINISTRACION_H

#include <QDialog>

typedef struct
{
  int dia;
  int mes;
  int anio;
}aFecha;

namespace Ui {
class DialogAdministracion;
}

class DialogAdministracion : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAdministracion(QWidget *parent = 0);
    ~DialogAdministracion();

    //Calculo de antiguedad/edad
    int calculoAntiguedad(aFecha fecha1);
    int regularBisiesto(int anio);
    int numeroBisiestos(int anio);
    int diaDelAnio(aFecha fecha);

    //metodos para solapa inscripciones
    void buscarDNI();
    void buscarNombreApellido();
    void editarPersona();
    void cleanScreen();
    void borrarPersona();

    //metodos para solapa actividades
    void buscarNombreAlumno();
    void buscarActividad();
    void cargarComboBoxPack();
    void cargarComboBoxStyles();
    void cargarComoBoxDocente();
    void cargarComboBoxNombreApellido();
    void cargarComboBoxTipoActividad();
    void cargarComboBoxId();
    void editarActividades();
    void borrarActividad();
    void cleanScreen2();
    void listarActividades();

    //METODOS PARA SOLAPA BUSQUEDA DE ACTIVIDADES
    void buscarActividades();

    //METODOS PARA SOLAPA BUSQUEDA DE ALUMNOS
    void buscarAlumno();
    void buscarAlummo2();
    void cargarPresentismo();
    void clearPresentismo();
    void listarPresentismoAlumno();
    void listarPresentismoStyle();
    
private slots:
    void on_volver_clicked();

    void on_buscarDNI_clicked();

    void on_busquedaNombre_clicked();



    void on_modificar_clicked();

    void on_clean_clicked();

    void on_eliminar_clicked();

    void on_search2_clicked();

    void on_search_clicked();

    void on_mod_clicked();

    void on_erase_clicked();

    void on_cleanScreen_clicked();

    void on_buscar_2_clicked();

    void on_search_3_clicked();



    void on_comboBoxId_currentIndexChanged();

    void on_searchAlumno_clicked();

    void on_presente_clicked();

    void on_searchAlumno_2_clicked();

    void on_searchStyles_clicked();


private:
    Ui::DialogAdministracion *ui;
};

#endif // DIALOGADMINISTRACION_H
