//
//  LA6889.cpp
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

const int MAXN = 50005;
int n;

struct disjointSet{
    int par[MAXN];
    void init(){
        for(int i = 1; i<= n; i++){
            par[i] = i;
        }
    }
    int find(int a){
        if(par[a] == a){
            return a;
        }
        return par[a] = find(par[a]);
    }
    void link(int a,int b){
        par[find(a)] = find(b);
    }
} djset;

struct RECT{
    int x,y,w,h;
} rect[MAXN];

struct Segment{
    int y,xa,xb,rectid;
    //also x,ya,yb
    bool operator < (const Segment &b) const{
        if(y == b.y){
            if(xa == b.xa){
                return xb < b.xb;
            }
            return xa < b.xa;
        }
        return y < b.y;
    }
} segX[MAXN*2],segY[MAXN*2];
int segtot;


int area[MAXN];
void solve(){
    djset.init();
    sort(segX+1,segX+1+segtot);
    int right = 0,cury = -segX[1].y-1,prv = -1;
    //ISSUE:the original cury = -segX[1].y may be hacked when segX[1] = 0
    for (int i = 1; i <= segtot; i++) {
        if(segX[i].y == cury){
            if (segX[i].xa <= right) {
                djset.link(segX[prv].rectid, segX[i].rectid);
            }
            if (segX[i].xb > right) {
                right = segX[i].xb;
                prv = i;
            }
        }else{
            cury = segX[i].y;
            right = segX[i].xb;
            prv = i;
        }
    }
    
    sort(segY+1,segY+1+segtot);
    cury = -segY[1].y-1,prv = -1;
    for (int i = 1; i <= segtot; i++) {
        if(segY[i].y == cury){
            if (segY[i].xa <= right) {
                djset.link(segY[prv].rectid, segY[i].rectid);
            }
            if (segY[i].xb > right) {
                right = segY[i].xb;
                prv = i;
            }
        }else{
            cury = segY[i].y;
            right = segY[i].xb;
            prv = i;
        }
    }
    
    int res = 0;
    for(int i = 1; i<= n; i++){
        area[i] = 0;
    }
    for(int i = 1;i <= n; i++){
        area[djset.find(i)] += rect[i].w*rect[i].h;
        res = max(res,area[djset.find(i)]);
    }
    printf("%d\n",res);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&n) != EOF) {
        segtot = 0;
        for (int i = 1; i <= n; i++) {
            scanf(" %d %d %d %d",&rect[i].x,&rect[i].y,&rect[i].w,&rect[i].h);
            segX[++segtot] = {rect[i].y,rect[i].x,rect[i].x+rect[i].w,i};
            segY[segtot] = {rect[i].x,rect[i].y,rect[i].y+rect[i].h,i};
            segX[++segtot] = {rect[i].y+rect[i].h,rect[i].x,rect[i].x+rect[i].w,i};
            segY[segtot] = {rect[i].x+rect[i].w,rect[i].y,rect[i].y+rect[i].h,i};
        }
        solve();
    }
    
    return 0;
}
