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

const int MAXN = 100005;
int n;
int seq[MAXN];

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> seq[i];
    }
    int len = 1,l = 1,r = 1;
    while (r < n) {
        if (seq[r+1] >= seq[r]) {
            r++;
            len = max(len,r-l+1);
        }else{
            l = r+1,r = l;
        }
    }
    cout << len << '\n';
    
    return 0;
}
