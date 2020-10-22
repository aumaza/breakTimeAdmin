#ifndef DIALOGUSERREGISTER_H
#define DIALOGUSERREGISTER_H

#include <QDialog>

namespace Ui {
class DialogUserRegister;
}

class DialogUserRegister : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogUserRegister(QWidget *parent = 0);
    ~DialogUserRegister();

    void cleanScreen();
    void addUser();
    void searchUser();
    void editUser();
    void deleteUser();
    
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_buscarUsuario_clicked();

    void on_modificarPass_clicked();

    void on_eliminarUser_clicked();

private:
    Ui::DialogUserRegister *ui;
};

#endif // DIALOGUSERREGISTER_H
