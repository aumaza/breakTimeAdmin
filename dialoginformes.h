#ifndef DIALOGINFORMES_H
#define DIALOGINFORMES_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>

namespace Ui {
class DialogInformes;
}

class DialogInformes : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogInformes(QWidget *parent = 0);
    ~DialogInformes();

    void listarInscriptos();
    void listarActividades();
    void listarPacks();
    void listarStyles();
    void listarDocentes();
    void listarTipoActividad();

    //EXPORT CSV
    QString escapedCSV(QString unexc);
    void queryToCsvDocentes();
    void querytoCsvActividades();
    void queryToCsvIncripciones();
    
private slots:
    void on_pushButton_2_clicked();

    void on_exportCSV_clicked();

    void on_exportCSV_2_clicked();

    void on_exportCSV_3_clicked();

private:
    Ui::DialogInformes *ui;
    QSqlDatabase db;
};

#endif // DIALOGINFORMES_H
