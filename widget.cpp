#include "widget.h"
#include "ui_widget.h"
#include"separatepainter.h"
#include<QMouseEvent>

QPaintWidget::QPaintWidget(MainWindow* calculator,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    calc = calculator;
}

QPaintWidget::~QPaintWidget()
{
    delete ui;
}

void QPaintWidget::paintEvent(QPaintEvent*){
    if (a == b){
        return;
    }
    QVector<QPointF> vec;
    float Ymax, Ymin;
    QPainter* paint = new QPainter(ui->openGLWidget);
    paint->fillRect(QRectF(QPointF(0,0),QSizeF(ui->openGLWidget->width(),ui->openGLWidget->height())),Qt::white);
    Queue ue = calc->parse(function);
    Queue que = calc->check_syntacsis(ue);
    Queue queue = calc->form_poland_queue(que);
    vec = getPoints(ui->openGLWidget,a,b,queue,b-a,&Ymax,&Ymin);
    this->Ymax = Ymax;
    this->Ymin = Ymin;
    paint->setPen(Qt::gray);
    paintCell(paint,Ymax,Ymin);
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::blue);
    paint->setPen(pen);
    if (vec.size() != 0){
        paint->drawLines(vec);
    }
    paint->end();
}

bool QPaintWidget::event(QEvent* event){
    if (event->type() == QEvent::MouseMove){
        return true;
    }
    return QWidget::event(event);
}

void QPaintWidget::paintCell(QPainter* paint,float Ymax, float Ymin){
    float Mx = ui->openGLWidget->width()/8;
    float My = ui->openGLWidget->height()/8;
    for (int i = 0; i < 8; ++i){
        paint->drawLine(0,My*i,ui->openGLWidget->width(),My*i);
        paint->drawLine(Mx*i,0,Mx*i,ui->openGLWidget->height());
    }
    QString str;
    float num = a;
    ui->x1->setText(str.setNum(a));
    ui->x2->setText(str.setNum(round((a + ((b-a)/8)*1)*100)/100));
    ui->x3->setText(str.setNum(round((a + ((b-a)/8)*2)*100)/100));
    ui->x4->setText(str.setNum(round((a + ((b-a)/8)*3)*100)/100));
    ui->x5->setText(str.setNum(round((a + ((b-a)/8)*4)*100)/100));
    ui->x6->setText(str.setNum(round((a + ((b-a)/8)*5)*100)/100));
    ui->x7->setText(str.setNum(round((a + ((b-a)/8)*6)*100)/100));
    ui->x8->setText(str.setNum(round((a + ((b-a)/8)*7)*100)/100));
    ui->y1->setText(str.setNum(Ymin));
    ui->y2->setText(str.setNum(round((Ymin + ((Ymax - Ymin)/8)*1)*100)/100));
    ui->y3->setText(str.setNum(round((Ymin + ((Ymax - Ymin)/8)*2)*100)/100));
    ui->y4->setText(str.setNum(round((Ymin + ((Ymax - Ymin)/8)*3)*100)/100));
    ui->y5->setText(str.setNum(round((Ymin + ((Ymax - Ymin)/8)*4)*100)/100));
    ui->y6->setText(str.setNum(round((Ymin + ((Ymax - Ymin)/8)*5)*100)/100));
    ui->y7->setText(str.setNum(round((Ymin + ((Ymax - Ymin)/8)*6)*100)/100));
    ui->y8->setText(str.setNum(round((Ymin + ((Ymax - Ymin)/8)*7)*100)/100));
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    paint->setPen(pen);
    if (a <= 0 && b >= 0){
        if (a != b){
            Mx = ui->openGLWidget->width()/(b-a);
            paint->drawLine(Mx*(-a),0,Mx*(-a),ui->openGLWidget->height());
            paint->drawLine(Mx*(-a),0,Mx*(-a)+5,5);
            paint->drawLine(Mx*(-a),0,Mx*(-a)-5,5);
        }
    }
    if (Ymin <= 0 && Ymax >= 0){
        if (Ymax != Ymin){
            My = ui->openGLWidget->height()/(Ymax - Ymin);
            paint->drawLine(0,ui->openGLWidget->height() + My*Ymin,ui->openGLWidget->width(),ui->openGLWidget->height() + My*Ymin);
            paint->drawLine(ui->openGLWidget->width(),ui->openGLWidget->height() + My*Ymin,ui->openGLWidget->width(),ui->openGLWidget->height() + My*Ymin + 5);
            paint->drawLine(ui->openGLWidget->width(),ui->openGLWidget->height() + My*Ymin,ui->openGLWidget->width(),ui->openGLWidget->height() + My*Ymin - 5);
        }
    }
}


