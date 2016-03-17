//
//  UVA11992.cpp
//  playground
//
//  Created by 張正昊 on 17/3/2016.
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
const int MAXN = 2000006,INF = 0x3f3f3f3f;
struct segmentTree{
    static const int MAXN = 2000006,INF = 0x3f3f3f3f;
#define LCH(x) (x << 1)
#define RCH(x) ((x << 1) + 1)
#define PAR(x) (x >> 1)
    int n;
    int pool_max[MAXN];
    int pool_min[MAXN];
    int pool_sum[MAXN];
    int lazy_add[MAXN];
    int lazy_set[MAXN];
    void build(int *seq,int cl = -1, int cr = -1, int cur = -1){
        if(cur == -1){
            build(seq, 1, n, 1);
            return ;
        }
        lazy_add[cur] = 0;
        lazy_set[cur] = -1;
        if(cl == cr){
            pool_max[cur] = pool_min[cur] = pool_sum[cur] = seq[cl];
            return;
        }
        int mid = (cl + cr) >> 1;
        build(seq, cl, mid, LCH(cur));
        build(seq, mid+1, cr, RCH(cur));
        pool_max[cur] = max(pool_max[LCH(cur)],pool_max[RCH(cur)]);
        pool_min[cur] = min(pool_min[LCH(cur)],pool_min[RCH(cur)]);
        pool_sum[cur] = pool_sum[LCH(cur)] + pool_sum[RCH(cur)];
    }
    void add(int delta,int l,int r,int cl = -1,int cr = -1,int cur = -1){
        if(cur == -1){
            add(delta, l, r, 1, n, 1);
            return;
        }
        pushdown(cl, cr, cur);
        if(cl >= l && cr <= r){
            lazy_add[cur] += delta;
            pushdown(cl, cr, cur);
            return;
        }
        if(cr < l || cl > r){
            return;
        }else{
            int mid = (cl + cr) >> 1;
            add(delta, l, r, cl, mid, LCH(cur));
            add(delta, l, r, mid+1, cr, RCH(cur));
            pool_max[cur] = max(pool_max[LCH(cur)],pool_max[RCH(cur)]);
            pool_min[cur] = min(pool_min[LCH(cur)],pool_min[RCH(cur)]);
            pool_sum[cur] = pool_sum[LCH(cur)] + pool_sum[RCH(cur)];
        }
    }
    void set(int val,int l,int r,int cl = -1,int cr = -1,int cur = -1){
        if(cur == -1){
            set(val, l, r, 1, n, 1);
            return;
        }
        pushdown(cl, cr, cur);
        if(cl >= l && cr <= r){
            lazy_set[cur] = val;
            if(lazy_add[cur]){
                lazy_add[cur] = 0;
            }
            pushdown(cl, cr, cur);
            return;
        }
        if(cr < l | cl > r){
            return;
        }else{
            int mid = (cl + cr) >> 1;
            set(val, l, r, cl, mid, LCH(cur));
            set(val, l, r, mid+1, cr, RCH(cur));
            pool_max[cur] = max(pool_max[LCH(cur)],pool_max[RCH(cur)]);
            pool_min[cur] = min(pool_min[LCH(cur)],pool_min[RCH(cur)]);
            pool_sum[cur] = pool_sum[LCH(cur)] + pool_sum[RCH(cur)];
        }
    }
    void pushdown(int cl,int cr,int cur){
        int siz = cr - cl + 1;
        if(lazy_set[cur] >= 0){
            pool_max[cur] = pool_min[cur] = lazy_set[cur];
            pool_sum[cur] = siz * lazy_set[cur];
            if(cl < cr)
                lazy_set[LCH(cur)] = lazy_set[RCH(cur)] = lazy_set[cur],lazy_add[LCH(cur)] = lazy_add[RCH(cur)] = 0;
            lazy_set[cur] = -1;
        }
        if(lazy_add[cur]){
            pool_max[cur] += lazy_add[cur];
            pool_min[cur] += lazy_add[cur];
            pool_sum[cur] += siz * lazy_add[cur];
            if(cl < cr)
                lazy_add[LCH(cur)] += lazy_add[cur], lazy_add[RCH(cur)] += lazy_add[cur];
            lazy_add[cur] = 0;
        }
    }
    void query(int l,int r,int &res_sum,int &res_min,int &res_max,int cl = -1,int cr = -1,int cur = -1){
        if(cur == -1){
            query(l, r, res_sum, res_min, res_max, 1, n, 1);
            return;
        }
        pushdown(cl, cr, cur);
        
        if(cl >= l && cr <= r){
            res_max = max(res_max,pool_max[cur]);
            res_min = min(res_min,pool_min[cur]);
            res_sum += pool_sum[cur];
            return;
        }
        if(cr < l || cl > r){
            return;
        }else{
            int mid = (cl + cr) >> 1;
            int lmax = 0,lmin = INF,lsum = 0,rmax = 0,rmin = INF,rsum = 0;
            query(l, r, lsum, lmin, lmax, cl, mid, LCH(cur));
            query(l, r, rsum, rmin, rmax, mid+1, cr, RCH(cur));
            res_sum += lsum + rsum;
            res_max = max(res_max,max(lmax,rmax));
            res_min = min(res_min,min(lmin,rmin));
        }
    }
} seg[22];

int R,C,M;
int NIL[1000006];

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d %d %d",&R,&C,&M) != EOF) {
        for (int i = 1; i <= R; i++) {
            seg[i].n = C;
            seg[i].build(NIL);
        }
        for (int i = 1; i <= M; i++) {
            int typ;
            scanf(" %d",&typ);
            if(typ == 1){
                int a,b,c,d,e;
                scanf(" %d %d %d %d %d",&a,&b,&c,&d,&e);
                for (int i = a; i <= c; i++) {
                    seg[i].add(e, b, d);
                }
            }else if(typ == 2){
                int a,b,c,d,e;
                scanf(" %d %d %d %d %d",&a,&b,&c,&d,&e);
                for (int i = a; i <= c; i++) {
                    seg[i].set(e, b, d);
                }
            }else if(typ == 3){
                int a,b,c,d;
                scanf(" %d %d %d %d",&a,&b,&c,&d);
                int res_sum = 0,res_min = INF,res_max = 0;
                for (int i = a; i <= c; i++) {
                    seg[i].query(b, d, res_sum, res_min, res_max);
                }
                printf("%d %d %d\n",res_sum,res_min,res_max);
            }
        }
    }
    
    return 0;
}
