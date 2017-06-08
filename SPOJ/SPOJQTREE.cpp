#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 100005;
int ch[MAXN][2],par[MAXN],key[MAXN],siz[MAXN];
int tot,root;

int pathpar[MAXN];

void clear(int id){
    ch[id][0] = ch[id][1] = -1;
    key[id] = -1, par[id] = -1, siz[id] = -1;
}

int alloc(){
    clear(tot);
    return tot++;
}

void maintain(int u){
    int l = ch[u][0], r = ch[u][1];
    int lsiz = 0,rsiz = 0;
    if(l != -1) lsiz = siz[l];
    if(r != -1) rsiz = siz[r];
    siz[u] = lsiz + rsiz + 1;
}

void recursive_maintain(int u){
    maintain(u);
    if(par[u] != -1) recursive_maintain(par[u]);
}

void pushdown(int u){
    
}

void recursive_pushdown(int u){
    if(par[u] != -1) recursive_pushdown(par[u]);
    pushdown(u);
}

void rotate(int u){
    int p = par[u], gp = par[p], d = (ch[p][0] == u)?0:1, gd;
    ch[p][d] = ch[u][d^1];if(ch[p][d] != -1) par[ch[p][d]] = p;
    ch[u][d^1] = p, par[p] = u, par[u] = gp;
    if(gp != -1) gd = (ch[gp][0] == p)?0:1, ch[gp][gd] = u;
    maintain(p), maintain(u);
    if(gp != -1) maintain(gp);
}

void splay(int u,int rt){
    recursive_pushdown(u);
    while(par[u] != rt){
        int p = par[u], gp = par[p];
        if(gp == rt) rotate(u);
        else if((ch[gp][0] == p) == (ch[p][0] == u)) rotate(p),rotate(u);
        else rotate(u),rotate(u);
    }
    recursive_maintain(u);
}

void access(int u){
    splay(u,-1);
    pathpar[ch[u][1]] = u;
    par[ch[u][1]] = -1;ch[u][1] = -1;
    while(u != -1){
        int p = pathpar[u];
        splay(p,-1);
        par[u] = p;
        ch[p][1] = u;
        pathpar[u] = -1;
        u = p;
    }
}




int main(int argc, char *argv[]) {

    

    return 0;
}
