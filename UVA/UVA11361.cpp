//
//  UVA11361.cpp
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

long long a,b,k;
long long wildcard[13][200][200];//when K is too large,ignore
long long moder;
void prepare(){
    memset(wildcard, 0, sizeof(wildcard));
    for(int i = 0; i <= 9; i++){
        wildcard[1][i%moder][i%moder]++;
    }
    int fac = 10;
    for (int i = 1; i <= 10; i++) {
        for(int j = 0; j <= 9; j++){
            for (int k = 0; k < moder; k++) {
                for (int l = 0;l < moder; l++) {
                    long long nm1 = (k + j * fac) % moder;
                    long long nm2 = (l + j) % moder;
                    wildcard[i+1][nm1][nm2] += wildcard[i][k][l];
                }
            }
        }
        fac *= 10;
        fac %= moder;
    }
}

long long sig(long long a){
    if (a % moder) {
        return 0;
    }
    long long j = 0;
    while (a) {
        j += a%10;
        a /= 10;
    }
    return (j%moder == 0)?1:0;
}

long long calc(long long a){
    long long ret = 0;
    long long fac = 10000000000;
    long long hi = 10;
    long long susp = 0,susd = 0;
    long long ca = a;
    while (fac) {
        bool flg = false;
        int i = 0;
        for (; i <= 9; i++) {
            if ((i+1) * fac - 1 + susp <= a) {
                if (!hi) {
                    ret += sig((i+1) * fac - 1 + susp);
                    continue;
                }
                long long rm1 = (moder + (moder - fac * i - susp)%moder)%moder;
                long long rm2 = (moder + (moder - i - susd)%moder)%moder;
                ret += wildcard[hi][rm1][rm2];
                flg = true;
            }else break;
        }
        if (flg) {
            susd += i,susp += i*fac,ca = a - susp;
        }
        fac /= 10,hi--;
    }
    return ret;
}

void solve(){
    prepare();
    cout << calc(b) - calc(a-1) << '\n';
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        cin >> a >> b >> k;
        moder = k;
        if (k > 200) {
            puts("0");
            continue;
        }
        solve();
    }
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
