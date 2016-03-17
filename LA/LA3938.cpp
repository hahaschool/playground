//
//  LA3938.cpp
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

const long long MAXN = 2000005;
long long segTree[MAXN][3];//Prefix 0 Suffix 1 Segment 2
long long posTree[MAXN][3][2];
#define LCH(x) (x << 1)
#define RCH(x) ((x << 1) + 1)
#define PAR(x) (x >> 1)
long long n,m;
long long seq[MAXN/2];
long long sum[MAXN/2];

long long query_sum(long long l,long long r){
    return sum[r] - sum[l-1];
}

struct State{
    long long val,ff,tt;
    bool operator < (const State &b)const{
        if(val != b.val) return val > b.val;
        if(ff != b.ff) return ff < b.ff;
        return tt < b.tt;
    }
};

void build(long long cl = -1,long long cr = -1,long long cur = -1){
    if (cur == -1) {
        for (long long i = 1; i <= n; i++) {
            sum[i] = seq[i] + sum[i-1];
        }
        build(1,n,1);
        return;
    }
    if (cl == cr) {
        segTree[cur][0] = segTree[cur][1] = segTree[cur][2] = seq[cl];
        posTree[cur][0][0] = posTree[cur][0][1] = posTree[cur][1][0] = posTree[cur][1][1] = posTree[cur][2][0] = posTree[cur][2][1] =cl;
        return;
    }
    long long mid = (cl + cr) >> 1;
    build(cl,mid,LCH(cur));
    build(mid+1,cr,RCH(cur));
    State tmp1[2] = {{segTree[LCH(cur)][0],cl,posTree[LCH(cur)][0][1]},{query_sum(cl , mid) + segTree[RCH(cur)][0],cl,posTree[RCH(cur)][0][1]}};
    sort(tmp1,tmp1+2);
    segTree[cur][0] = tmp1[0].val,posTree[cur][0][0] = tmp1[0].ff,posTree[cur][0][1] = tmp1[0].tt;
    State tmp2[2] = {{segTree[RCH(cur)][1],posTree[RCH(cur)][1][0],cr},{segTree[LCH(cur)][1] + query_sum(mid+1 , cr),posTree[LCH(cur)][1][0],cr}};
    sort(tmp2,tmp2+2);
    segTree[cur][1] = tmp2[0].val,posTree[cur][1][0] = tmp2[0].ff,posTree[cur][1][1] = tmp2[0].tt;
    State tmp3[3] = {{segTree[LCH(cur)][2],posTree[LCH(cur)][2][0],posTree[LCH(cur)][2][1]},{segTree[RCH(cur)][2],posTree[RCH(cur)][2][0],posTree[RCH(cur)][2][1]},{segTree[LCH(cur)][1] + segTree[RCH(cur)][0],posTree[LCH(cur)][1][0],posTree[RCH(cur)][0][1]}};
    sort(tmp3,tmp3+3);
    segTree[cur][2] = tmp3[0].val,posTree[cur][2][0] = tmp3[0].ff,posTree[cur][2][1] = tmp3[0].tt;
}

long long query_sfx(long long l,long long r,long long &ff,long long cl = -1,long long cr = -1,long long cur = -1){
    long long mid = (cl + cr) >> 1;
    if (cl == l && cr == r) {
        ff = posTree[cur][1][0];
        return segTree[cur][1];
    }
    if (mid < l) {
        return query_sfx(l,r,ff,mid + 1,cr,RCH(cur));
    }else if(mid >= r){
        return query_sfx(l,r,ff,cl,mid,LCH(cur));
    }else{
        long long lt,rt,lff,rff;
        lt = query_sfx(l, mid,lff,cl,mid,LCH(cur));
        rt = query_sfx(mid+1,r,rff,mid+1,cr,RCH(cur));
        lt += query_sum(mid+1, cr);
        if (lt > rt) {
            ff = lff;
        }else if(rt > lt){
            ff = rff;
        }else{
            ff = min(lff,rff);
        }//ISSUE:当lt 等于 rt 时，要注意选更小的那个ff
        return max(lt, rt);
    }
}

long long query_pfx(long long l,long long r,long long &tt,long long cl = -1,long long cr = -1,long long cur = -1){
    long long mid = (cl + cr) >> 1;
    if (cl == l && cr == r) {
        tt = posTree[cur][0][1];
        return segTree[cur][0];
    }
    if (mid < l) {
        return query_pfx(l,r,tt,mid + 1,cr,RCH(cur));
    }else if(mid >= r){
        return query_pfx(l,r,tt,cl,mid,LCH(cur));
    }else{
        long long lt,rt,ltt,rtt;
        lt = query_pfx(l, mid,ltt,cl,mid,LCH(cur));
        rt = query_pfx(mid+1,r,rtt,mid+1,cr,RCH(cur));
        rt += query_sum(cl, mid);
        if (lt > rt) {
            tt = ltt;
        }else if(rt > lt){
            tt = rtt;
        }else{
            tt = min(ltt,rtt);
        }//ISSUE:当lt 等于 rt 时，要注意选更小的那个tt
        return max(lt, rt);
    }
}



long long query(long long l,long long r,long long &ff,long long &tt,long long cl = -1,long long cr = -1,long long cur = -1){
    if (cur == -1) {
        return query(l,r,ff,tt,1,n,1);
    }
    long long mid = (cl + cr) >> 1;
    if (cl == l && cr == r) {
        ff = posTree[cur][2][0],tt = posTree[cur][2][1];
        return segTree[cur][2];
    }
    if (mid < l) {
        return query(l,r,ff,tt,mid + 1,cr,RCH(cur));
    }else if(mid >= r){
        return query(l,r,ff,tt,cl,mid,LCH(cur));
    }else{
        long long lt,rt,md,lff,rff,ltt,rtt,mff,mtt;
        lt = query(l,mid,lff,ltt,cl,mid,LCH(cur));
        rt = query(mid+1,r,rff,rtt,mid+1,cr,RCH(cur));
        md = query_sfx(l, mid,mff,cl,mid,LCH(cur)) + query_pfx(mid+1, r,mtt,mid+1,cr,RCH(cur));
        State tmp[3] = {{lt,lff,ltt},{rt,rff,rtt},{md,mff,mtt}};
        sort(tmp,tmp+3);
        ff = tmp[0].ff,tt = tmp[0].tt;
        return tmp[0].val;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    long long caseCnt = 0;
    while (scanf(" %lld %lld",&n,&m) != EOF) {
        printf("Case %lld:\n",++caseCnt);
        for (long long i = 1; i <= n; i++) {
            scanf(" %lld",&seq[i]);
        }
        memset(segTree, 0, sizeof(segTree));
        build();
        for (long long i = 1; i <= m; i++) {
            long long l,r;
            long long resf = -1,rest = -1;
            scanf(" %lld %lld",&l,&r);
            query(l,r,resf, rest);
            printf("%lld %lld\n",resf,rest);
            //printf("%d %d | %d %d %d\n",l,r,tmp,resf,rest);
        }
    }
    return 0;
}
