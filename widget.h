#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPainter>
#include<QPaintEvent>
#include<QVector>
#include"../PolandCalculator/mainwindow.h"
#include<QOpenGLWidget>
#include<QMessageBox>
#include"SolvingFunctions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QPaintWidget : public QDialog
{
    Q_OBJECT

public:
    bool event(QEvent* event);
    QPaintWidget(MainWindow* calculator, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void paintTangent(QPainter* paint,double point);
    void paintCell(QPainter* paint,float Ymax = 0, float Ymin = 0);
    ~QPaintWidget();
    QString getFunction();
    MainWindow* getCalculator();
    double getA();
    double getB();

private slots:
    void on_pushButton_clicked();

    void on_AA_editingFinished();

    void on_BB_editingFinished();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Widget *ui;
    MainWindow* calc;
    QString function = "0";
    double a = 0.;
    double b = 0.;
    double Ymin = 0;
    double Ymax = 0;
};
#endif // WIDGET_H
