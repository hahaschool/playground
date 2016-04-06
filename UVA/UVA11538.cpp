//
//  UVA11538.cpp
//  playground
//
//  Created by 張正昊 on 30/3/2016.
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

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    unsigned long long M,N;
    while (cin >> N >> M && M+N) {
        unsigned long long res = M * N * (N - 1) + N * M * (M - 1);
        unsigned long long i;
        for (i = 2; i < min(M,N); i++) {
            res += i * (i - 1) * 4;
        }
        for(;i <= max(M,N); i++){
            res += min(M,N) * (min(M,N) - 1) * 2;
        }
        cout << res << '\n';
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
