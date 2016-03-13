//
//  LA6070.cpp
//  playground
//
//  Created by 張正昊 on 13/3/2016.
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

const int MAXN = 400005;
int n;
struct Edge{
    int a,b,c;
    bool operator < (const Edge &b) const{
        return c > b.c;
    }
} edge[MAXN];

struct disjointSet{
    int par[MAXN];
    long long num[MAXN];
    long long cst[MAXN];
        void init(){
            for(int i = 1; i<= n; i++){
                par[i] = i+n;
            }
            for(int i = n+1; i <= n*2; i++){
                par[i] = i;
                num[i] = 1;
                cst[i] = 0;
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
    bool check(int a,int b){
        return find(a) == find(b);
    }
} djset;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&n) != EOF) {
        djset.init();
        for(int i = 1; i<= n-1; i++){
            scanf(" %d %d %d",&edge[i].a,&edge[i].b,&edge[i].c);
        }
        sort(edge+1, edge+n);
        long long res = 0;
        for (int i = 1; i<= n-1; i++) {
            int pa = djset.find(edge[i].a);
            int pb = djset.find(edge[i].b);
            long long nL = djset.num[pa];
            long long nR = djset.num[pb];
            long long cL = djset.cst[pa];
            long long cR = djset.cst[pb];
            long long ncL = nR * (long long)edge[i].c + cL;
            long long ncR = nL * (long long)edge[i].c + cR;
            djset.num[pa] += djset.num[pb];
            djset.cst[pa] = max(ncL,ncR);
            res = max(res,djset.cst[pa]);
            djset.par[pb] = pa;
        }
        printf("%lld\n",res);
    }
    return 0;
}
