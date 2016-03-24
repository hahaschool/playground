//
//  UVA11107.cpp
//  playground
//
//  Created by 張正昊 on 20/3/2016.
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

const int MAXN = 110005,MAXBUF = 1005;
//const int MAXN = 425,MAXBUF = 1005;

int sa[MAXN],t[MAXN],t2[MAXN],c[MAXN],n,rnk[MAXN],plc[MAXN];
void build_sa(char *str,int m){
    //Actually the str here is perproccessed to a string contains only 0~m-1
    int *x = t,*y = t2;//x是分类数组(1准，保存位置对应的名次) y是排序数组(2准，保存名次对应的位置)
    for (int i = 0; i < m; i++) c[i] = 0;
    for (int i = 0; i < n; i++) c[x[i] = str[i]]++;
    for (int i = 1; i < m; i++) c[i] += c[i-1];
    for (int i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (int i = n-k; i < n; i++) y[p++] = i;
        for (int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
        for (int i = 0; i < m; i++) c[i] = 0;
        for (int i = 0; i < n; i++) c[x[y[i]]]++;
        for (int i = 1; i < m; i++) c[i] += c[i-1];
        for (int i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for(int i = 1; i < n; i++) x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k]?p-1:p++;
        if (p >= n) break;
        m = p;
    }
    
    for(int i = 0; i < n; i++) rnk[sa[i]] = i;
    int k = 0;
    for(int i = 0; i < n; i++){
        if (k) k--;
        if(!rnk[i]) continue;
        int j = sa[rnk[i] - 1];
        while (str[j+k] == str[i+k]) k++;
        plc[rnk[i]] = k;
    }
}

int N,mxlen;
char str[MAXN],buf[MAXBUF];

inline char hah(char c){
    return c - 'a';
}

bool flg[MAXN];
int belong[MAXN];
void flgclear(){
    for(int i = 1; i <= N; i++){
        flg[i] = false;
    }
}
bool flgcheck(){
    int cnt = 0;
    for(int i = 1; i<= N; i++){
        if (flg[i]) {
            cnt++;
        }
    }
    return cnt > N/2;
}
bool check(int ll){
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (plc[i] < ll) {
            if (i - l > N/2) {
                flgclear();
                for(int j = l; j < i; j++){
                    flg[belong[sa[j]]] = true;
                }
                if (flgcheck()) {
                    return true;
                }
            }
            l = i;
        }
    }
    return false;
}

int solve(){
    build_sa(str, 128);
    int l = 1,r = mxlen,mid;
    while (l + 1 < r) {
        mid = l + (r-l)/2;
        if (check(mid)) {
            l = mid;
        }else{
            r = mid-1;
        }
    }
    if (check(r)) {
        return r;
    }else if(check(l)){
        return l;
    }else return 0;
}

void printans(int ll){
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (plc[i] < ll) {
            if (i - l > N/2) {
                flgclear();
                for(int j = l; j < i; j++){
                    flg[belong[sa[j]]] = true;
                }
                if (flgcheck()) {
                    for (int j = sa[l],k = 0; k < ll; j++,k++) {
                        putchar(str[j] + 'a');
                    }
                    puts("");
                }
            }
            l = i;
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while (scanf(" %d",&N) != EOF && N) {
        if (caseCnt++) {
            puts("");
        }
        n = 0;
        mxlen = 0;
        for(int i = 0; i < N; i++){
            scanf(" %s",buf);
            int buflen = (int)strlen(buf);
            mxlen = max(mxlen,buflen);
            for(int j = 0; j < buflen;j++){
                belong[n] = i+1;
                str[n++] = hah(buf[j]);
            }
            //belong[n] = i+1;
            str[n++] = 26+(char)i;
        }
        if (N == 1) {
            puts(buf);
            continue;
        }
        int res = solve();
        if (!res) {
            puts("?");
            continue;
        }
        //printf("%d\n",res);
        printans(res);
    }
    
    return 0;
}
