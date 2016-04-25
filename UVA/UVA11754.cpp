//
//  UVA11754.cpp
//  playground
//
//  Created by 張正昊 on 17/4/2016.
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

typedef long long LL;
const LL MAXN = 105,LIM = 10000;
struct Condition{
    LL k,x,y[MAXN];
    void arrange(){
        sort(y+1, y+1+k);
    }
    bool operator < (const Condition &b) const{
        return k*b.x < x*b.k;
    }
} cond[10];
LL C,S;

void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
    if(!b){
        d = a;
        x = 1;
        y = 0;
    }else{
        exgcd(b,a%b,d,y,x);
        y -= x*(a/b);
    }
}

LL CRT(LL n,LL *a,LL *m){
    LL M = 1,d,y,x = 0;
    for(int i = 1; i <= n; i++){
        M *= m[i];
    }
    for (int i = 1; i <= n; i++) {
        LL w = M / m[i];
        exgcd(m[i],w,d,d,y);
        x = (x + y*w*a[i]) % M;
    }
    return (x+M)%M;
}

set<LL> sol;
LL tma[10],tmm[10];
void dfs(int cur){
    if (cur == C+1) {
        sol.insert(CRT(C,tma,tmm));
    }else{
        for (int i = 1; i <= cond[cur].k; i++) {
            tma[cur] = cond[cur].y[i];
            tmm[cur] = cond[cur].x;
            dfs(cur+1);
        }
    }
}

void solve_CRT(){
    priority_queue<LL,vector<LL>,greater<LL> > que;
    sol.clear();
    dfs(1);
    LL MM = 1;
    for (int i = 1; i <= C; i++) {
        MM *= cond[i].x;
    }
    for (set<LL>::iterator it = sol.begin(); it != sol.end(); it++) {
        if (*it > 0) {
            que.push(*it);
        }else{
            que.push(MM);
        }
    }
    for(int i = 1; i <= S; i++){
        printf("%lld\n",que.top());
        LL tt = que.top();
        que.pop();
        que.push(tt + MM);
    }
}

set<LL> modst[10];
bool check(LL a){
    for (int i = 1; i <= C; i++) {
        if (!modst[i].count((a+cond[i].x)%cond[i].x)) {
            return false;
        }
    }
    return true;
}

void solve_brute(){
    for (int i = 1; i <= C; i++) {
        modst[i].clear();
        for (int j = 1; j <= cond[i].k; j++) {
            modst[i].insert(cond[i].y[j]);
        }
    }
    
    for (int i = 0; S; i++) {
        for (int j = 1; j <= cond[1].k; j++) {
            LL att = i*cond[1].x + cond[1].y[j];
            if (att == 0) {
                continue;
            }
            if (check(att)) {
                printf("%lld\n",att);
                if (--S == 0) {
                    break;
                }
            }
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %lld %lld",&C,&S) != EOF && C+S) {
        LL tot = 1;
        memset(cond, 0, sizeof(cond));
        for (int i = 1; i <= C; i++) {
            scanf(" %lld %lld",&cond[i].x,&cond[i].k);
            for (int j = 1; j <= cond[i].k; j++) {
                scanf(" %lld",&cond[i].y[j]);
            }
            cond[i].arrange();
            tot *= cond[i].k;
        }
        sort(cond+1,cond+1+C);
        if (tot > LIM) {
            solve_brute();
        }else{
            solve_CRT();
        }
        puts("");
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
