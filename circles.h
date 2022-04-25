#ifndef CIRCLES_H
#define CIRCLES_H

#include <QDialog>
#include<QPainter>
#include<QMouseEvent>
#include<QVector>
#include<QPainterPath>

namespace Ui {
class Circles;
}

class Circles : public QDialog
{
    Q_OBJECT

public:
    explicit Circles(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    bool event(QEvent* ev);
    ~Circles();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Circles *ui;
};

#endif // CIRCLES_H
