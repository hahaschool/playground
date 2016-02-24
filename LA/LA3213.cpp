//
//  LA3213.cpp
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

string a,b;
int cnta[26],cntb[26];

void solve(){
    memset(cnta, 0, sizeof(cnta));
    for (int i = 0; i < a.size(); i++) {
        cnta[a[i] - 'A']++;
    }
    sort(cnta, cnta+26);
    memset(cntb, 0, sizeof(cntb));
    for (int i = 0; i < b.size(); i++) {
        cntb[b[i] - 'A']++;
    }
    sort(cntb, cntb+26);
    for (int i = 0; i < 26; i++) {
        if (cnta[i] != cntb[i]) {
            puts("NO");
            return;
        }
    }
    puts("YES");
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (cin >> a >> b) {
        solve();
    }
    return 0;
}