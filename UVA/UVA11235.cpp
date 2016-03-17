//
//  UVA11235.cpp
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
int n,q;
int seq[MAXN];
int rem[MAXN],lem[MAXN],itv[MAXN];
int tot;
struct RLE{
    int val,len;
} rsq[MAXN];
int d[MAXN][32];
int id[MAXN][32];

void prep(){
    //RLE Part:
    tot = 0;
    for (int i = 1; i <= n; i++) {
        ++tot;
        int j = i+1;
        rem[i] = 1;
        while (seq[j] == seq[i]) {
            rem[j] = rem[j-1] + 1;
            j++;
        }j--;
        for (int k = j,l = 1; k >= i; k--,l++) {
            lem[k] = l;
            itv[k] = tot;
        }
        i = j;
        rsq[tot] = {seq[i],rem[i]};
    }
    
    //RMQ Part:
    for (int i = 1; i <= tot; i++) {
        d[i][0] = rsq[i].len;
        id[i][0] = i;
    }
    for (int j = 1; (1 << j) <= tot; j++) {
        for (int i = 1; i + (1 << j) - 1 <= tot; i++) {
            if (d[i][j-1] > d[i + (1 << (j-1))][j-1]) {
                id[i][j] = id[i][j-1];
            }else{
                id[i][j] = id[i + (1 << (j-1))][j-1];
            }
            d[i][j] = max(d[i][j-1] , d[i + (1 << (j-1))][j-1]);
        }
    }
}

RLE rmq(int l,int r){
    int k = 0;
    while ((1 << (k+1)) <= r-l+1) {
        k++;
    }
    if (d[l][k] > d[r-(1 << k)+1][k]) {
        return rsq[id[l][k]];
    }else{
        return rsq[id[r-(1 << k)+1][k]];
    }
}

int query(int l,int r){
    if (itv[l] == itv[r]) {
        return r-l+1;
    }else{
        int llen = lem[l];
        int rlen = rem[r];
        if (itv[l] + 1 < itv[r]) {
            RLE atp = rmq(itv[l]+1, itv[r]-1);
            return max(max(llen,rlen),atp.len);
        }
        return max(llen,rlen);
    }
}

int main(){
//#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r", stdin);
//#endif
    while (scanf(" %d",&n) != EOF && n) {
        scanf(" %d",&q);
        for (int i = 1; i<= n; i++) {
            scanf(" %d",&seq[i]);
        }
        prep();
        for(int i = 1; i <= q;i++){
            int l,r;
            scanf(" %d %d",&l,&r);
            printf("%d\n",query(l, r));
        }
    }
    
    
    return 0;
}
