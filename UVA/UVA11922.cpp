//
//  UVA11922.cpp
//  playground
//
//  Created by 張正昊 on 29/3/2016.
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

int ch[MAXN][2],par[MAXN],siz[MAXN],val[MAXN],lazy_flip[MAXN];
void init(int id){
    ch[id][0] = ch[id][1] = -1;
    par[id] = -1,siz[id] = 1,val[id] = 0;
    lazy_flip[id] = 0;
}
void maintain(int u){
    siz[u] = 1;
    if(ch[u][0] != -1) siz[u] += siz[ch[u][0]];
    if(ch[u][1] != -1) siz[u] += siz[ch[u][1]];
}
void pushdown(int u){
    if (lazy_flip[u]) {
        swap(ch[u][0], ch[u][1]);
        lazy_flip[u] = 0;
        if(ch[u][0] != -1) lazy_flip[ch[u][0]] ^= 1;
        if(ch[u][1] != -1) lazy_flip[ch[u][1]] ^= 1;
    }
}
void recursive_pushdown(int u){
    if (par[u] != -1) recursive_pushdown(par[u]);
    pushdown(u);
}
void rtp(int u){
    //Rotating u to the parent position
    int p = par[u],gp = par[p],d = (ch[p][0] == u)?0:1,gd;
    ch[p][d] = ch[u][d^1];
    if(ch[p][d]) par[ch[p][d]] = p;
    ch[u][d^1] = p,par[p] = u,par[u] = gp;;
    if(gp != -1) gd = (ch[gp][0] == p)?0:1,ch[gp][gd] = u;
    maintain(p),maintain(u);
    if(gp != -1) maintain(gp);
}
void splay(int u,int rt){
    //rt here is not actual rt but 1st lvl. parent!
    //to splay direct to root,assign rt as -1
    recursive_pushdown(u);
    while(par[u] != rt){
        int p = par[u],gp = par[p];
        if(gp == rt) rtp(u);
        else if((ch[gp][1] == p) == (ch[p][1] == u)) rtp(p),rtp(u);
        else rtp(u),rtp(u);
    }
}

int kth(int u,int k){
    if(u == -1 || siz[u] < k || k <= 0) return -1;
    pushdown(u);
    int lsiz = 0, rsiz = 0;
    if(ch[u][0] != -1) lsiz = siz[ch[u][0]];
    if(ch[u][1] != -1) rsiz = siz[ch[u][1]];
    if(lsiz + 1 == k) return u;
    else if(k <= lsiz) return kth(ch[u][0],k);
    else return kth(ch[u][1],k - lsiz - 1);
}

int n,m;
int root,tot;

void recursive_maintain(int u){
    maintain(u);
    if(par[u] != -1) recursive_maintain(par[u]);
}

void perform(int l,int r){
    if (l == 1 && r == n) {
        lazy_flip[root] ^= 1;
        return;
    }else if(l == 1){
        int rt = kth(root, r+1);
        splay(rt, -1),root = rt;
        int sub = ch[rt][0];
        lazy_flip[sub] ^= 1;
        ch[rt][0] = -1,recursive_maintain(rt);
        int lst = kth(root, n-siz[sub]);
        splay(lst, -1),root = lst;
        par[sub] = lst,ch[lst][1] = sub,recursive_maintain(lst);
    }else if(r == n){
        int lt = kth(root, l-1);
        splay(lt, -1),root = lt;
        int sub = ch[lt][1];
        lazy_flip[sub] ^= 1;
        ch[lt][1] = -1,recursive_maintain(lt);
        int lst = kth(root, n-siz[sub]);
        splay(lst, -1),root = lst;
        par[sub] = lst,ch[lst][1] = sub,recursive_maintain(lst);
    }else{
        int lt = kth(root, l-1);
        splay(lt, -1),root = lt;
        int rt = kth(root, r+1);
        splay(rt, root);
        int sub = ch[rt][0];
        lazy_flip[sub] ^= 1;
        ch[rt][0] = -1,recursive_maintain(rt);
        int lst = kth(root, n-siz[sub]);
        splay(lst, -1),root = lst;
        par[sub] = lst,ch[lst][1] = sub,recursive_maintain(lst);
    }
    
}


int build(int ll,int rr,int p){
    if(ll > rr) return -1;
    int x = ++tot,mid = (ll+rr)/2;
    init(x),par[x] = p,val[x] = mid;
    ch[x][0] = build(ll, mid-1, x);
    ch[x][1] = build(mid+1, rr, x);
    maintain(x);
    return x;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d",&n,&m) != EOF) {
        tot = 0;
        root = 1;
        build(1,n,-1);
        for(int i = 1; i <= m; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            perform(a, b);
        }
        
        for(int i = 1; i <= n; i++){
            int rt = kth(root, i); splay(rt, -1),root = rt;
            printf("%d\n",val[rt]);
        }
    }
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    return 0;
}
