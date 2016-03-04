//
//  HDU4035.cpp
//  playground
//
//  Created by Adam Chang on 2015/4/5.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//
//Review: Each pair of rooms is connected by one and only one path
//this statement marks the structure is tree (or DAG),i.e. no rings.

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

using namespace std;

struct vertexType{
    vector<int> to;
    double pk,pe;
    void init(){
        to.clear();
        pk = 0;
        pe = 0;
    }
} vertex[10005];

double A[10005],B[10005],C[10005];
bool vis[10005];
void dfs(int father){
    vis[father] = true;
    vector<int> child;
    for (int i = 0; i < vertex[father].to.size(); i++) {
        int next = vertex[father].to[i];
        if (vis[next]) {
            continue;
        }
        child.push_back(next);
        dfs(next);
    }
    
    double w = 1-vertex[father].pk-vertex[father].pe;
    if (child.size()) {
        //normal vertex
        double m = (double)vertex[father].to.size();
        double q = 1;
        double e = vertex[father].pk;
        double r = w;
        for (int i = 0; i < child.size(); i++) {
            e += w/m*A[child[i]];
            q -= w/m*B[child[i]];
            r += w/m*C[child[i]];
        }
        A[father] = e/q;
        B[father] = w/m/q;
        C[father] = r/q;
    }else{
        //endpoint vertex
        A[father] = vertex[father].pk;
        B[father] = w;
        C[father] = w;
    }
}


int main(){
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int ci = 1; ci <= caseCnt; ci++) {
        int n = 0;
        scanf(" %d",&n);
        for (int i = 1; i <= n; i++) {
            vertex[i].init();
        }
        for (int i = 1; i <= n-1; i++) {
            int arg1,arg2;
            scanf(" %d %d",&arg1,&arg2);
            vertex[arg1].to.push_back(arg2);
            vertex[arg2].to.push_back(arg1);
        }
        for (int i = 1; i <= n; i++) {
            double arg1,arg2;
            scanf(" %lf %lf",&arg1,&arg2);
            vertex[i].pk = arg1/100;
            vertex[i].pe = arg2/100;
        }
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        memset(C, 0, sizeof(C));
        memset(vis, 0, sizeof(vis));
        dfs(1);
        if (abs(1-A[1]) < 0.000000001) {//这里卡精度
            printf("Case %d: impossible\n",ci);
            continue;
        }
        printf("Case %d: %.10lf\n",ci,C[1]/(1-A[1]));
    }
    return 0;
}