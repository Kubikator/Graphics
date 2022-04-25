#include "diagram.h"
#include "ui_diagram.h"

Diagram::Diagram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Diagram)
{
    ui->setupUi(this);
}

Diagram::~Diagram()
{
    delete ui;
}

bool Diagram::event(QEvent *ev){
    if (ev->type() == QEvent::MouseMove){
        return true;
    }
    return QWidget::event(ev);
}

void Diagram::on_pushButton_clicked()
{
    bool ok;
    ui->lineEdit->text().toDouble(&ok);
    if (!ok){
        return;
    }
    ui->listWidget->addItem(ui->lineEdit->text());
    ui->lineEdit->setText("");
    paintEvent();
}

void Diagram::paintEvent(){
    QPainter* paint = new QPainter(ui->openGLWidget);
    paint->fillRect(QRectF(QPointF(0,0),QSizeF(ui->openGLWidget->width(),ui->openGLWidget->height())),Qt::white);
    QBrush br;
    br.setColor(Qt::blue);
    paint->setBrush(br);
    QVector<double> vec;
    for (int i = 0; i < ui->listWidget->count(); ++i){
        vec.push_back(ui->listWidget->item(i)->text().toDouble());
    }
    if (vec.size() == 0 || vec.size() == 1){
        paint->end();
        return;
    }
    double max = vec[0], min = vec[0];
    for (const auto& elem : vec){
        if (elem > max){
            max = elem;
        }
        if (elem < min){
            min = elem;
        }
    }
    double delta =(max - min)/much;
    QVector<QLabel*> lab{ui->x1,ui->x2,ui->x3,ui->x4};
    QVector<QLabel*> lab1{ui->first,ui->second,ui->third,ui->four};
    QVector<QString> style{"color: rgb(0,0,200)","color: rgb(200,0,0)","color: rgb(0,200,0)","color: rgb(200,200,0)"};
    QString str;
    QString string;
    for (int i = 0; i < much; ++i){
        int count = std::count_if(vec.begin(),vec.end(),[delta,i,min](double& number){
            if (i != 3){
                return min + delta*i <= number && min + delta*(i+1) > number;
            } else {
                return min + delta*i <= number && min + delta*(i+1) >= number;
            }
        });
        lab[i]->setText(QString::number(count));
        lab1[i]->setText("["+str.setNum(min + delta*i)+" , "+string.setNum(min + delta*(i+1)) + "]");
        double Mx = ui->openGLWidget->width()/much;
        double My = ui->openGLWidget->height()/(vec.size());
        paint->fillRect(QRectF(QPointF(Mx*i,ui->openGLWidget->height() - My*count),QSizeF(Mx,ui->openGLWidget->height())),Qt::blue);
    }
    paint->end();
}

