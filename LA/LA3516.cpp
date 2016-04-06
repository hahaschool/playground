//
//  LA3516.cpp
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

string str;
const long long MODER = 1000000000;
const int MAXN = 305;
long long d[MAXN][MAXN];

long long dp(int i,int j){
    if (i > j || str[i-1] != str[j-1]) {
        return 0;
    }
    if (i == j) {
        return 1;
    }
    long long &ret = d[i][j];
    if(ret >= 0) return ret;
    ret = 0;
    for(int k = i;k <= j; k++){
        if(str[i-1] == str[k-1])
        ret += dp(i+1,k-1) * dp(k,j);
        ret %= MODER;
    }
    return ret;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    while (cin >> str) {
        memset(d, -1, sizeof(d));
        cout << dp(1, str.size()) << endl;
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
