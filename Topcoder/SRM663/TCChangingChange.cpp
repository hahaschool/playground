//
//  TCChangingChange.cpp
//  playground
//
//  Created by 張正昊 on 13/5/2016.
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

class ChangingChange{
public:
    vector<int> W;
    typedef long long LL;
    static const LL MODER = 1000000007;
    LL mul_mod(LL a,LL b){
        LL ret = (a*b)%MODER;
        if(ret<0) ret+=MODER;
        return ret;
    }
    LL pow_mod(LL a,LL p){
        LL ret = 1,fac = a;
        while(p){
            if(p&1) ret = mul_mod(ret, fac);
            fac = mul_mod(fac,fac);
            p >>= 1;
        }
        return ret;
    }
    LL inv_mod(LL a){
        return pow_mod(a, MODER-2);
    }
    
    static const int MAXN = 1005005;
    //ISSUE:注意预处理阶乘要到1000000+5000 因为组合数的n为r+k-1，高达r+N，即100W+2000
    LL factorial[MAXN],factorial_inv[MAXN];
    void prepare(){
        //预处理阶乘和阶乘逆元
        factorial[0] = 1;
        for(int i = 1;i < MAXN; i++){
            factorial[i] = mul_mod(factorial[i-1], i);
        }
        factorial_inv[MAXN-1] = inv_mod(factorial[MAXN-1]);
        for (int i = MAXN-2; i >= 0; i--) {
            factorial_inv[i] = mul_mod(i+1, factorial_inv[i+1]);
        }
    }
    LL C(LL n,LL k){
        if(k>n) return 0;
        return mul_mod(factorial[n],mul_mod(factorial_inv[k],factorial_inv[n-k]));
    }
    LL D(LL r,LL k){
        return mul_mod(C(r+k-1,k),(k&1)?-1:1);
    }
    int N;
    int query(int v,int r){
        LL ret = 0;
        for (int i = 0,di = 0; i <= N; i += v,di++) {
            ret += mul_mod(W[N-i], D(r,di));
            ret %= MODER;
        }
        if(ret < 0) ret += MODER;
        return ret;
    }
    
    ChangingChange(){
        prepare();
    }
    
    vector<int> countWays(vector<int> ways,vector<int> valueRemoved,vector<int> numRemoved){
        W = ways,N = W.size()-1;
        vector<int> ret;ret.resize(valueRemoved.size());
        for(int i = 0; i < valueRemoved.size(); i++){
            ret[i] = query(valueRemoved[i], numRemoved[i]);
        }
        return ret;
    }
} solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int n,t;
    vector<int> a,b,c;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> t;
        a.push_back(t);
    }
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> t;
        b.push_back(t);
    }
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> t;
        c.push_back(t);
    }
    vector<int> d = solver.countWays(a, b, c);
    for(int i = 0;i < d.size(); i++){
        cout << d[i] << endl;
    }
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
