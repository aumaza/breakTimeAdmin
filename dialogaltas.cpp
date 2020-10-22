#include "dialogaltas.h"
#include "ui_dialogaltas.h"
#include "dialoginscripcion.h"
#include "dialogaltapacks.h"
#include "dialogaltastylos.h"
#include "dialogaltaclases.h"
#include "dialogaltadocente.h"
#include "dialoghorasdias.h"
#include "dialogtipoactividad.h"

DialogAltas::DialogAltas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAltas)
{
    ui->setupUi(this);
    setWindowTitle("Ingresos");
}

DialogAltas::~DialogAltas()
{
    delete ui;
}

void DialogAltas::on_pushButton_2_clicked()
{
    DialogInscripcion In;
    In.exec();
}

void DialogAltas::on_pushButton_5_clicked()
{
    DialogAltaPacks Packs;
    Packs.exec();
}

void DialogAltas::on_pushButton_4_clicked()
{
    DialogAltaStylos St;
    St.exec();
}

void DialogAltas::on_pushButton_3_clicked()
{
    DialogAltaClases Ac;
    Ac.exec();
}

void DialogAltas::on_salir_clicked()
{
    reject();
}

void DialogAltas::on_pushButton_6_clicked()
{
    DialogAltaDocente Ad;
    Ad.exec();
}

void DialogAltas::on_diasHorarios_clicked()
{
    DialogHorasDias Hd;
    Hd.exec();
}

void DialogAltas::on_pushButton_7_clicked()
{
    DialogTipoActividad Ta;
    Ta.exec();
}
