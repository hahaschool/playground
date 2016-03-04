//
//  HDU4336.cpp
//  playground
//
//  Created by Adam Chang on 2015/4/6.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

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

using namespace std;

double pa[21];

int main(){
    int n = 0;
    while (cin >> n) {
        memset(pa, 0, sizeof(pa));
        for (int i = 1; i <= n; i++) {
            scanf(" %lf",&pa[i]);
        }
        int maxn = 1 << n;
        double ex = 0;
        for (int i = 1; i < maxn; i++) {
            int ci = i;
            int cnt = 0;
            double pt = 0;
            int idx = 1;
            while (ci) {
                if (ci & 1) {
                    pt += pa[idx];
                    cnt++;
                }
                ci >>= 1;
                idx++;
            }
            if (cnt % 2) {
                ex += 1/pt;
            }else{
                ex -= 1/pt;
            }
        }
        printf("%.10lf\n",ex);
    }
    
    
    return 0;
}