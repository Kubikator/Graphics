#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QDialog>
#include<QPainter>
#include<QPoint>

namespace Ui {
class Diagram;
}

class Diagram : public QDialog
{
    Q_OBJECT

public:
    explicit Diagram(QWidget *parent = nullptr);
    ~Diagram();

private slots:

    void on_pushButton_clicked();

    void paintEvent();

    bool event(QEvent* ev);

private:
    Ui::Diagram *ui;
    int much = 4;
};

#endif // DIAGRAM_H
