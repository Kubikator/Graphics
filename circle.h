#ifndef CIRCLE_H
#define CIRCLE_H

#include <QDialog>

namespace Ui {
class Circles;
}

class Circles : public QDialog
{
    Q_OBJECT

public:
    explicit Circles(QDialog *parent = nullptr);
    ~Circles();

private:
    Ui::Circles *ui;
};

#endif // CIRCLE_H
