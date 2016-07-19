//
//  TCXorSequence.cpp
//  playground
//
//  Created by 張正昊 on 19/7/2016.
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

const int MAXN = 4000005;

struct TreeNode{
    int ch[2],par,siz;
    TreeNode(){
        ch[0] = ch[1] = -1;
        par = -1;
        siz = 0;
    }
} pool[MAXN];
int tot,root;

void init(){
    tot = root = 1;
    pool[root] = TreeNode();
}
int alloc(){
    pool[++tot] = TreeNode();
    return tot;
}

void maintain(int u){
    int ret = 0;
    if(pool[u].ch[0] != -1) ret += pool[pool[u].ch[0]].siz;
    if(pool[u].ch[1] != -1) ret += pool[pool[u].ch[1]].siz;
    pool[u].siz = ret;
}
void recursive_maintain(int u){
    while (u != -1) {
        maintain(u);
        u = pool[u].par;
    }
}

long long cost[33][2];
void insert(int n){
    int u = root;
    for (int i = 29,msk = 1<<29; i >= 0; msk >>= 1,i--) {
        int dig = (n&msk)?1:0;
        if(pool[u].ch[0] == -1) pool[pool[u].ch[0] = alloc()].par = u;
        if(pool[u].ch[1] == -1) pool[pool[u].ch[1] = alloc()].par = u;
        if(dig) cost[i][0] += pool[pool[u].ch[0]].siz;
        else cost[i][1] += pool[pool[u].ch[1]].siz;
        u = pool[u].ch[dig];
    }
    pool[u].siz++;
    recursive_maintain(pool[u].par);
}

class XorSequence{
public:
    vector<long long> vec;
    long long getmax(int _N,int _sz,int _A0,int _A1,int _P,int _Q,int _R){
        vec.resize(_sz);
        vec[0] = _A0;
        vec[1] = _A1;
        for (int i = 2; i < _sz; i++) {
            vec[i] = (vec[i-2]*_P+vec[i-1]*_Q+_R)%_N;
        }
        memset(cost, 0, sizeof(cost));
        for (int i = 0; i < _sz; i++) {
            insert(vec[i]);
        }
        long long res = 0;
        for (int i = 0; i <= 29; i++) {
            res += max(cost[i][1],cost[i][0]);
        }
        return res;
    }
    XorSequence(){}
};

XorSequence solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.getmax(524288, 76851, 106815, 442987, 457652, 41007, 502193) << endl;
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
