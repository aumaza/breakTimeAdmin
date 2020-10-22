#ifndef DIALOGTIPOACTIVIDAD_H
#define DIALOGTIPOACTIVIDAD_H

#include <QDialog>

namespace Ui {
class DialogTipoActividad;
}

class DialogTipoActividad : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogTipoActividad(QWidget *parent = 0);
    ~DialogTipoActividad();

    void addTipoActividad();
    
private slots:
    void on_back_clicked();

    void on_agregar_clicked();

private:
    Ui::DialogTipoActividad *ui;
};

#endif // DIALOGTIPOACTIVIDAD_H
