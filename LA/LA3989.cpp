//
//  LA3989.cpp
//  playground
//
//  Created by 張正昊 on 4/3/2016.
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

const int MAXN = 1005;
int gpfb[MAXN][MAXN],bpfg[MAXN][MAXN],n;
int Mb[MAXN],Mg[MAXN],Qb[MAXN];
set<int> Qg[MAXN];

bool check(){
    for(int i = 1; i<= n; i++){
        if (!Mb[i]) {
            return false;
        }
    }
    return true;
}

void solve(){
    for(int i = 1; i <= n; i++){
        Mb[i] = Mg[i] = Qb[i] = 0;
    }
    while (!check()) {
        for (int i = 1; i <= n; i++) {
            Qg[i].clear();
        }
        for (int i = 1; i <= n; i++) {
            if (!Mb[i]) {
                Qg[bpfg[i][++Qb[i]]].insert(i);
            }
        }
        for(int i = 1;i <= n; i++){
            if (Qg[i].size()) {
                for(int j = 1; j <= n; j++){
                    if (Mg[i] == gpfb[i][j]) {
                        break;//ISSUE:当前匹配上的男人也要参与比较
                    }
                    if (Qg[i].count(gpfb[i][j])){
                        if (Mg[i]) {
                            Mb[Mg[i]] = 0;
                        }
                        Mg[i] = gpfb[i][j];
                        Mb[Mg[i]] = i;
                        break;
                    }
                }
            }
        }
    }
    for(int i = 1; i <= n; i++){
        printf("%d\n",Mb[i]);
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt;d++){
        scanf(" %d",&n);
        for(int i = 1;i <= n; i++){
            for(int j = 1;j <= n; j++){
                scanf(" %d",&bpfg[i][j]);
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                scanf(" %d",&gpfb[i][j]);
            }
        }
        solve();
        if (d != caseCnt) {
            puts("");
        }
    }
    
    
    return 0;
}