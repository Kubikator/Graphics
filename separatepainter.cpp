#include "separatepainter.h"
#include "ui_separatepainter.h"

SeparatePainter::SeparatePainter(QPaintWidget* mainF,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeparatePainter)
{
    ui->setupUi(this);
    this->mainF = mainF;
    QPaintEvent* p;
    paintEvent(p);
}

SeparatePainter::~SeparatePainter()
{
    delete ui;
}

void SeparatePainter::paintEvent(QPaintEvent*){
    QVector<QPointF> vec;
    float Ymax,Ymin;
    QPainter* paint = new QPainter(ui->openGLWidget);
    paint->fillRect(QRectF(QPointF(0,0),QSizeF(ui->openGLWidget->width(),ui->openGLWidget->height())),Qt::white);
    Queue ue = mainF->getCalculator()->parse(mainF->getFunction());
    Queue que = mainF->getCalculator()->check_syntacsis(ue);
    Queue queue = mainF->getCalculator()->form_poland_queue(que);
    vec = getPoints(ui->openGLWidget,mainF->getA(),mainF->getB(),queue.copy(),&Ymax,&Ymin);
    paintScalableCell(paint,Ymax,Ymin);
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::blue);
    paint->setPen(pen);
    paint->drawLines(vec);
    paint->end();
}

void SeparatePainter::paintScalableCell(QPainter* paint,float Ymax, float Ymin){
    paint->setPen(Qt::gray);
    float a = mainF->getA();
    float b = mainF->getB();
    float Mx = a != b? ui->openGLWidget->width()/(b-a) : ui->openGLWidget->width()/2;
    for (int i = 0;Mx*(0.5*i) < ui->openGLWidget->width(); ++i){
        paint->drawLine(Mx*(0.5*i),0,Mx*(0.5*i),height());
    }
    float My = Ymax != Ymin? ui->openGLWidget->height()/(Ymax - Ymin) : ui->openGLWidget->height()/2;
    for (int i = 0; ui->openGLWidget->height() - My*(0.5*i) >= 0; ++i){
        paint->drawLine(0,ui->openGLWidget->height() - My*(0.5*i),ui->openGLWidget->width(),ui->openGLWidget->height() - My*(0.5*i));
    }

    if (!numbers){
    QString first;
    QString second;
    first.setNum(a + 0.5);
    second.setNum(Ymin + 0.5);

    QLabel* lab = new QLabel(this);
    QLabel* lab2 = new QLabel(this);
    lab->setText(first);
    lab2->setText(second);
    lab->activateWindow();
    lab->raise();
    lab2->activateWindow();
    lab2->raise();
    lab->setGeometry(Mx*(0,5) - 80,height()-70,100,100);
    lab2->setGeometry(10,ui->openGLWidget->height() - My*(0.5)+330,100,100);
    lab->show();
    lab2->show();
    numbers = true;
    }

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(3);
    paint->setPen(pen);
    if (a <= 0 && b >= 0){
        paint->drawLine(Mx*(-a),0,Mx*(-a),ui->openGLWidget->height());
        paint->drawLine(Mx*(-a),0,Mx*(-a)-5,5);
        paint->drawLine(Mx*(-a),0,Mx*(-a)+5,5);
    }
    if (Ymin <= 0 && Ymax >= 0){
        paint->drawLine(0,ui->openGLWidget->height() - My*(-Ymin),ui->openGLWidget->width(),ui->openGLWidget->height() - My*(-Ymin));
        paint->drawLine(ui->openGLWidget->width(),ui->openGLWidget->height() - My*(-Ymin),ui->openGLWidget->width()-5,ui->openGLWidget->height() - My*(-Ymin) - 5);
        paint->drawLine(ui->openGLWidget->width(),ui->openGLWidget->height() - My*(-Ymin),ui->openGLWidget->width()-5,ui->openGLWidget->height() - My*(-Ymin) + 5);
    }
}
