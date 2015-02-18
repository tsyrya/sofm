#include "som.h"
#include <cmath>

som::som()
{

}

som::som(QVector < QPair<int,int> > v)
{
    this->dots = v;
}

som::som(int grid_size,int cell_size, int beginx, int beginy){
    for(int i=0;i<grid_size;i++)
        for(int j=0;j<grid_size;j++)
            this->dots.push_back(QPair<int,int> (beginx+i*cell_size,beginy+j*cell_size));
}

void som::recalculate_weight(QPair<int, int> bmu, int current, int n, double eta){
    this->dots[current].first += eta * (bmu.first-this->dots[current].first);
    this->dots[current].second += eta * (bmu.second-this->dots[current].second);
}

int som::find_bmu(QPair<int, int> dot){
    int bmu_index =0;
    int min_dist = (int)pow(dot.first-this->dots[0].first,2)+(int)pow(dot.second-this->dots[0].second,2);
    for (int i=1;i<this->dots.length();i++){
        int dist = (int)pow(dot.first-this->dots[i].first,2)+(int)pow(dot.second-this->dots[i].second,2);
        if (dist<min_dist){
            bmu_index = i;
            min_dist = dist;
        }
    }
    return bmu_index;
}

som::~som(){
    this->dots.clear();
}
