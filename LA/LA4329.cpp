//
//  LA4329.cpp
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
int fenwick[MAXN],n;
int seq[20005];
inline int lowbit(int a){
    return (a)&(-a);
}
int sum(int x){
    int ret = 0;
    while (x > 0) {
        ret += fenwick[x];
        x -= lowbit(x);
    }
    return ret;
}
void add(int x,int val){
    while (x <= 100000) {
        fenwick[x] += val;
        x += lowbit(x);
    }
}

int l[20005],r[20005];

void solve(){
    long long ret = 0;
    memset(fenwick, 0, sizeof(fenwick));
    for (int i = 1; i <= n; i++) {
        l[i] = sum(seq[i]-1);
        add(seq[i], 1);
    }
    memset(fenwick, 0, sizeof(fenwick));
    for (int i = n; i >= 1; i--) {
        r[i] = sum(100000) - sum(seq[i]);
        add(seq[i], 1);
    }
    for (int i = 1; i <= n; i++) {
        ret += (long long)l[i] * (long long)r[i];
    }
    memset(fenwick, 0, sizeof(fenwick));
    for (int i = 1; i <= n; i++) {
        l[i] = sum(100000) - sum(seq[i]);
        add(seq[i], 1);
    }
    memset(fenwick, 0, sizeof(fenwick));
    for (int i = n; i >= 1; i--) {
        r[i] = sum(seq[i]-1);
        add(seq[i], 1);
    }
    for (int i = 1; i <= n; i++) {
        ret += (long long)l[i] * (long long)r[i];
    }
    printf("%lld\n",ret);
}

int main(){
//#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r", stdin);
//#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d",&n);
        for (int i = 1; i <= n; i++) {
            scanf(" %d",&seq[i]);
        }
        solve();
    }
    return 0;
}
