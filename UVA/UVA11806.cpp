//
//  UVA11806.cpp
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

unsigned long long M,N,K;
const unsigned long long MODER = 1000007;
const int MAXN = 505;
unsigned long long C[MAXN][MAXN];

void prepare(){
    C[0][0] = 1;
    for(int i = 1; i < MAXN; i++){
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; j++){
            C[i][j] = C[i-1][j] + C[i-1][j-1];
            C[i][j] %= MODER;
        }
    }
}

void solve(){
    unsigned long long res = 0;
    for (int S = 0; S < 16; S++) {
        unsigned long long cnt = 0,r = M,c = N;
        if(S&1) cnt++,r--;
        if(S&2) cnt++,r--;
        if(S&4) cnt++,c--;
        if(S&8) cnt++,c--;
        if(cnt&1) res = res + MODER - C[r*c][K];
        else res += C[r*c][K];
        res %= MODER;
    }
    cout << res << '\n';
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prepare();
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt; d++){
        printf("Case %d: ",d);
        cin >> M >> N >> K;
        solve();
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    return 0;
}
