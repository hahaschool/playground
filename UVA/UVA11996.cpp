//
//  UVA11996.cpp
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

const int MAXN = 1000005;

int ch[MAXN][2],val[MAXN],par[MAXN],siz[MAXN],flip[MAXN];
unsigned long long chr[MAXN],hah[MAXN],hah_rev[MAXN],pp[MAXN];

void init(int id){
    ch[id][0] = ch[id][1] = -1;
    val[id] = 0,par[id] = -1,siz[id] = 1,flip[id] = 0;
    hah[id] = 0,hah_rev[id] = 0;
}

int n,m,root,tot;

void prepare(unsigned long long seed){
    pp[0] = 1;
    for(int i = 1; i < MAXN; i++){
        pp[i] = pp[i-1] * seed;
    }
}

void maintain(int u){
    int lsiz = 0,rsiz = 0;
    if(ch[u][0] != -1) lsiz = siz[ch[u][0]];
    if(ch[u][1] != -1) rsiz = siz[ch[u][1]];
    siz[u] = lsiz + rsiz + 1;
    hah[u] = chr[u] * pp[lsiz],hah_rev[u] = chr[u] * pp[rsiz];
    if(lsiz) hah[u] += hah[ch[u][0]],hah_rev[u] += hah_rev[ch[u][0]] * pp[rsiz + 1];
    if(rsiz) hah[u] += hah[ch[u][1]] * pp[lsiz + 1],hah_rev[u] += hah_rev[ch[u][1]];
}

void recursive_maintain(int u){
    maintain(u);
    if(par[u] != -1) recursive_maintain(par[u]);
}

void pushdown(int u){
    if(flip[u]){
        swap(ch[u][0], ch[u][1]);
        flip[u] = 0;
        if(ch[u][0] != -1) flip[ch[u][0]] ^= 1,swap(hah[ch[u][0]],hah_rev[ch[u][0]]);
        if(ch[u][1] != -1) flip[ch[u][1]] ^= 1,swap(hah[ch[u][1]],hah_rev[ch[u][1]]);
    }
}

void recursive_pushdown(int u){
    if(par[u] != -1) recursive_pushdown(par[u]);
    pushdown(u);
}

void rotate(int u){
    int p = par[u],gp = par[p],d = (ch[p][0] == u)?0:1,gd;
    ch[p][d] = ch[u][d^1];if(ch[p][d] != -1) par[ch[p][d]] = p;
    ch[u][d^1] = p,par[p] = u,par[u] = gp;
    if(gp != -1) gd = (ch[gp][0] == p)?0:1,ch[gp][gd] = u;
    maintain(p),maintain(u);
    if(gp != -1) maintain(gp);
}

void splay(int u,int rt){
    recursive_pushdown(u);
    while (par[u] != rt) {
        int p = par[u],gp = par[p];
        if(gp == rt) rotate(u);
        else if ((ch[gp][0] == p) == (ch[p][0] == u)) rotate(p),rotate(u);
        else rotate(u),rotate(u);
    }
    recursive_maintain(u);
}

int kth(int u,int k){
    if(u == -1 || k <= 0 || k > siz[u]) return -1;
    pushdown(u);
    int lsiz = 0,rsiz = 0;
    if(ch[u][0] != -1) lsiz = siz[ch[u][0]];
    if(ch[u][1] != -1) rsiz = siz[ch[u][1]];
    if(k == lsiz + 1) return u;
    else if(k <= lsiz) return kth(ch[u][0],k);
    else return kth(ch[u][1],k - lsiz - 1);
}

int extract(int l,int r){
    int sub;
    if(l == 1 && r == n){
        return root;
    }else if(l == 1){
        int rt = kth(root, r+1);
        splay(rt, -1), root = rt;
        sub = ch[rt][0];
    }else if(r == n){
        int lt = kth(root, l-1);
        splay(lt, -1), root = lt;
        sub = ch[lt][1];
    }else{
        int lt = kth(root, l-1);
        splay(lt, -1), root = lt;
        int rt = kth(root, r+1);
        splay(rt, root);
        sub = ch[rt][0];
    }
    pushdown(sub);//ISSUE 2:SHOULD COMMIT PUSHDOWN HERE(otherwise you will meet such situ. that a reverse operation is comitted after the new node insterion,which is absolutely incorrect)
    return sub;
}

inline bool check(int a, int b, int len){
    return hah[extract(a, a+len-1)] == hah[extract(b, b+len-1)];
}
int getlcp(int a,int b){
    if(a > b) swap(a, b);
    int l = 1,r = n - b + 1,mid;
    while (l + 1 < r) {
        mid = l + (r-l)/2;
        if(check(a,b,mid)){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
    if(check(a,b,r)) return r;
    else if(check(a,b,l)) return l;
    else return 0;
}

void doflip(int l,int r){
    int sub = extract(l, r);
    flip[sub] ^= 1,swap(hah[sub],hah_rev[sub]);
    //ISSUE1: the hah and hah_rev 's reverse will affect the maintain,so you must makr sure when you commit a maintain,the reverse action is commited in its child nodes!
    //to resolve this situ. we assume the hah & hah_rev hav been reversed for the current node,when pushdown,its child node will be reversed,i.e,pushdown UPDATES the child node
}

void remove(int pos){
    int sub = extract(pos, pos);
    int p = par[sub],d = (ch[p][0] == sub)?0:1;
    ch[p][d] = par[sub] = -1;
    n--;
    recursive_maintain(p);
}

void append(int pos,int cha){
    if(pos == 0){
        int sub = kth(root, 1);
        init(++tot);
        chr[tot] = cha;
        par[tot] = sub;
        ch[sub][0] = tot;
        n++;
        recursive_maintain(tot);
        return;
    }
    int sub = extract(pos, pos);
    ch[sub][1] = ++tot;
    init(tot);
    chr[tot] = cha;
    par[tot] = sub;
    n++;
    recursive_maintain(tot);
}

char str[MAXN];
int build(int ll,int rr,int p){
    if (ll > rr) return -1;
    int cur = ++tot;
    int mid = (ll + rr) >> 1;
    init(cur);
    chr[cur] = str[mid-1];
    par[cur] = p;
    ch[cur][0] = build(ll, mid-1, cur);
    ch[cur][1] = build(mid+1, rr, cur);
    maintain(cur);
    return cur;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    srand(time(NULL));
    prepare(rand());
    while (scanf(" %d %d",&n,&m) != EOF) {
        scanf(" %s",str);
        tot = 0;
        root = 1;
        build(1,n,-1);
        for(int i = 1; i<= m; i++){
            int typ;
            scanf(" %d",&typ);
            if (typ == 1) {
                int p,c;
                scanf(" %d %d",&p,&c);
                append(p, c+'0');
            }else if(typ == 2){
                int p;
                scanf(" %d",&p);
                remove(p);
            }else if(typ == 3){
                int p1,p2;
                scanf(" %d %d",&p1,&p2);
                doflip(p1, p2);
            }else if(typ == 4){
                int p1,p2;
                scanf(" %d %d",&p1,&p2);
                printf("%d\n",getlcp(p1, p2));
            }
        }
        
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
