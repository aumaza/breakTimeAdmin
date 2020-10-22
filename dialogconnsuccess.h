#ifndef DIALOGCONNSUCCESS_H
#define DIALOGCONNSUCCESS_H

#include <QDialog>

namespace Ui {
class DialogConnSuccess;
}

class DialogConnSuccess : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogConnSuccess(QWidget *parent = 0);
    ~DialogConnSuccess();
    
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::DialogConnSuccess *ui;
};

#endif // DIALOGCONNSUCCESS_H
