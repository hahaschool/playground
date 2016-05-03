//
//  UVA10294.cpp
//  playground
//
//  Created by 張正昊 on 25/4/2016.
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

int n,t;

int gcd(int a,int b){
    if (!b) return a;
    return gcd(b,a%b);
}

void solve(){
    long long pow[105];
    pow[0] = 1;
    for(int i = 1; i <= n; i++){
        pow[i] = pow[i-1] * t;
    }
    long long a = 0;
    for(int i = 0; i < n; i++){
        a += pow[gcd(i,n)];
    }
    long long b = 0;
    if (n&1) {
        b = n*pow[(n+1)/2];
    }else{
        b = n/2*(pow[n/2+1]+pow[n/2]);
    }
    printf("%lld %lld\n",a/n,(a+b)/2/n);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    while (scanf(" %d %d",&n,&t) != EOF) {
        solve();
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
