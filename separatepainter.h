#ifndef SEPARATEPAINTER_H
#define SEPARATEPAINTER_H

#include <QWidget>
#include"widget.h"
#include<QLabel>

namespace Ui {
class SeparatePainter;
}

class SeparatePainter : public QDialog
{
    Q_OBJECT

public:
    explicit SeparatePainter(QPaintWidget* mainF,QWidget *parent = nullptr);
    void paintScalableCell(QPainter* paint,float Ymax, float Ymin);
    ~SeparatePainter();
    void paintEvent(QPaintEvent*);

private:
    Ui::SeparatePainter *ui;
    QPaintWidget* mainF;
    bool numbers = false;
};

#endif // SEPARATEPAINTER_H
