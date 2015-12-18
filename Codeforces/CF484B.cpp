//
//  CF484B.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/12.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

#include <algorithm>
#include <cmath>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int seq[200005];
int main()
{
    int n = 0;
    scanf(" %d", &n);
    memset(seq, 0, sizeof(seq));
    for (int i = 1; i <= n; i++) {
        scanf(" %d", &seq[i]);
    }
    n = unique(seq + 1, seq + 1 + n) - seq - 1;
    sort(seq + 1, seq + 1 + n);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        //opt
        if (seq[i] == 1) {
            continue;
        }
        if (res >= seq[i] - 1) {
            continue;
        }
        int k = 0;
        while (k * seq[i] <= seq[n]) {
            k++;
            int pos = lower_bound(seq + 1, seq + 1 + n, k * seq[i]) - seq;
            pos--;
            if (pos >= i)
                res = max(res, seq[pos] % seq[i]);
            //quit
            if (res >= seq[i] - 1) {
                break;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}