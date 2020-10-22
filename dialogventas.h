#ifndef DIALOGVENTAS_H
#define DIALOGVENTAS_H

#include <QDialog>

namespace Ui {
class DialogVentas;
}

class DialogVentas : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogVentas(QWidget *parent = 0);
    ~DialogVentas();

    void agregarVenta();
    void cleanScreen();
    void listarVentas();
    void sumarVentas();
    
private slots:
    void on_backToMenu_clicked();

    void on_agregar_clicked();

    void on_buscar_clicked();

private:
    Ui::DialogVentas *ui;
};

#endif // DIALOGVENTAS_H
