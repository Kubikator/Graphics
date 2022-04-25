#include"SolvingFunctions.h"

QVector<QPointF> getPoints(QOpenGLWidget* pw,float a,float b,Queue ue,float* max, float* min){
    QVector<QPointF> vec;
    if (a != b){
        float Mx = pw->width()/(b-a);
        float h = pow(Mx,-1);
        vec.reserve((b-a)/h);
        for (double x = a; x < b + h/2; x +=h){
            try{
                Queue queue = ue.copy();
                vec.push_back(QPointF(static_cast<float>(x),static_cast<float>(solve_poland(queue,&x))));
            } catch (QString str){
                continue;
            }
        }
        float Ymax = vec[0].y();
        float Ymin = vec[0].y();
        for (const auto& point : vec){
            if (point.y() > Ymax){
                Ymax = point.y();
            }
            if (point.y() < Ymin){
                Ymin = point.y();
            }
        }
        *max = Ymax;
        *min = Ymin;
        float My = Ymax != Ymin ? pw->height()/(Ymax - Ymin) : pw->height()/2;
        for (auto& point : vec){
            point.setX(Mx * (point.x() - a));
            point.setY(Ymax != Ymin? pw->height() - My * (point.y() - Ymin) : My);
        }
    } else {
        double x = a;
        Queue queue = ue.copy();
        *max = solve_poland(queue,&x);
        *min = *max;
        vec.push_back(QPointF(static_cast<float>(a),static_cast<float>(*max)));
    }
    return vec;
}

QVector<QPointF> getPoints(QOpenGLWidget* pw,float a,float b,Queue& ue,int zoom,float* Yma, float* Ymi){
    QVector<QPointF> vec;
    if (a!=b){
        float Mx = pw->width()/zoom;
        float h = pow(pw->width()/(b-a),-1);
        vec.reserve((b-a)/h);
        for (double x = a; x < b + h/2; x +=h){
            Queue queue = ue.copy();
            try{
            vec.push_back(QPointF(static_cast<float>(x),static_cast<float>(solve_poland(queue,&x))));
            } catch (QString str){
                continue;
            }
        }
        float Ymax = vec[0].y();
        float Ymin = vec[0].y();
        for (const auto& point : vec){
            if (point.y() > Ymax){
                Ymax = point.y();
            }
            if (point.y() < Ymin){
                Ymin = point.y();
            }
        }
        float My = Ymax != Ymin? pw->height()/(Ymax - Ymin) : pw->height()/2;
        for (auto& point : vec){
            point.setX(Mx * (point.x() - a));
            point.setY(Ymax != Ymin? pw->height() - My * (point.y() - Ymin) : My);
        }
        *Yma = Ymax;
        *Ymi = Ymin;
    }
    return vec;
}

