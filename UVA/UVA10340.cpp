//
//  UVA10340.cpp
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

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (cin >> a >> b) {
        if (a.size() > b.size()) {
            swap(a, b);
        }
        int cur = 0;
        for (int i = 0; i < b.size(); i++) {
            if (a[cur] == b[i]) {
                cur++;
            }
        }
        if (cur == a.size()) {
            puts("Yes");
        }else{
            puts("No");
        }
    }
    
    return 0;
}