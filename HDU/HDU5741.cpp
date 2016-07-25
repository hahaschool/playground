//
//  HDU5741.cpp
//  playground
//
//  Created by 張正昊 on 22/7/2016.
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

typedef long long LL;
const int MAXN = 1005*1005;
int n,m;
LL run_all[MAXN],run_zerosum[MAXN],run_onesum[MAXN];

struct Point{
    LL x,y;
    Point operator - (const Point &b) const{
        return {x-b.x,y-b.y};
    }
    bool operator < (const Point &b) const{
        if(x != b.x) return x < b.x;
        return y < b.y;
    }
};

LL Cross(Point A,Point B){
    return A.x*B.y - A.y*B.x;
}

set<Point> upper,lower;
Point upper_convex[MAXN],lower_convex[MAXN];
int upper_m,lower_m;

void prep(){
    for (int i = 1; i <= n; i++) {
        if(i&1) run_zerosum[i] = run_all[i], run_onesum[i] = 0;
        else run_onesum[i] = run_all[i], run_zerosum[i] = 0;
        run_zerosum[i] += run_zerosum[i-1];
        run_onesum[i] += run_onesum[i-1];
    }
    upper.clear();
    lower.clear();
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if(i&1 && j&1){
                //both being zero
                lower.insert({run_zerosum[j] - run_zerosum[i-1],run_onesum[j] - run_onesum[i-1]});
            }else if(!(i&1) && !(j&1)){
                //both being one
                upper.insert({run_zerosum[j] - run_zerosum[i-1],run_onesum[j] - run_onesum[i-1]});
            }
        }
    }
    
    //Convex
    lower_m = 0;
    for (set<Point>::iterator it = lower.begin(); it != lower.end(); it++) {
        if(lower_m >= 1 && it->y >= lower_convex[lower_m-1].y && it->x <= lower_convex[lower_m-1].x) continue;
        while (lower_m >= 1 && it->y <= lower_convex[lower_m-1].y) {
            lower_m--;
        }
        lower_convex[lower_m++] = *it;
    }
    
    upper_m = 0;
    for (set<Point>::reverse_iterator it = upper.rbegin(); it != upper.rend(); it++) {
        if(upper_m >= 1 && it->y <= upper_convex[upper_m-1].y && it->x >= upper_convex[upper_m-1].x) continue;
        while(upper_m >= 1 && it->y >= upper_convex[upper_m-1].y){
            upper_m--;
        }
        upper_convex[upper_m++] = *it;
    }
    sort(upper_convex, upper_convex+upper_m);
}

bool query(Point a){
    //find the first point in upper side that have lower/equal x value
    //find the first point in lower side that have bigger/equal x value
    int uub = upper_bound(upper_convex, upper_convex+upper_m, (Point){a.x,0x3f3f3f3f3f3f3f3fLL}) - upper_convex;
    int llb = upper_bound(lower_convex, lower_convex+lower_m, (Point){a.x,-0x3f3f3f3f3f3f3f3fLL}) - lower_convex;
    return llb < lower_m && a.y >= lower_convex[llb].y && a.y <= upper_convex[uub-1].y;
}

int main(int argc, const char * argv[]){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d %d",&n,&m);
        for (int i = 1; i <= n; i++) {
            scanf(" %lld",&run_all[i]);
        }
        prep();
        for (int i = 1; i <= m; i++) {
            LL a,b;
            scanf(" %lld %lld",&a,&b);
            if(query({a,b})) putchar('1');
            else putchar('0');
        }
        puts("");
    }
#ifndef ONLINE_JUDGE
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
