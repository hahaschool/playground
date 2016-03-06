//
//  LA5821.cpp
//  playground
//
//  Created by 張正昊 on 5/3/2016.
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

//OFFLINE VERSION
//const int MAXN = 15,MAXQ = 15,INF = 0x6fffffff;
const int MAXN = 100005,MAXQ = 50005;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int xsq[MAXN*2],ysq[MAXN*2],xtot,ytot;
map<int,int> xmp,ymp;
set<int> xst,yst;

struct Point{
    int x,y;
    bool operator < (const Point &b)const{
        if(x != b.x) return x > b.x;
        return y > b.y;
    }
} pt[MAXN];

struct Query{
    int x,y,id;
    long long res;
    bool operator < (const Query &b) const{
        if (x != b.x) return x > b.x;
        return y > b.y;
    }
} qq[MAXQ];
bool query_cmp(const Query &a,const Query &b){
    return a.id < b.id;
}
int n,q;

struct SEGTREE{
    long long segTree[MAXN*10];
#define LCH(a) (a << 1)
#define RCH(a) ((a << 1) + 1)
#define PAR(a) (a >> 1)
    void segTree_build(long long fill,int n,int cl = -1,int cr = -1,int cur = -1){
        if(cl == -1){
            segTree_build(fill,n,1,n,1);
            return;
        }
        segTree[cur] = fill;
        if(cl == cr){
            return;
        }
        int mid = (cl+cr) >> 1;
        segTree_build(fill, n,cl,mid,LCH(cur));
        segTree_build(fill, n,mid+1,cr,RCH(cur));
    }
    void segTree_insert(int pos,long long val,int n,int cl = -1,int cr = -1,int cur = -1){
        if (cl == -1) {
            segTree_insert(pos,val,n,1,n,1);
            return;
        }
        if (cl == cr && cl == pos) {
            segTree[cur] = min(val,segTree[cur]);
            return;
        }
        int mid = (cl + cr) >> 1;
        if (pos <= mid) {
            segTree_insert(pos, val, n,cl,mid,LCH(cur));
        }else{
            segTree_insert(pos, val, n,mid+1,cr,RCH(cur));
        }
        segTree[cur] = min(segTree[LCH(cur)],segTree[RCH(cur)]);
    }
    long long segTree_qres;
    void segTree_query(int l,int r,int n,int cl = -1,int cr = -1,int cur = -1){
        if (cl == -1) {
            segTree_query(l,r,n,1,n,1);
            return;
        }
        if(cl >= l && cr <= r){
            segTree_qres = min(segTree_qres,segTree[cur]);
            return;
        }
        if(cl > r || cr < l){
            return;
        }
        int mid = (cl+cr)>>1;
        segTree_query(l, r, n,cl,mid,LCH(cur));
        segTree_query(l, r, n,mid+1,cr,RCH(cur));
    }
} tree[2];

void solve(){
    tree[0].segTree_build(INF, ytot);
    tree[1].segTree_build(INF, ytot);
    int inscur = 1;
    for (int i = 1; i <= q; i++) {
        while (inscur <= n && pt[inscur].x >= qq[i].x) {
            tree[0].segTree_insert(ymp[pt[inscur].y], + pt[inscur].y + pt[inscur].x,ytot);
            tree[1].segTree_insert(ymp[pt[inscur].y], - pt[inscur].y + pt[inscur].x,ytot);
            inscur++;
        }
        tree[0].segTree_qres = INF;
        tree[0].segTree_query(ymp[qq[i].y], ytot, ytot);
        qq[i].res = min(qq[i].res, - qq[i].x - qq[i].y + tree[0].segTree_qres);
        tree[1].segTree_qres = INF;
        tree[1].segTree_query(1, ymp[qq[i].y], ytot);
        qq[i].res = min(qq[i].res, - qq[i].x + qq[i].y + tree[1].segTree_qres);
    }
    
    inscur = n;
    tree[0].segTree_build(INF, ytot);
    tree[1].segTree_build(INF, ytot);
    for(int i = q; i >= 1; i--){
        while (inscur >= 1 && pt[inscur].x <= qq[i].x) {
            tree[0].segTree_insert(ymp[pt[inscur].y], + pt[inscur].y - pt[inscur].x,ytot);
            tree[1].segTree_insert(ymp[pt[inscur].y], - pt[inscur].y - pt[inscur].x,ytot);
            inscur--;
        }
        tree[0].segTree_qres = INF;
        tree[0].segTree_query(ymp[qq[i].y], ytot, ytot);
        qq[i].res = min(qq[i].res,qq[i].x - qq[i].y+tree[0].segTree_qres);
        tree[1].segTree_qres = INF;
        tree[1].segTree_query(1,ymp[qq[i].y], ytot);
        qq[i].res = min(qq[i].res, qq[i].x + qq[i].y+tree[1].segTree_qres);
    }
    
    sort(qq+1, qq+1+q, query_cmp);
    for(int i = 1; i<= q; i++){
        printf("%lld\n",qq[i].res);
    }
}


int main(){
    int caseCnt = 0;
    while (scanf(" %d",&n) != EOF && n != -1) {
        if (caseCnt++) {
            puts("");
        }
        xst.clear(),yst.clear(),xmp.clear(),ymp.clear();
        for(int i = 1; i<= n; i++){
            scanf(" %d %d",&pt[i].x,&pt[i].y);
            xst.insert(pt[i].x),yst.insert(pt[i].y);
        }
        scanf(" %d",&q);
        for(int i = 1; i <= q; i++){
            scanf(" %d %d",&qq[i].x,&qq[i].y);
            qq[i].id = i;
            xst.insert(qq[i].x),yst.insert(qq[i].y);
            qq[i].res = INF;
        }
        xtot = ytot = 0;
        for(set<int>::iterator it = xst.begin();it != xst.end();it++)
            xsq[++xtot] = *it,xmp[*it] = xtot;
        for(set<int>::iterator it = yst.begin();it != yst.end();it++)
            ysq[++ytot] = *it,ymp[*it] = ytot;
        sort(pt+1, pt+1+n);
        sort(qq+1, qq+1+q);
        solve();
    }
    
    
    return 0;
}
