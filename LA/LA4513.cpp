//
//  LA4513.cpp
//  playground
//
//  Created by 張正昊 on 25/3/2016.
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

const int MAXN = 40005;
unsigned long long pp[MAXN];
unsigned long long hah[MAXN];

int n,m;
char str[MAXN];

void preproc(){
    pp[0] = 1,pp[1] = rand();
    for(int i = 2; i < MAXN; i++){
        pp[i] = pp[i-1] * pp[1];
    }
}

void prepare(){
    hah[0] = 0;
    for(int i = 0; i < n; i++){
        hah[i+1] = (unsigned long long)(str[i]) * pp[i];
        hah[i+1] += hah[i];
    }
}

struct Node{
    unsigned long long val;
    int pos;
    bool operator < (const Node &b) const{
        if(val != b.val) return val < b.val;
        return pos < b.pos;
    }
} arr[MAXN];
int tot;
bool check(int l,int &mxpos){
    tot = 0;
    for(int i = n-l+1,j = 0; i > 0; i--,j++){
        int lt = i,rt = i+l-1;
        unsigned long long val = (hah[rt] - hah[lt-1])*pp[j];
        arr[++tot] = {val,i-1};
    }
    sort(arr+1, arr+1+tot);
    bool flg = false;
    for(int i = 1; i <= tot; i++){
        int j = i,cnt = 0;
        while (arr[j].val == arr[i].val) {
            j++,cnt++;
        }j--;
        i = j;
        if (cnt >= m) {
            flg = true;
            mxpos = max(mxpos,arr[j].pos);
        }
    }
    return flg;
}

void solve(){
    prepare();
    int l = 1,r = n,mid,mxpos = -1;
    while (l + 1 < r) {
        mid = l + (r - l)/2;
        if(check(mid,mxpos)){
            l = mid;
        }else{
            r = mid-1;
        }
    }
    mxpos = -1;
    if(check(r,mxpos)){
        printf("%d %d\n",r,mxpos);
    }else{
        mxpos = -1;
        if(check(l, mxpos)){
            printf("%d %d\n",l,mxpos);
        }else{
            puts("none");
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    srand(time(NULL));
    preproc();
    while (scanf(" %d",&m) != EOF && m) {
        scanf(" %s",str);
        n = (int)strlen(str);
        solve();
    }
    return 0;
}
