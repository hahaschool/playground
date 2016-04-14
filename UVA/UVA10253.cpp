//
//  UVA10253.cpp
//  playground
//
//  Created by 張正昊 on 6/4/2016.
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

unsigned long long C(unsigned long long n,unsigned long long m){
    double ans = 1;
    for(int i = 0;i < m; i++){
        ans *= n-i;
    }
    for(int i = 0;i < m; i++){
        ans /= i+1;
    }
    return (unsigned long long)(ans + 0.5);//神姿势
}

unsigned long long f[33];

vector<int> stk;
int cnt[33];
void dfs(int prv,int rem,int cur){
    if (!rem) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < stk.size(); i++) {
            cnt[stk[i]]++;
        }
        unsigned long long ret = 1;
        for (int i = 1; i < cur; i++) {
            ret *= C(f[i]+cnt[i]-1,cnt[i]);
        }
        f[cur] += ret;
    }
    for (int i = prv; i < cur && i <= rem; i++) {
        stk.push_back(i);
        dfs(i,rem-i,cur);
        stk.erase(stk.end()-1);
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    f[1] = 1;
    for (int i = 2; i <= 30; i++) {
        dfs(1, i, i);
    }
    int q;
    while (cin >> q && q) {
        if(q == 1) {cout << 1 << endl;continue;}
        cout << f[q]*2 << endl;
    }
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
