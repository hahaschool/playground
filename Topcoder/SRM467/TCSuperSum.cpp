//
//  TCSuperSum.cpp
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

class SuperSum{
public:
    long long mul_mod(long long a,long long b,long long m){
        long long ret = a*b%m;
        if(ret < 0) ret += m;
        return ret;
    }
    long long pow_mod(long long a,long long p,long long m){
        long long fac = a;
        long long ret = 1;
        while (p) {
            if(p&1){
                ret = mul_mod(ret, fac, m);
            }
            fac = mul_mod(fac, fac, m);
            p >>= 1;
        }
        return ret;
    }
    long long inv_mod(long long a,long long m){
        return pow_mod(a, m-2, m);
    }
    long long inv2;
    static const long long MODER = 1000000007;
    SuperSum(){
        inv2 = inv_mod(2, MODER);
    }
    long long factorial(int a){
        long long ret = 1;
        for (int i = 2; i <= a; i++) {
            ret = mul_mod(ret, i, MODER);
        }
        return ret;
    }
    long long C(int n,int k){
        long long ret = 1;
        long long mul = n;
        for (int i = 1; i <= k; i++) {
            ret = mul_mod(ret, mul, MODER);
            mul--;
        }
        ret = mul_mod(ret, inv_mod(factorial(k), MODER), MODER);
        return ret;
    }
    int calculate(int k,int n){
        return C(n+k,k+1);
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    int k,n;
    SuperSum solver;
    while (cin >> k >> n) {
        cout << solver.calculate(k, n) << endl;
    }
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
