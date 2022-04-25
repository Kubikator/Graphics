#include "circles.h"
#include "ui_circles.h"

Circles::Circles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Circles)
{
    ui->setupUi(this);
}

Circles::~Circles()
{
    delete ui;
}

bool Circles::event(QEvent *ev){
    if (ev->type() == QEvent::MouseMove){
        return true;
    }
    return QWidget::event(ev);
}

void Circles::on_pushButton_clicked()
{
    bool ok;
    ui->lineEdit->text().toDouble(&ok);
    if (!ok){
        return;
    }
    ui->listWidget->addItem(ui->lineEdit->text());
    ui->lineEdit->setText("");
}

void Circles::paintEvent(QPaintEvent *){
    QPainter* paint = new QPainter(ui->openGLWidget);
    paint->fillRect(QRectF(QPointF(0,0),QSizeF(ui->openGLWidget->width(),ui->openGLWidget->height())),Qt::white);
    if (ui->listWidget->count() == 0 || ui->listWidget->count() == 1){
        paint->end();
        return;
    }
    QVector<double> vec;
    for (int i = 0; i < ui->listWidget->count(); ++i){
        vec.push_back(ui->listWidget->item(i)->text().toDouble());
    }
    double max = vec[0],min = vec[0];
    for (auto& elem : vec){
        if (elem > max){
            max = elem;
        }
        if (elem < min){
            min = elem;
        }
    }
    double delta = (max - min)/4;
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);
    paint->setPen(pen);
    int work = 0;
    QVector<QBrush> br{QBrush(Qt::blue), QBrush(Qt::red), QBrush(Qt::green), QBrush(Qt::yellow)};
    QVector<QLabel*> lab{ui->x1,ui->x2,ui->x3,ui->x4,ui->i1,ui->i2,ui->i3,ui->i4};
    QVector<QString> style{"color: rgb(0,0,200)","color: rgb(200,0,0)","color: rgb(0,200,0)","color: rgb(200,200,0)"};
    for (int i = 0 ; i < 4; ++i){
    int count = std::count_if(vec.begin(),vec.end(),[delta,i,min](const double& num){
        if (i+1 != 4){
            return min + delta*i <= num && num < min + delta*(i+1);
        } else {
            return min + delta*i <= num && num <= min + delta*(i+1);
        }
        });
    paint->setBrush(br[i]);
    if (i != 3){
    paint->drawPie(0,0,
                   ui->openGLWidget->width(),ui->openGLWidget->height(),
                   (360/vec.size())*work*16,(360/vec.size())*count*16);
    } else {
        paint->drawPie(0,0,
                       ui->openGLWidget->width(),ui->openGLWidget->height(),
                       (360/vec.size())*work*16,360*16 - (360/vec.size())*work*16);
    }

    work += count;
    lab[i]->setText(QString::number(count));
    lab[i]->setStyleSheet(style[i]);
    QString number;
    QString numb;
    lab[i+4]->setText("["+number.setNum(min + delta*i)+" , " + numb.setNum(min + delta*(i+1)) + "]");
    lab[i+4]->setStyleSheet(style[i]);
    }
    paint->end();
}

