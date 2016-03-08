//
//  CF651C.cpp
//  playground
//
//  Created by 張正昊 on 7/3/2016.
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

map<pair<int, int>,int> cntmp;
int n;
struct Point{
    int x,y;
} pt[200005];

bool cpx(const Point &a,const Point &b){
    if(a.x != b.x){
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool cpy(const Point &a,const Point &b){
    if (a.y != b.y) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

long long dcs(long long sx,long long mx){
    return (sx+mx)*(mx-sx+1)/2;
}

int main(){
    scanf(" %d",&n);
    cntmp.clear();
    for(int i  =1; i<= n; i++){
        scanf(" %d %d",&pt[i].x,&pt[i].y);
        cntmp[make_pair(pt[i].x, pt[i].y)]++;
    }
    sort(pt+1, pt+1+n, cpx);
    long long res = 0;
    for (int i = 1;i <= n; i++) {
        int j = i;
        long long cnt = 0;
        while (pt[j].x == pt[i].x && j <= n) {
            cnt++;
            j++;
        }j--;
        if (cnt > 1) {
            res += dcs(1,cnt-1);
        }
        i = j;
    }
    sort(pt+1, pt+1+n, cpy);
    for (int i = 1;i <= n; i++) {
        int j = i;
        long long cnt = 0;
        while (pt[j].y == pt[i].y && j <= n) {
            cnt++;
            j++;
        }j--;
        if (cnt > 1) {
            res += dcs(1,cnt-1);
        }
        i = j;
    }
    for(map<pair<int, int>,int>::iterator it=cntmp.begin();it != cntmp.end();it++){
        if (it->second > 1) {
            res -= dcs(1,it->second-1);
        }
    }
    cout << res << endl;
    
}