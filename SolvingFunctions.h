#ifndef SOLVINGFUNCTIONS_H
#define SOLVINGFUNCTIONS_H

#include<QVector>
#include<QWidget>
#include<QPainter>
#include<cmath>
#include<QOpenGLWidget>
#include"../PolandCalculator/queue.h"
#include"../PolandCalculator/mainwindow.h"
//#include"widget.h"

QVector<QPointF> getPoints(QOpenGLWidget* pw,float a,float b,Queue ue,float* max, float* min);
QVector<QPointF> getPoints(QOpenGLWidget* pw,float a,float b,Queue& ue,int zoom,float* Yma, float* Ymi);


#endif // SOLVINGFUNCTIONS_H
