#ifndef DIALOGMENU_H
#define DIALOGMENU_H

#include <QDialog>

namespace Ui {
class DialogMenu;
}

class DialogMenu : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMenu(QWidget *parent = 0);
    ~DialogMenu();
    
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_salir_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::DialogMenu *ui;
};

#endif // DIALOGMENU_H
