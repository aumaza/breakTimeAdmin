#ifndef DIALOGHORASDIAS_H
#define DIALOGHORASDIAS_H

#include <QDialog>

namespace Ui {
class DialogHorasDias;
}

class DialogHorasDias : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogHorasDias(QWidget *parent = 0);
    ~DialogHorasDias();

    void cargarComboBoxStyles();
    void cargarComboBoxDocente();
    void addHoraDia();
    void listarHoraDia();
    void filtrarDia();
    void filtrarActividad();
    void buscarStyle();
    
private slots:
    void on_pushButton_2_clicked();

    void on_agregar_clicked();

    void on_filtrarDia_clicked();

    void on_filtrarActividad_clicked();

    void on_buscar_clicked();

private:
    Ui::DialogHorasDias *ui;
};

#endif // DIALOGHORASDIAS_H
