//
//  LA5059.cpp
//  playground
//
//  Created by 張正昊 on 23/4/2016.
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

long long sg(long long a){
    return (a&1)?sg(a/2):a/2;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1;d <= caseCnt; d++) {
        int n;
        scanf(" %d",&n);
        long long res = 0;
        for (int i = 1; i<= n; i++) {
            long long a;
            scanf(" %lld",&a);
            res ^= sg(a);
        }
        if (res) {
            puts("YES");
        }else{
            puts("NO");
        }
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
