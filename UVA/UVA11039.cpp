//
//  UVA11039.cpp
//  playground
//
//  Created by 張正昊 on 23/2/2016.
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

const int MAXN = 500005;
int n;
int seq[MAXN];

bool cmp(int a,int b){
    return abs(a) < abs(b);
}

int solve(){
    sort(seq+1, seq+1+n, cmp);
    int POS1 = -1,NEG1 = -1;
    for (int i = 1; i <= n; i++) {
        if (seq[i] > 0 && POS1 == -1) {
            POS1 = i;
        }
        if (seq[i] < 0 && NEG1 == -1) {
            NEG1 = i;
        }
        if (POS1 != -1 && NEG1 != -1) {
            break;
        }
    }
    if (POS1 == -1 || NEG1 == -1) {
        return 1;
    }
    int POSans = 0,NEGans = 0;
    int tick = 1;
    for(int i = POS1;i <= n; i++){
        if (tick && seq[i] > 0) {
            POSans++;
            tick ^= 1;
            continue;
        }
        if (!tick && seq[i] < 0) {
            POSans++;
            tick ^= 1;
        }
    }
    tick = 1;
    for (int i = NEG1; i <= n;i++) {
        if (tick && seq[i] < 0) {
            NEGans++;
            tick ^= 1;
            continue;
        }
        if (!tick && seq[i] > 0) {
            NEGans++;
            tick ^= 1;
        }
    }
    return max(POSans,NEGans);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt;d++){
        scanf(" %d",&n);
        for(int i = 1; i<= n; i++){
            scanf(" %d",&seq[i]);
        }
        printf("%d\n",solve());
    }
    return 0;
}