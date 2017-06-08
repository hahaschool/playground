#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const double EPS = 1e-8;
int dcmp(double x){
    if(x < -EPS) return -1;
    if(x > EPS) return 1;
    return 0;
}

struct Point{
    double x,y;
    Point(double x = 0, double y = 0) : x(x),y(y){}
    Point operator + (const Point &b) const{
        return Point(x+b.x, y+b.y);
    }
    Point operator - (const Point &b) const{
        return Point(x-b.x,y-b.y);
    }
    Point operator * (const double &k) const{
        return Point(x*k,y*k);
    }
    Point operator / (const double &k) const{
        return Point(x/k,y/k);
    }
    Point operator - () const{
        return Point(-x,-y);
    }
    double len(){
        return sqrt(x*x + y*y);
    }
};

double dot(const Point &a,const Point &b){
    return a.x*b.x + a.y*b.y;
}

double cross(const Point a,const Point b){
    return a.x*b.y - a.y*b.x;
}

Point normal(Point a){
    double L = a.len();
    return Point(-a.y/L,a.x/L);
}

bool isLineParallel(Point a1, Point a2, Point b1, Point b2){
    return dcmp(cross(a2-a1,b2-b1)) == 0;
}



int N;
Point pts[66];

void solve(){
    
}

int main(int argc, char *argv[]){

    scanf(" %d",&N);
    for(int i = 1;i <= N; i++){
        scanf(" %lf %lf %lf %lf",&pts[i].x,&pts[i].y,&pts[i+N].x,&pts[i+N].y);
    }
    solve();

    return 0;
}
