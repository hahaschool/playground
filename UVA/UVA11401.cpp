//
//  11401.cpp
//  playground
//
//  Created by 張正昊 on 5/4/2016.
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

const int MAXN = 1000005;
unsigned long long d[MAXN];

void prepare(){
    unsigned long long cur = 1;
    for(int i = 4; i < MAXN-1; i++){
        d[i] = d[i-1] + cur;
        d[i+1] = d[i] + cur;
        i++,cur++;
    }
    for(int i = 1;i < MAXN; i++){
        d[i] += d[i-1];
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prepare();
    int n;
    while (cin >> n && n >= 3) {
        cout << d[n] << '\n';
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
