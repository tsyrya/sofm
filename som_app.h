#ifndef SOM_APP_H
#define SOM_APP_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <som.h>

namespace Ui {
class som_app;
}

class som_app : public QMainWindow
{
    Q_OBJECT

public:
    explicit som_app(QWidget *parent = 0);
    ~som_app();

private slots:
    void on_pushButton_clicked();

    void on_start_algo_clicked();

private:
    Ui::som_app *ui;
    QGraphicsScene* scene;
    QImage* image;
    QPixmap pixmap;
    QGraphicsPixmapItem* pixmapitem;
    QVector < QPair<int,int> > dots;

    int rad;
    int grid_size;
    int cell_size;
    int n0;
    int nmax;
    double alpha;
    double amin;
    double change_radius;

    som* net;

    void draw_nets(QVector < QPair<int,int> > v,int grid_size);
    int generate_index_of_dot();
    double a(int n);
    double eta (int n, int ibmu, int jbmu,int i,int j);
    bool is_in_radius(QPair<int,int> fire_dot, QPair<int,int> fired_dot);
    void start_algo();
    void redraw();
};

#endif // SOM_APP_H
