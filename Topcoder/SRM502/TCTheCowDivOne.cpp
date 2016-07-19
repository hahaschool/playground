//
//  TCTheCowDivOne.cpp
//  playground
//
//  Created by 張正昊 on 18/7/2016.
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

class TheCowDivOne{
public:
    typedef long long LL;
    LL N,K;
    static const LL MODER = 1000000007;
    LL get_mod(LL a){
        if(a < 0 || a >= MODER) a %= MODER;
        if(a < 0) a += MODER;
        return a;
    }
    LL mul_mod(LL a,LL b){
        return get_mod(get_mod(a) * get_mod(b));
    }
    LL sum_mod(LL a,LL b){
        return get_mod(get_mod(a) + get_mod(b));
    }
    LL pow_mod(LL a,LL p){
        LL ret = 1;
        while (p) {
            if(p&1) ret = mul_mod(a, ret);
            a = mul_mod(a, a);
            p >>= 1;
        }
        return ret;
    }
    LL inv_mod(LL a){
        return pow_mod(a, MODER-2);
    }
    LL fac_mod(int n){
        LL ret = 1;
        for (LL i = 1; i <= n; i++) {
            ret = mul_mod(i, ret);
        }
        return ret;
    }
    
    map<vector<LL>,LL> mp;
    LL F(LL d,LL k,LL a){
        if(k == 0) return 1;
        if(mp.count({d,k,a})) return mp[{d,k,a}];
        if(a == 1 && __gcd(d,k) != d) return mp[{d,k,a}] = mul_mod(F(__gcd(d,k),k,1), inv_mod(mul_mod(d, inv_mod(__gcd(d,k)))));
        LL g = __gcd(a,d);
        return mp[{d,k,a}] = sum_mod(mul_mod(F(g,k-1,1), mul_mod(g, N/d)),-mul_mod(F(d,k-1,(a+1)%d),(k-1)));
    }
    int find(int _N,int _K){
        N = _N;
        K = _K;
        mp.clear();
        return mul_mod(F(N,K,1),inv_mod(fac_mod(K)));
    }
};

TheCowDivOne solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.find(7, 4) << endl;
    cout << solver.find(1, 1) << endl;
    cout << solver.find(58, 4) << endl;
    cout << solver.find(1000, 47) << endl;
    cout << solver.find(1000000000, 1000) << endl;
    
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
