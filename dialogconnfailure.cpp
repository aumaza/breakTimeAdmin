#include "dialogconnfailure.h"
#include "ui_dialogconnfailure.h"

DialogConnFailure::DialogConnFailure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnFailure)
{
    ui->setupUi(this);
    setWindowTitle("Connfailure");
}

DialogConnFailure::~DialogConnFailure()
{
    delete ui;
}

void DialogConnFailure::on_pushButton_2_clicked()
{
    return;
}
