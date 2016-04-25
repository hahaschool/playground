//
//  UVA11426.cpp
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
const int MAXN = 4000005;
int phi[MAXN];
void phi_table(int n){
    for (int i = 2; i <= n; i++) phi[i] = 0;
    phi[1] = 1;
    for(int i = 2; i <= n; i++){
        if(!phi[i]){
            for (int j = i; j <= n; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i-1);
            }
        }
    }
}

LL f[MAXN],s[MAXN];
void prepare(){
    phi_table(MAXN-5);
    for (int i = 1; i <= MAXN-5; i++) {
        for (int j = 2; i*j <= MAXN-5; j++) {
            f[i*j] += phi[j] * i;
        }
    }
    for (int i = 1; i <= MAXN-5; i++) {
        s[i] = s[i-1] + f[i];
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prepare();
    int q;
    while (cin >> q && q) {
        cout << s[q] << '\n';
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