void QPaintWidget::on_pushButton_clicked()
{
    function = ui->lineEdit->text();
    QPainter* paint = new QPainter(ui->openGLWidget);
    paint->fillRect(QRectF(QPointF(0,0),QSizeF(ui->openGLWidget->width(),ui->openGLWidget->height())),Qt::white);
    paint->end();
    try{
        QPaintEvent* pa;
        paintEvent(pa);
    } catch (QString str){
        QMessageBox::about(this,"Error",str);
    }
}


void QPaintWidget::on_AA_editingFinished()
{
    bool ok;
    double number = ui->AA->text().toDouble(&ok);
    if (!ok){
        ui->AA->setText(QString("0"));
        a = 0;
    } else if (number > ui->BB->text().toDouble()) {
        ui->AA->setText(ui->BB->text());
        a = ui->BB->text().toDouble();
    } else {
        a = number;
    }
}


void QPaintWidget::on_BB_editingFinished()
{
    bool ok;
     double number = ui->BB->text().toDouble(&ok);
     if (!ok){
         ui->BB->setText(QString("0"));
         b = 0;
     } else if (number < ui->AA->text().toDouble()) {
         ui->BB->setText(ui->AA->text());
         b = ui->AA->text().toDouble();
     } else {
         b = number;
     }

}


void QPaintWidget::on_pushButton_2_clicked()
{
    function = ui->lineEdit->text();
    QPainter* paint = new QPainter(ui->openGLWidget);
    paint->fillRect(QRectF(QPointF(0,0),QSizeF(ui->openGLWidget->width(),ui->openGLWidget->height())),Qt::white);
    paint->end();
    try{
        QPaintEvent* pa;
    paintEvent(pa);
    SeparatePainter sep(this);
    sep.setModal(true);
    sep.exec();
    } catch (QString str){
        QMessageBox::about(this,"Error",str);
    }
}

QString QPaintWidget::getFunction(){
    return function;
}

MainWindow* QPaintWidget::getCalculator(){
    return calc;
}

double QPaintWidget::getA(){
    return a;
}

double QPaintWidget::getB(){
    return b;
}


void QPaintWidget::on_pushButton_3_clicked()
{
}


void QPaintWidget::on_pushButton_4_clicked()
{
}


void QPaintWidget::on_pushButton_5_clicked()
{
    bool ok;
    double point = ui->tangent->text().toDouble(&ok);
    if (ok){
        if (point < b && point > a){
            try {
                QPaintEvent* pa;
                paintEvent(pa);
                auto* paint = new QPainter(ui->openGLWidget);
                paintTangent(paint,point);
                paint->end();
            }  catch (QString str) {
                QMessageBox::about(this,"Error",str);
            }
        } else {
            QMessageBox::about(this,"Error!","Your point isn`t included in (a,b)!");
        }
    } else {
        QMessageBox::about(this,"Error!","Incorrect number for tangent!");
    }
}

void QPaintWidget::paintTangent(QPainter* paint,double point){
    // y = f(c) + f`(c)(x - c)
    // f`(c) = dy / dx
    // y2 = f(c) + f`(c)(c + h - c)
    if (Ymin == Ymax){
        return;
    }
    double f_in_point;
    Queue ue = calc->parse(function);
    Queue que = calc->check_syntacsis(ue);
    Queue queue = calc->form_poland_queue(que);
    Queue temp = queue.copy();
    Queue time = queue.copy();
    double h = pow(ui->openGLWidget->width()/(b-a),-1);
    double increment = point - h;
    try{
    f_in_point = solve_poland(temp,&point);
    } catch (QString str){
        return;
    }
    temp = queue.copy();
    double derivative = (f_in_point - solve_poland(time,&increment)) / h;
    double Mx = ui->openGLWidget->width()/(b-a);
    double My = ui->openGLWidget->height()/(Ymax - Ymin);
    double delta_point = point + 10*h;
    QPointF first(0,
                  ui->openGLWidget->height() - My*(f_in_point + derivative * (a - point) - Ymin));
    QPointF second (Mx*(b-a),
                    ui->openGLWidget->height() - My*(f_in_point + derivative * (b - point) - Ymin));
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    paint->setPen(pen);
    paint->drawLine(first.x(),first.y(),second.x(),second.y());
}

