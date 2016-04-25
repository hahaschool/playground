//
//  UVA11762.cpp
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

int n;

const int MAXN = 1000000;
int prime[MAXN/10],primetot;
bool isprime[MAXN+5];
void genprime(){
    primetot = 0;
    memset(isprime, true, sizeof(isprime));
    for (int i = 2; i <= MAXN; i++) {
        if(isprime[i]){
            prime[++primetot] = i;
            for (int j = i+i; j <= MAXN; j += i) {
                isprime[j] = false;
            }
        }
    }
}

double dp[MAXN];
bool vis[MAXN];
double dget(int a){
    if (vis[a]) {
        return dp[a];
    }
    double ret = 0;
    int p = 0,g = 0;
    for (int i = 1; i <= primetot && prime[i] <= a; i++) {
        p++;
        if(a % prime[i] == 0){
            g++;
            ret += dget(a/prime[i]);
        }
    }
    ret = (ret + p) / g;
    return dp[a] = ret;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    genprime();
    vis[1] = true;
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        printf("Case %d: ",d);
        scanf("%d",&n);
        printf("%.10lf\n",dget(n));
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
