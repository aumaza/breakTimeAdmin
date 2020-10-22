#ifndef DIALOGALTAS_H
#define DIALOGALTAS_H

#include <QDialog>

namespace Ui {
class DialogAltas;
}

class DialogAltas : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAltas(QWidget *parent = 0);
    ~DialogAltas();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_salir_clicked();

    void on_pushButton_6_clicked();

    void on_diasHorarios_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::DialogAltas *ui;
};

#endif // DIALOGALTAS_H
