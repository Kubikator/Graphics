#include "dialog.h"
#include "ui_dialog.h"
#include"mainwindow.h"
#include"widget.h"
#include"diagram.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Graph_clicked()
{
    MainWindow* mw = new MainWindow();
    QPaintWidget pw(mw);
    pw.exec();
    pw.show();
}


void Dialog::on_Diagr_clicked()
{
    Diagram diag;
    diag.setModal(true);
    diag.exec();
    diag.show();
}


void Dialog::on_Gistogr_clicked()
{
    Circles crl;
    crl.setModal(true);
    crl.exec();
    crl.show();
}

