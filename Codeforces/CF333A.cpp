//
//  CF333A.cpp
//  playground
//
//  Created by 張正昊 on 12/3/2016.
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
    while (cin >> n) {
        long long mkr = 1;
        while (mkr < n && n % mkr == 0) {
            mkr *= 3;
        }
        if (mkr >= n) {
            puts("1");
        }else{
            cout << n/mkr+1 << '\n';
        }
    }
    return 0;
}
