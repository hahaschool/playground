//
//  LA3641.cpp
//  playground
//
//  Created by 張正昊 on 26/4/2016.
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

bool vis[26];
int cnt[27];

void solve(){
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < 26; i++) {
        int cur = i,len = 0;
        while (!vis[cur]) {
            vis[cur] = true;
            len++;
            cur = str[cur] - 'A';
        }
        cnt[len]++;
    }
    for(int i = 1; i <= 26; i++){
        if (!(i&1) && (cnt[i]&1)) {
            puts("No");
            return;
        }
    }
    puts("Yes");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        cin >> str;
        solve();
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
