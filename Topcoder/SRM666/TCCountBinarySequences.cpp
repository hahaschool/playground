//
//  TCCountBinarySequences.cpp
//  playground
//
//  Created by 張正昊 on 16/5/2016.
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


const int MAXSIZ = 15;
typedef long long LL;
const LL MODER = 1000000007;

struct Matrix{
    LL mat[MAXSIZ][MAXSIZ];
    void zero(){
        memset(mat, 0, sizeof(mat));
    }
    void identity(int siz){
        zero();
        for(int i = 0;i < siz;i++){
            mat[i][i] = 1;
        }
    }
};
LL mul_mod(LL a,LL b){
    if(a>=MODER) a%=MODER;
    if(b>=MODER) b%=MODER;
    LL ret = (a*b)%MODER;
    if(ret<0) ret+=MODER;
    return ret;
}
LL add_mod(LL a,LL b){
    if(a>=MODER) a%=MODER;
    if(b>=MODER) b%=MODER;
    LL ret = (a+b)%MODER;
    if(ret<0) ret+=MODER;
    return ret;
    
}
Matrix mul_mat(Matrix A,Matrix B,int siz){
    Matrix C;C.zero();
    for (int k = 0; k < siz; k++) {
        for(int i = 0; i < siz; i++){
            for (int j = 0; j < siz; j++) {
                C.mat[i][j] = add_mod(C.mat[i][j], mul_mod(A.mat[i][k], B.mat[k][j]));
            }
        }
    }
    return C;
}
Matrix pow_mat(Matrix A,LL p,int siz){
    Matrix C;C.identity(siz);
    while (p) {
        if(p&1) C = mul_mat(A, C, siz);
        A = mul_mat(A, A, siz);
        p >>= 1;
    }
    return C;
}
Matrix add_mat(Matrix A,Matrix B,int siz){
    Matrix C;C.zero();
    for (int i = 0; i < siz; i++) {
        for (int j = 0; j < siz; j++) {
            C.mat[i][j] = add_mod(A.mat[i][j], B.mat[i][j]);
        }
    }
    return C;
}

class CountBinarySequences{
public:
    struct Segment{
        int l,r;
        bool operator < (const Segment &b) const{
            if(l != b.l) return l < b.l;
            return r > b.r;
        }
    };
    vector<Segment> seg;
    int N,K;
    
    Matrix buildAp(int p){
        Matrix A; A.zero();
        if (p<=0) {
            A.identity(2*(K+1));
            return A;
        }
        for (int i = 0; i <= K; i++) {
            A.mat[0][i] = 1;
            A.mat[K+1][K+1+i] = 1;
        }
        for (int i = 1; i <= K; i++) {
            A.mat[i][K+i] = 1;
            A.mat[K+1+i][i-1] = 1;
        }
        A = pow_mat(A, p, (K+1)*2);
        return A;
    }
    Matrix E,O,D;
    void prepare(){
        //E矩阵用于提取偶数部分向量
        E.zero();
        for (int i = 0; i <= K; i++) {
            E.mat[i][i] = 1;
        }
        //O矩阵用于提取并提升奇数部分向量
        O.zero();
        for (int i = 0; i <= K; i++) {
            O.mat[i][i+K+1] = 1;
        }
        //D矩阵用于下沉奇数部分向量
        D.zero();
        for (int i = 0; i <= K; i++) {
            D.mat[i+K+1][i] = 1;
        }
    }
    
    bool vis[55];
    map<pair<int, int>, Matrix> mp;
    Matrix calcInterval(int s,int t){
        int cur = s;
        Matrix RET;RET.identity(2*(K+1));
        if(mp.count(make_pair(s, t))) return mp[make_pair(s, t)];
        for (int i = 0; i < seg.size(); i++) {
            if (!vis[i] && seg[i].l >= cur && seg[i].r <= t) {
                vis[i] = true;
                if (seg[i].l == s) {
                    RET = mul_mat(calcInterval(seg[i].l, seg[i].r), RET, 2*(K+1));
                }else{
                    RET = mul_mat(buildAp(seg[i].l - cur - 1), RET, 2*(K+1));
                    cur = seg[i].l-1;
                    Matrix EE = mul_mat(E, RET, 2*(K+1));
                    Matrix OO = mul_mat(O, RET, 2*(K+1));
                    EE = mul_mat(buildAp(1), EE, 2*(K+1));
                    OO = mul_mat(buildAp(1), OO, 2*(K+1));
                    EE = mul_mat(calcInterval(seg[i].l, seg[i].r), EE, 2*(K+1));
                    OO = mul_mat(calcInterval(seg[i].l, seg[i].r), OO, 2*(K+1));
                    OO = mul_mat(D, OO, 2*(K+1));
                    RET = add_mat(EE, OO, 2*(K+1));
                }
                vis[i] = false;
                cur = seg[i].r;
            }
        }
        if(s == 0){
            if(cur < t){
                RET = mul_mat(buildAp(N-cur), RET, 2*(K+1));
            }
            return RET;
        }
        if(cur < t){
            RET = mul_mat(buildAp(t-cur), RET, 2*(K+1));
        }
        RET = mul_mat(E, RET, 2*(K+1));
        mp[make_pair(s, t)] = RET;
        return RET;
    }
    int countSequences(int n,int k,vector<int> L,vector<int> R){
        N = n,K = k;
        prepare();
        memset(vis, 0, sizeof(vis));
        seg.clear();seg.resize(L.size());
        for (int i = 0; i < L.size(); i++) {
            seg[i].l = L[i];
            seg[i].r = R[i];
        }
        sort(seg.begin(), seg.end());
        Matrix RES;RES.zero();RES.mat[0][0] = 1;
        RES = mul_mat(calcInterval(0, N+1), RES, 2*(K+1));
        LL ret = 0;
        for (int i = 0; i < 2*(K+1); i++) {
            ret = add_mod(ret,RES.mat[i][0]);
        }
        return ret;
    }
};

CountBinarySequences solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.countSequences(4, 2, {2}, {3}) << endl;
    cout << solver.countSequences(4, 1, {2}, {2}) << endl;
    cout << solver.countSequences(4, 1, {1,1,1}, {4,4,4}) << endl;
    cout << solver.countSequences(1000, 4, {10,101,201,110,121}, {100,200,300,120,130}) << endl;
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
