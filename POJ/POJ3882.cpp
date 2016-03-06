//
//  POJ3882.cpp
//  playground
//
//  Created by 張正昊 on 6/3/2016.
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

struct SAM_Node{
    int mxn;
    int to[26];
    int parent;
    int rightmost;
    int time;
    void init(){
        mxn = 0;
        parent = -1;
        rightmost = time = 0;
        memset(to, -1, sizeof(to));
    }
} pool[MAXN*2];

int SAM_tot;

void SAM_init(){
    pool[0].init();
    SAM_tot = 1;
}

int SAM_Append(int last,int ch){
    int p = last;
    int np = SAM_tot++;
    pool[np].init();
    pool[np].mxn = pool[p].mxn+1;
    while (p != -1 && pool[p].to[ch] == -1) {
        pool[p].to[ch] = np;
        p = pool[p].parent;
    }
    if (p != -1) {
        int q = pool[p].to[ch];
        if (pool[q].mxn == pool[p].mxn + 1) {
            pool[np].parent = q;
        }else{
            int nq = SAM_tot++;
            pool[nq] = pool[q];
            pool[nq].mxn = pool[p].mxn+1;
            pool[q].parent = nq;
            pool[np].parent = nq;
            while(p != -1 && pool[p].to[ch] == q){
                pool[p].to[ch] = nq;
                p = pool[p].parent;
            }
        }
    }else{
        pool[np].parent = 0;
    }
    return np;
}

int term[MAXN];

void SAM_build(char* str,int len){
    SAM_init();
    int lst = 0;
    for(int i = 0; i< len; i++){
        lst = SAM_Append(lst, str[i]-'a');
        term[i] = lst;
    }
}

int m;
char str[MAXN];
int len;

struct DPH{
    int mxn,id;
    bool operator < (const DPH &b)const{
        return mxn > b.mxn;
    }
} aux[MAXN*2];

void solve(){
    for(int i = 0; i< len; i++){
        pool[term[i]].rightmost = i+1;
        pool[term[i]].time = 1;
    }
    for(int i = 0; i < SAM_tot; i++){
        aux[i].mxn = pool[i].mxn;
        aux[i].id = i;
    }
    sort(aux,aux+SAM_tot);
     
    for(int i = 0; i < SAM_tot; i++){
        int inode = aux[i].id;
        if (pool[inode].parent != -1) {
            pool[pool[inode].parent].time += pool[inode].time;
            pool[pool[inode].parent].rightmost = max(pool[pool[inode].parent].rightmost,pool[inode].rightmost);
        }
    }
    int rm = -1,mxl = -1;
    for(int i = 1; i< SAM_tot; i++){
        if (pool[i].time >= m) {
            if (pool[i].mxn > mxl) {
                rm = pool[i].rightmost;
                mxl = pool[i].mxn;
            }else if(pool[i].mxn == mxl){
                rm = max(rm,pool[i].rightmost);
            }
        }
    }
    if (mxl == -1) {
        puts("none");
    }else{
        printf("%d %d\n",mxl,rm-mxl);
    }
}

int main(){
//#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r", stdin);
//#endif
    while (scanf(" %d",&m) != EOF && m) {
        scanf(" %s",str);
        SAM_build(str, len=strlen(str));
        solve();
    }
    
    
    return 0;
}
