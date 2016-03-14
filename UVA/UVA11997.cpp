//
//  UVA11997.cpp
//  playground
//
//  Created by 張正昊 on 14/3/2016.
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

const int MAXN = 755;
int k;

struct Item{
    long long s,b;
    bool operator < (const Item &b) const{
        return s > b.s;
    }
};

long long seq[MAXN][MAXN];
priority_queue<Item> que;

void solve(int r){
    while (!que.empty()) {
        que.pop();
    }
    for (int i = 1; i <= k; i++) {
        que.push({seq[1][i]+seq[r][1],1});
    }
    for (int i = 1; i <= k; i++) {
        seq[1][i] = que.top().s;
        long long nb = que.top().b;
        que.pop();
        que.push({seq[1][i] - seq[r][nb] + seq[r][nb+1],nb+1});
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&k) != EOF) {
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                scanf(" %lld",&seq[i][j]);
            }
            sort(seq[i]+1, seq[i]+1+k);
        }
        if (k == 1) {
            printf("%lld\n",seq[1][1]);
            continue;
        }
        for (int i = 2; i <= k; i++) {
            solve(i);
        }
        for(int i = 1;i <= k; i++){
            printf("%lld",seq[1][i]);
            if (i == k) {
                puts("");
            }else{
                putchar(' ');
            }
        }
        
    }
    
    
    return 0;
}
