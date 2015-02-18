#include "som_app.h"
#include "ui_som_app.h"
#include "cstdlib"

som_app::som_app(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::som_app)
{
    ui->setupUi(this);

    rad = 2;
    grid_size=25;
    cell_size = 10;
    nmax = 21500;
    alpha = 0.9;
    amin=0.0007;

    image = new QImage();
    image->load("/home/tsyrya/som_app/spot.bmp");
    for (int x=0;x<image->width();x++)
        for (int y=0;y<image->height();y++){
            if (image->pixel(x,y)!=qRgb(255,255,255)){
                image->setPixel(x,y,qRgb(0,0,0));
                dots.push_back(QPair<int,int>(x,y));
                ui->textEdit->insertPlainText(QString::number(x)+" "+QString::number(y)+"\n");
            }
        }

    pixmap = QPixmap::fromImage(*image);
    pixmapitem = new QGraphicsPixmapItem(pixmap);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(image->rect());
    scene->addItem(pixmapitem);
    ui->graphicsView->setScene(scene);

    int beginx = image->width()/2-(grid_size/2)*cell_size;
    int beginy = image->height()/2-(grid_size/2)*cell_size;
    net = new som(grid_size,cell_size,beginx,beginy);
    draw_nets(net->dots,grid_size);
}

som_app::~som_app()
{
    delete ui;
}


void som_app::start_algo(){
    for (int i = 1;i<=n0;i++){
        QPair<int,int> edu_dot = dots[generate_index_of_dot()];
        int bmu_index = net->find_bmu(edu_dot);
        net->recalculate_weight(edu_dot,bmu_index,i,eta(i,net->dots[bmu_index].first,net->dots[bmu_index].second,edu_dot.first,edu_dot.second));
    }
}

void som_app::draw_nets(QVector<QPair<int, int> > v,int grid_size){
    QBrush green (qRgb(38, 166, 91));
    QPen pen (qRgb(38, 166, 91));
    pen.setWidth(0);
    for(int i=0;i<v.length();i++){
        scene->addEllipse(v[i].first-rad,v[i].second-rad,rad*2,rad*2,pen,green);
        if (i % grid_size != 0) scene->addLine(v[i-1].first,v[i-1].second,v[i].first,v[i].second,pen);
        if (i>=grid_size) scene->addLine(v[i-grid_size].first,v[i-grid_size].second,v[i].first,v[i].second,pen);
    }
}

void som_app::redraw(){
    scene->clear();
    scene->addItem(pixmapitem);
    draw_nets();
}

int som_app::generate_index_of_dot(){
    int res = rand() % dots.length();
    return res;
}

double som_app::a(int n){
    double res = 0;
    if (n==1) res =  100;
    if (n==this->n0) res = 27;
    if (n<n0) res = (a(n0)-a(1))/n0 * (n0-n) +a(1);
    if (n>n0 && n<=nmax)
        res= a(n0) * (1-exp(5 * (n-nmax-n0)/(nmax+n0) )) * pow(0.005, (n-n0)/(nmax-n0)) + amin;
}

double som_app::eta(int n, int ibmu, int jbmu, i, j){
    double dist = pow(ibmu-i,2)+pow(jbmu-j,2);
    double n02 = pow(n,-0.2);
    double divisor = 2 * pow((a(n) * n02),2);
    return n02 * exp(-(dist/d));
}

void som_app::on_pushButton_clicked()
{
    scene->clear();
    scene->addItem(pixmapitem);
}

void som_app::on_start_algo_clicked()
{
    start_algo();
}
