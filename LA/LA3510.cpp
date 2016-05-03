//
//  LA3510.cpp
//  playground
//
//  Created by 張正昊 on 26/4/2016.
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

const int MAXN = 1066;

int n;
inline void getpos(int val,int &x,int &y){
    y = val/n;
    x = val%n;
}
inline int makepos(int y,int x){
    return y*n+x;
}


int A[MAXN][MAXN],B[MAXN][MAXN];

void commit(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = B[i][j];
        }
    }
}

void rot(int w){
    for (int i = 0,sj = (w>0)?n-1:0; i < n; i++,sj+=(w>0)?-1:1) {
        for(int j = 0,si = (w>0)?0:n-1; j < n; j++,si+=(w>0)?1:-1){
            B[i][j] = A[si][sj];
        }
    }
    commit();
}

void sym(){
    for(int i = 0; i < n; i++){
        for(int j = 0,sj = n-1; j < n; j++,sj--){
            B[i][j] = A[i][sj];
        }
    }
    commit();
}

void bhsym(){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = (i>=n/2)?A[i][n-1-j]:A[i][j];
        }
    }
    commit();
}

void bvsym(){
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[i][j];
        }
    }
    for (int i = n/2,si = n-1; i < n; i++,si--) {
        for(int j = 0; j < n; j++){
            B[i][j] = A[si][j];
        }
    }
    commit();
}

void div(int w){
    if(w > 0){
        int ti0 = 0,ti1 = n/2;
        for (int i = 0; i < n; i++) {
            int &ti = (i&1)?ti1:ti0;
            for (int j = 0; j < n; j++) {
                B[ti][j] = A[i][j];
            }
            ti++;
        }
    }else{
        for (int i = 0,ti = 0; i < n/2; i++,ti += 2) {
            for (int j = 0; j < n; j++) {
                B[ti][j] = A[i][j];
            }
        }
        for (int i = n/2,ti = 1; i < n; i++,ti += 2) {
            for (int j = 0; j < n; j++) {
                B[ti][j] = A[i][j];
            }
        }
    }
    commit();
}

void mix(int w){
    if (w > 0){
        for (int i = 0; i < n; i++) {
            if (i&1) {
                for (int j = n/2,tj = 0; j < n; j++,tj += 2) {
                    B[i][tj] = A[i-1][j];
                    B[i][tj+1] = A[i][j];
                }
            }else{
                for (int j = 0,tj = 0; j < n/2; j++,tj += 2) {
                    B[i][tj] = A[i][j];
                    B[i][tj+1] = A[i+1][j];
                }
            }
        }
    }else{
        for (int i = 0; i < n; i++) {
            if (i&1) {
                for(int j = 0,sj = n/2; j < n; j+=2,sj++){
                    B[i-1][sj] = A[i][j];
                    B[i][sj] = A[i][j+1];
                }
            }else{
                for(int j = 0,sj = 0; j < n; j+=2,sj++){
                    B[i][sj] = A[i][j];
                    B[i+1][sj] = A[i][j+1];
                }
            }
        }
    }
    commit();
}



void print(){
    for(int i = 0; i< n;i++){
        for(int j = 0;j < n; j++){
            printf("%d\t",A[i][j]);
        }
        puts("");
    }
}


long long gcd(long long a,long long b){
    if (!b) {
        return a;
    }
    return gcd(b,a%b);
}

long long lcm(long long a,long long b){
    return a*b/gcd(a, b);
}

bool vis[MAXN*MAXN];

void solve(){
    for (int i = 0; i < n*n; i++) {
        vis[i] = false;
    }
    long long res = 1;
    for (int i = 0; i < n*n; i++) {
        int cur = i;
        long long len = 0;
        while (!vis[cur]) {
            vis[cur] = true;
            len++;
            int xx,yy;
            getpos(cur, xx, yy);
            cur = A[yy][xx];
        }
        if(len) res = lcm(res,len);
    }
    printf("%lld\n",res);
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 0;d < caseCnt; d++){
        if(d) puts("");
        scanf(" %d",&n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                A[i][j] = makepos(i,j);
            }
        }
        string cmd;
        stack<string> stk;
        while (cin.peek() != EOF && !isdigit(cin.peek())) {
            cin >> cmd;
            stk.push(cmd);
            while (cin.peek() == '\n' || cin.peek() == ' ') {
                cin.get();
            }
        }
        while (!stk.empty()) {
            cmd = stk.top();
            stk.pop();
            switch (cmd[0]) {
                case 'r':
                    if (cmd.size() == 4) rot(-1);
                    else rot(1);
                    break;
                case 's':
                    sym();
                    break;
                case 'b':
                    if (cmd[1] == 'h') {
                        bhsym();
                    }else{
                        bvsym();
                    }
                    break;
                case 'd':
                    if(cmd.size() == 4) div(-1);
                    else div(1);
                    break;
                case 'm':
                    if(cmd.size() == 4) mix(-1);
                    else mix(1);
                    break;
                default:
                    break;
            }
        }
        solve();
    }
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
