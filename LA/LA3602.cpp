//
//  LA3602.cpp
//  playground
//
//  Created by 張正昊 on 24/2/2016.
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

const int MAXM = 55,INF = 0x3f3f3f3f;
int m,n;
char dir[5] = "ACGT";
string seq[MAXM];
string ans;
int ansham;

inline int ham(char ch,int pos){
    int ret = 0;
    for (int i = 1; i <= m; i++) {
        if (seq[i][pos] != ch) {
            ret++;
        }
    }
    return ret;
}


void solve(){
    ans.clear();
    ansham = 0;
    for (int i = 0; i < n; i++) {
        int minham = INF;
        char minch = 0;
        for (int j = 0; j < 4; j++) {
            int curham = ham(dir[j], i);
            if (curham < minham) {
                minham = curham;
                minch = dir[j];
            }
        }
        ans += minch;
        ansham += minham;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        scanf(" %d %d",&m,&n);
        for (int i = 1; i <= m; i++) {
            cin >> seq[i];
        }
        solve();
        cout << ans << '\n' << ansham << '\n';
    }
    
    return 0;
}