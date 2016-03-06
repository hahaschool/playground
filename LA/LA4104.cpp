//
//  LA4104.cpp
//  playground
//
//  Created by 張正昊 on 5/3/2016.
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

void mod(long long &a,long long &m){
    a %= m;
    if (a < 0) {
        a += m;
    }
}

long long fastpow(long long a,long long p,long long m){
    long long fac = a;
    long long cp = 1;
    long long ret = 1;
    while (cp < p) {
        if (cp & p) {
            ret *= fac;
            mod(ret,m);
        }
        fac *= fac;
        mod(fac,m);
        cp <<= 1;
    }
    return ret;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    cin >> caseCnt;
    for(int d = 1; d <= caseCnt;d++){
        long long x,y,n;
        cin >> x >> y >> n;
        cout << fastpow(x, y, n) << '\n';
    }
    cin >> caseCnt;
    return 0;
}