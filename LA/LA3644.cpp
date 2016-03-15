//
//  LA3644.cpp
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

const int MAXN = 100005;
int n;

int par[MAXN];
void init(){
    for(int i = 1; i<= n; i++){
        par[i] = i;
    }
}
int find(int a){
    if (par[a] == a) {
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



int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int x,y,res = 0;
    n = 100001;
    init();
    while (scanf(" %d",&x) != EOF) {
        if (x == -1) {
            printf("%d\n",res);
            init();
            res = 0;
            continue;
        }
        scanf(" %d",&y);
        if (check(x, y)) {
            res++;
            continue;
        }
        link(x, y);
    }
    return 0;
}
