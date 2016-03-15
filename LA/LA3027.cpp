//
//  LA3027.cpp
//  playground
//
//  Created by 張正昊 on 15/3/2016.
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

const int MAXN = 20005;
int par[MAXN];
int dtp[MAXN];//dis to par
int n;
void clr(){
    for(int i = 1; i <= n; i++){
        par[i] = i;
        dtp[i] = 0;
    }
}
inline int dis(int u,int v){
    return abs(u-v)%1000;
}
int find(int a){
    if (par[a] == a) {
        return a;
    }
    int rt = find(par[a]);//注意要先find才能把par[a]的dtp更新到根部，否则只能往上一层！
    dtp[a] += dtp[par[a]];
    par[a] = rt;
    return par[a];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        scanf(" %d",&n);
        clr();
        char typ;
        while (scanf(" %c",&typ) && typ != 'O') {
            if (typ == 'I') {
                int u,v;
                scanf(" %d %d",&u,&v);
                par[u] = v;
                dtp[u] = dis(u, v);
            }else if(typ == 'E'){
                int u;
                scanf(" %d",&u);
                find(u);
                printf("%d\n",dtp[u]);
            }
        }
    }
    
    return 0;
}
