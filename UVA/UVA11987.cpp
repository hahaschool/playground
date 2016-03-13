//
//  UVA11987.cpp
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

const int MAXN = 200005;
int n,m;

struct disjointSet{
    int par[MAXN];
    int num[MAXN];
    long long sum[MAXN];
    void init(){
        for(int i = 1; i<= n; i++){
            par[i] = i+n;
        }
        for(int i = n+1; i <= n*2; i++){
            par[i] = i;
            num[i] = 1;
            sum[i] = i-n;
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
    while (scanf(" %d %d",&n,&m) != EOF) {
        djset.init();
        for(int i = 1; i <= m; i++){
            int typ,arg1,arg2;
            scanf(" %d",&typ);
            if (typ == 1) {
                scanf(" %d %d",&arg1,&arg2);
                int pa = djset.find(arg1);
                int pb = djset.find(arg2);
                if (pa == pb) {
                    continue;
                }
                djset.sum[pa] += djset.sum[pb];
                djset.num[pa] += djset.num[pb];
                djset.par[pb] = pa;
            }else if(typ == 2){
                scanf(" %d %d",&arg1,&arg2);
                int pa = djset.find(arg1);
                int pb = djset.find(arg2);
                if (pa == pb) {
                    continue;
                }
                djset.sum[pa] -= arg1;
                djset.num[pa] --;
                djset.sum[pb] += arg1;
                djset.num[pb] ++;
                djset.par[arg1] = pb;
            }else{
                scanf(" %d",&arg1);
                int pa = djset.find(arg1);
                printf("%d %lld\n",djset.num[pa],djset.sum[pa]);
            }
        }
    }
    
    return 0;
}
