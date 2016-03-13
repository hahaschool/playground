//
//  UVA11490.cpp
//  playground
//
//  Created by 張正昊 on 13/3/2016.
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
#endif
    long long n;
    set<long long> ans;
    int caseCnt = 0;
    while (scanf(" %lld",&n) != EOF && n) {
        ans.clear();
        long long b = 1;
        while (n > 6LL*b*b) {
            long long upper = n - 6LL*b*b;
            if (upper % (b*7LL)) {
                b++;
                continue;
            }
            ans.insert(-upper/(b*7LL));
            b++;
        }
        if (!ans.size()) {
            puts("No Solution Possible\n");
            continue;
        }
        for (set<long long>::iterator it = ans.begin(); it != ans.end(); it++) {
            long long res = ((-*it)%100000007LL)*((-*it)%100000007LL)*2LL%100000007LL;
            if (res < 0) {
                res += 100000007;
            }
            printf("Possible Missing Soldiers = %lld\n",res);
        }
        puts("");
    }
    
    
    return 0;
}
