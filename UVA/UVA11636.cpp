//
//  UVA11636.cpp
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

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int n;
    int caseCnt = 0;
    while (scanf(" %d",&n) != EOF && n >= 0) {
        int cnt = 0;
        int hid = 1;
        while (hid < n) {
            hid *= 2;
            cnt++;
        }
        printf("Case %d: %d\n",++caseCnt,cnt);
    }
    
    return 0;
}