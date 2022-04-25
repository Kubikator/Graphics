#include "circle.h"
#include "ui_circle.h"

Circles::Circles(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Circles)
{
    ui->setupUi(this);
}

Circles::~Circles()
{
    delete ui;
}
