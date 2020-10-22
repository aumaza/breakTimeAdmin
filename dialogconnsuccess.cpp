#include "dialogconnsuccess.h"
#include "ui_dialogconnsuccess.h"


DialogConnSuccess::DialogConnSuccess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnSuccess)
{
    ui->setupUi(this);
    setWindowTitle("ConnSuccesfully");
}

DialogConnSuccess::~DialogConnSuccess()
{
    delete ui;
}

void DialogConnSuccess::on_pushButton_2_clicked()
{
    accept();
}
