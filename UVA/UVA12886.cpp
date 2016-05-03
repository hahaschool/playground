//
//  UVA12886.cpp
//  playground
//
//  Created by 張正昊 on 1/5/2016.
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

const int MAXN = 2005;

int n,m,np,mp;
bool str[MAXN][MAXN],pat[MAXN][MAXN];
unsigned long long strh[MAXN][MAXN],path[MAXN][MAXN],pw[MAXN*MAXN];
inline int sgn(bool a){
    return a?1:2;
}
inline int pos(int i,int j){
    return (i-1)*n+(j-1);
}

unsigned long long seed;

void prepare(){
    seed = rand();
    pw[0] = 1;
    for (int i = 1;i < MAXN*MAXN; i++) {
        pw[i] = pw[i-1] * seed;
    }
}

void make(){
    for(int i = 1;i <= n; i++){
        for(int j = 1; j<= m; j++){
            strh[i][j] = sgn(str[i][j]) * pw[pos(i,j)] + strh[i-1][j] + strh[i][j-1] - strh[i-1][j-1];
        }
    }
    for (int i = 1; i <= np; i++) {
        for (int j = 1; j<= mp;j++) {
            path[i][j] = sgn(pat[i][j]) * pw[pos(i,j)] + path[i-1][j] + path[i][j-1] - path[i-1][j-1];
        }
    }
}

unsigned long long extract(int ai,int aj,int bi,int bj){
    unsigned long long ret = strh[bi][bj];
    ret -= strh[ai-1][bj];
    ret -= strh[bi][aj-1];
    ret += strh[ai-1][aj-1];
    return ret;
}

void solve(){
    make();
    int res = 0;
    for (int ai = 1,bi = np; bi <= n; ai++,bi++) {
        for(int aj = 1,bj = mp; bj <= m; aj++,bj++){
            if (extract(ai, aj, bi, bj) == path[np][mp] * pw[pos(ai,aj)]) {
                res++;
            }
        }
    }
    printf("%d\n",res);
}



int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    srand(time(NULL));
    prepare();
    while (scanf(" %d %d %d %d",&np,&mp,&n,&m) != EOF) {
        for (int i = 1; i <= np; i++) {
            for (int j = 1;j <= mp; j++) {
                char cr;
                scanf(" %c",&cr);
                pat[i][j] = cr == 'o';
            }
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                char cr;
                scanf(" %c",&cr);
                str[i][j] = cr == 'o';
            }
        }
        solve();
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    return 0;
}
