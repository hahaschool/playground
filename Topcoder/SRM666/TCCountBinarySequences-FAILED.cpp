//
//  TCCountBinarySequences.cpp
//  playground
//
//  Created by 張正昊 on 16/5/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

//WARNING! FAILED VERSION
//Severe time comsuption on extreme ("[[[[[]]]]]") case!

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
    bool vis[55];
    Matrix calcInterval(int s,int t,Matrix V){
        //cout << s << ' ' << t << endl;
        Matrix RET = V;int cur = s;
        for (int i = 0; i < seg.size(); i++) {
            if (!vis[i] && seg[i].l >= cur && seg[i].r <= t) {
                vis[i] = true;
                if (seg[i].l == s) {
                    RET = calcInterval(seg[i].l, seg[i].r, RET);
                }else{
                    Matrix Ea,Oa;Ea.zero(),Oa.zero();
                    RET = mul_mat(buildAp(seg[i].l - cur - 1), RET, 2*(K+1));
                    Matrix E,O;E.zero();O.zero();
                    bool Ef = false, Of = false;
                    for (int j = 0; j <= K; j++) {
                        E.mat[j][0] = RET.mat[j][0];
                        O.mat[j][0] = RET.mat[j+K+1][0];
                    }
                    if(Ef) Ea = calcInterval(seg[i].l, seg[i].r, mul_mat(buildAp(1), E, 2*(K+1)));
                    if(Of) Oa = calcInterval(seg[i].l, seg[i].r, mul_mat(buildAp(1), O, 2*(K+1)));
                    for (int j = 0; j <= K; j++) {
                        RET.mat[j][0] = Ea.mat[j][0];
                        RET.mat[j+1+K][0] = Oa.mat[j][0];
                    }
                }
                vis[i] = false;
                cur = seg[i].r;
            }
        }
        if (s == 0) {
            if (cur < N){
                RET = mul_mat(buildAp(N-cur), RET, 2*(K+1));
            }
            return RET;
        }
        if (cur < t){
            RET = mul_mat(buildAp(t-cur), RET, 2*(K+1));
        }
        for (int i = 0; i <= K; i++) {
            RET.mat[i+1+K][0] = 0;
        }
        return RET;
    }
    
    int countSequences(int n,int k,vector<int> L,vector<int> R){
        N = n,K = k;
        memset(vis, 0, sizeof(vis));
        seg.clear();seg.resize(L.size());
        for (int i = 0; i < L.size(); i++) {
            seg[i].l = L[i];
            seg[i].r = R[i];
        }
        sort(seg.begin(), seg.end());
        Matrix INIT;INIT.zero();INIT.mat[0][0] = 1;
        Matrix RES = calcInterval(0, N+1, INIT);
        LL ret = 0;
        for (int i = 0; i < 2*(K+1); i++) {
            ret = add_mod(ret, RES.mat[i][0]);
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
    //cout << solver.countSequences(4, 2, {2}, {3}) << endl;
    //cout << solver.countSequences(4, 1, {2}, {2}) << endl;
    //cout << solver.countSequences(4, 1, {1,1,1}, {4,4,4}) << endl;
    //cout << solver.countSequences(1000, 4, {10,101,201,110,121}, {100,200,300,120,130}) << endl;
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
