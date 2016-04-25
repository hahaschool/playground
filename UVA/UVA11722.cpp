//
//  UVA11722.cpp
//  playground
//
//  Created by 張正昊 on 25/4/2016.
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

int s1,s2,t1,t2,w;

double getArea(int ww){
    double ret = 0;

    if (s1 >= t2 + ww) {
        ret = (s2-s1)*(t2-t1);
    }else if (s2 <= t1 + ww) {
        ret = 0;
    }else{
        if (s1 <= t1 + ww) {
            ret = ((s2 - (t1 + ww)) * (s2 - (t1 + ww)))/2.0;
        }else if(s2 <= t2 + ww){
            double tri = ((s2-s1)*(s2-s1))/2.0;
            double par = (s1 - ww - t1) * (s2 - s1);
            ret = tri + par;
        }else{
            double cpl = ((t2 + ww - s1) * (t2 + ww - s1))/ 2.0;
            ret = (s2-s1)*(t2-t1) - cpl;
        }
    }
    if (ww < 0) {
        return (s2-s1)*(t2-t1)-ret;
    }
    return ret;
}

void solve(){
    if ((s2-s1) > (t2-t1)) {
        swap(s1, t1);
        swap(s2, t2);
    }
    double cpl1 = getArea(w);
    double cpl2 = getArea(-w);
    double area = (s2-s1)*(t2-t1);
    printf("%.8lf\n",(area-cpl1-cpl2)/area);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        printf("Case #%d: ",d);
        scanf(" %d %d %d %d %d",&t1,&t2,&s1,&s2,&w);
        solve();
    }
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
