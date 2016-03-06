//
//  LA4504.cpp
//  playground
//
//  Created by 張正昊 on 5/3/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <cmath>
#include <map>
#include <complex>

using namespace std;

const int MAXN = 50000;

double dis(double xa,double ya,double xb,double yb){
    return sqrt((xa-xb)*(xa-xb) + (ya-yb)*(ya-yb));
}

struct Point{
    double x,y;
} pt[MAXN];

const double EPS = 1e-10;
int n;

double get(double mtx){
    double ret = -1e6;
    for(int i = 1; i<= n; i++){
        ret = max(ret,dis(pt[i].x, pt[i].y, mtx, 0));
    }
    return ret;
}

void solve(){
    double l = -1e6,r = 1e6,ll = 0, rr = 0;
    while (abs(r - l) > EPS) {
        ll = l + (r-l)/3;
        rr = r - (r-l)/3;
        double lldis = get(ll);
        double rrdis = get(rr);
        if (lldis > rrdis) {
            l = ll;
        }else{
            r = rr;
        }
    }
    printf("%.9lf %.9lf\n",ll,get(ll));
}

int main(){
#ifndef ONLINE_JUDGE
    //freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&n) != EOF && n) {
        for(int i = 1; i<= n; i++){
            scanf(" %lf %lf",&pt[i].x,&pt[i].y);
        }
        solve();
    }
    
    return 0;
}