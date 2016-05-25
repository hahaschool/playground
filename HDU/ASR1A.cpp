////
////  ASR1A.cpp
////  playground
////
////  Created by 張正昊 on 21/5/2016.
////  Copyright © 2016 Adam Chang. All rights reserved.
////
//
//#include <stdio.h>
//#include <iostream>
//#include <algorithm>
//#include <queue>
//#include <vector>
//#include <cstdlib>
//#include <cstdio>
//#include <string>
//#include <cstring>
//#include <ctime>
//#include <iomanip>
//#include <cmath>
//#include <set>
//#include <stack>
//#include <cmath>
//#include <map>
//#include <complex>
//
//using namespace std;
//
//int x,k,c;
//long long m;
//const int MAXN = 3;
//struct Matrix{
//    int mat[MAXN][MAXN];
//    void zero(){
//        memset(mat, 0, sizeof(mat));
//    }
//    void identity(int siz){
//        zero();
//        for(int i = 0;i < siz; i++){
//            mat[i][i] = 1;
//        }
//    }
//};
//int mod(int a,int _m){
//    if(a < 0 || a >= _m) a %= _m;
//    if(a < 0) a += _m;
//    return a;
//}
//int mul_mod(int a,int b,int _m){
//    return mod(mod(a,_m)*mod(b,_m),_m);
//}
//int add_mod(int a,int b,int _m){
//    return mod(mod(a,_m)+mod(b,_m),_m);
//}
//Matrix mul_mat(Matrix A,Matrix B,int siz,int _m){
//    Matrix ret;ret.zero();
//    for (int k = 0;k < siz; k++) {
//        for(int i = 0; i < siz; i++){
//            for (int j = 0; j < siz; j++) {
//                ret.mat[i][j] = add_mod(ret.mat[i][j],mul_mod(A.mat[i][k], B.mat[k][j], _m),_m);
//            }
//        }
//    }
//    return ret;
//}
//Matrix pow_mat(Matrix A,long long p,int siz,int _m){
//    Matrix ret;ret.identity(siz);
//    Matrix fac = A;
//    while (p) {
//        if(p&1){
//            ret = mul_mat(ret, fac, siz, _m);
//        }
//        fac = mul_mat(fac, fac, siz, _m);
//        p >>= 1;
//    }
//    return ret;
//}
//
//void solve(){
//    Matrix A;A.zero();
//    A.mat[0][0] = mod(10, k),A.mat[0][1] = 1,A.mat[1][0] = 0,A.mat[1][1] = 1;
//    Matrix B;B.zero();
//    B.mat[0][0] = 0,B.mat[1][0] = mod(x, k);
//    A = pow_mat(A, m, 2, k);
//    B = mul_mat(A, B, 2, k);
//    if (mod(B.mat[0][0], k) == mod(c, k)) {
//        puts("Yes");
//    }else{
//        puts("No");
//    }
//}
//
//int main(){
//
//    int caseCnt;
//    scanf(" %d",&caseCnt);
//    for (int i = 1; i <= caseCnt; i++) {
//        printf("Case #%d:\n",i);
//        scanf(" %d %lld %d %d",&x,&m,&k,&c);
//        solve();
//    }
//    
//    
//    return 0;
//}
