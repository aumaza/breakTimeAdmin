#ifndef DIALOGALTADOCENTE_H
#define DIALOGALTADOCENTE_H

#include <QDialog>

typedef struct
{
  int dia;
  int mes;
  int anio;
}eFecha;

namespace Ui {
class DialogAltaDocente;
}

class DialogAltaDocente : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAltaDocente(QWidget *parent = 0);
    ~DialogAltaDocente();

    void addDocente();
    void cleanScreen();
    void nuevaBusqueda();
    void buscarDocente();
    void editarDocente();
    void borrarDocente();

    int calculoAntiguedad(eFecha fecha1);
    int regularBisiesto( int anio);
    int numeroBisiestos( int anio );
    int diaDelAnio(eFecha fecha );
    
private slots:
    void on_back_clicked();

    void on_pushButton_5_clicked();

    void on_editar_clicked();

    void on_buscar_clicked();

    void on_nuevaBusqueda_clicked();

    void on_borrar_clicked();

private:
    Ui::DialogAltaDocente *ui;
};

#endif // DIALOGALTADOCENTE_H
