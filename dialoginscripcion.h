#ifndef DIALOGINSCRIPCION_H
#define DIALOGINSCRIPCION_H

#include <QDialog>

typedef struct
{
  int dia;
  int mes;
  int anio;
}Fecha;

namespace Ui {
class DialogInscripcion;
}

class DialogInscripcion : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogInscripcion(QWidget *parent = 0);
    ~DialogInscripcion();

    void addInscription();
    void clearScreen();

    int calculoAntiguedad(Fecha fecha1);
    int regularBisiesto( int anio);
    int numeroBisiestos( int anio );
    int diaDelAnio( Fecha fecha );

    
private slots:


    void on_inscribir_clicked();

    void on_cancelar_clicked();

private:
    Ui::DialogInscripcion *ui;
};

#endif // DIALOGINSCRIPCION_H
