#ifndef DIALOGALTASTYLOS_H
#define DIALOGALTASTYLOS_H

#include <QDialog>

namespace Ui {
class DialogAltaStylos;
}

class DialogAltaStylos : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAltaStylos(QWidget *parent = 0);
    ~DialogAltaStylos();

    void addStylos();
    
private slots:
    void on_salir_clicked();

    void on_agregar_clicked();

private:
    Ui::DialogAltaStylos *ui;
};

#endif // DIALOGALTASTYLOS_H
