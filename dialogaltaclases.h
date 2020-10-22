#ifndef DIALOGALTACLASES_H
#define DIALOGALTACLASES_H

#include <QDialog>

namespace Ui {
class DialogAltaClases;
}

class DialogAltaClases : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAltaClases(QWidget *parent = 0);
    ~DialogAltaClases();

    void cargarComboBoxPack();
    void cargarComboxStyles();
    void cargarComboBoxAlumno();
    void cargarComboBoxTipoActividad();
    void addClases();
    void clearScreen();
    
private slots:
    void on_salir_clicked();

    void on_agregar_clicked();

private:
    Ui::DialogAltaClases *ui;
};

#endif // DIALOGALTACLASES_H
