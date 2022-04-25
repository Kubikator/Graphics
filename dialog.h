#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"circles.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_Graph_clicked();

    void on_Diagr_clicked();

    void on_Gistogr_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
