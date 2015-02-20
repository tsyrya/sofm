#ifndef SOM_H
#define SOM_H

#include <QtCore>
#include <QVector>
#include <QPair>

class som
{

public:
    som();
    som(QVector < QPair<int,int> >);
    som(int grid_size,int cell_size,int beginx,int beginy); //size - размер сетки, x-координата x для точки отсчета, y - координата y для точки отсчета
    int find_bmu(QPair<int,int> dot);
    //bool is_in_radius(QPair<int,int> fire_dot, QPair<int,int> fired_dot);
    void recalculate_weight(QPair <int,int> bmu, int current, int n, double eta);
    ~som();
    QVector < QPair<int,int> > dots;

private:


};

#endif // SOM_H
