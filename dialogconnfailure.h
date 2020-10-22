#ifndef DIALOGCONNFAILURE_H
#define DIALOGCONNFAILURE_H

#include <QDialog>

namespace Ui {
class DialogConnFailure;
}

class DialogConnFailure : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogConnFailure(QWidget *parent = 0);
    ~DialogConnFailure();
    
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::DialogConnFailure *ui;
};

#endif // DIALOGCONNFAILURE_H
