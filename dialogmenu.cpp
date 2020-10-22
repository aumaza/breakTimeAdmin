#include "dialogmenu.h"
#include "ui_dialogmenu.h"
#include "dialoguserregister.h"
#include "dialogaltas.h"
#include "dialoginformes.h"
#include "dialogadministracion.h"
#include "dialogfacturacion.h"
#include "dialogventas.h"

DialogMenu::DialogMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMenu)
{
    ui->setupUi(this);
    setWindowTitle("Menu Principal");
}

DialogMenu::~DialogMenu()
{
    delete ui;
}

void DialogMenu::on_pushButton_3_clicked()
{
    DialogUserRegister Ur;
    Ur.exec();
}

void DialogMenu::on_pushButton_5_clicked()
{
    DialogAltas Al;
    Al.exec();

}

void DialogMenu::on_salir_clicked()
{
    exit(0);
}

void DialogMenu::on_pushButton_7_clicked()
{
    DialogInformes In;
    In.exec();
}



void DialogMenu::on_pushButton_2_clicked()
{
    DialogAdministracion Gd;
    Gd.exec();
}

void DialogMenu::on_pushButton_4_clicked()
{
    DialogFacturacion Fa;
    Fa.exec();
}

void DialogMenu::on_pushButton_6_clicked()
{
    DialogVentas Ve;
    Ve.exec();
}
