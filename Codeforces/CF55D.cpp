//
//  CF55D.cpp
//  playground
//
//  Created by 張正昊 on 4/5/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

//这个版本是递推，有好多无效状态没有跳过，常数超级大，加了各种姿势才混过

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

typedef unsigned long long ull;

int lcm(int a,int b){
    return a*b/__gcd(a,b);
}

set<int> st;
int mp[2050];
vector<int> vec;
void go_is_god(int cur,int _lcm){
    st.insert(_lcm);
    if(cur == 5) return;
    for(int i = 1; i <= 9; i++){
        go_is_god( cur+1, lcm(_lcm, i));
    }
}

ull dp[20][2550][50];
ull wildcard[20],fac[20];
void prepare(){
    go_is_god(1, 1);
    vec.emplace_back(0);
    for (set<int>::iterator it = st.begin(); it != st.end(); it++) {
        vec.emplace_back(*it);
        mp[*it] = (int)vec.size()-1;
    }
    fac[0] = 1;
    for (int i = 1; i <= 19; i++) {
        wildcard[i] = wildcard[i-1] * 10ULL + 9;
        fac[i] = wildcard[i]+1;
    }
    dp[1][0][1] = 1;
    for (int i = 1; i <= 9; i++) {
        dp[1][i][mp[i]] = 1;
    }
    for (int i = 1; i <= 18; i++) {
        for (int j = 0; j <= 2520; j++) {
            for (int k = 1; k <= 48; k++) {
                if(!dp[i][j][k]) continue;
                for (int l = 0; l <= 9; l++) {
                    int nv = (j * 10 + l)%2520;
                    int nlcm = vec[k];
                    if(l) nlcm = lcm(nlcm, l);
                    dp[i+1][nv][mp[nlcm]] += dp[i][j][k];
                }
            }
        }
    }
}
ull stat(int preload_lcm,ull preload_val,int wildcard){
    if (!wildcard) {
        if (preload_val) {
            return (preload_val%preload_lcm == 0)?1:0;
        }
        return 0;
    }
    ull ret = 0;
    for (int i = 0; i <= 2520; i++) {
        ull loaded_val = (preload_val + i) % 2520;
        for (int j = 1; j <= 48; j++) {
            if(!dp[wildcard][i][j]) continue;
            int loaded_lcm = lcm(preload_lcm, vec[j]);
            if (loaded_val % loaded_lcm == 0) {
                ret += dp[wildcard][i][j];
            }
        }
    }
    if (preload_lcm == 1 && preload_val == 0) {
        ret--;
    }
    return ret;
}

map<ull,ull> mem;
ull query(ull x){
    if(mem.count(x)) return mem[x];
    ull cx = x;
    int dig = 0;
    while (cx) {
        dig++;
        cx /= 10;
    }
    ull ret = 0;
    cx = x;
    int acc_lcm = 1;
    ull acc = 0;
    for (int i = dig; i >= 1; i--) {
        ull cur = cx / fac[i-1];
        for (ull j = 0; j < ((i==1)?cur+1:cur); j++) {
            int nxtlcm = j?lcm(acc_lcm, j):acc_lcm;
            ret += stat(nxtlcm,acc+j*fac[i-1], i-1);
        }
        if(cur) acc_lcm = lcm(acc_lcm, cur);
        acc += (cx/fac[i-1])*fac[i-1];
        cx -= cur * fac[i-1];
    }
    return mem[x] = ret;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prepare();
    int caseCnt;
    cin >> caseCnt;
    for(int d = 1;d <= caseCnt;d++){
        unsigned long long a,b;
        cin >> a >> b;
        cout << query(b) - query(a-1) << '\n';
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    return 0;
}