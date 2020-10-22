#ifndef DIALOGALTAPACKS_H
#define DIALOGALTAPACKS_H

#include <QDialog>

namespace Ui {
class DialogAltaPacks;
}

class DialogAltaPacks : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAltaPacks(QWidget *parent = 0);
    ~DialogAltaPacks();

    void addPacks();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DialogAltaPacks *ui;
};

#endif // DIALOGALTAPACKS_H
