//  HDU5724.cpp
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

int board[1005];

int encode(vector<bool> vec){
    int ret = 0;
    for (int i = 0; i < 20; i++) {
        if(vec[i]) ret += 1<<i;
    }
    return ret;
}
void decode(vector<bool> &vec,int code){
    for (int i = 0; i < 20; i++) {
        vec.push_back(code&1);
        code >>= 1;
    }
    
}

const int MAXN = 1100000;
int sg[MAXN];
int dfs(int u){
    if(sg[u] != -1) return sg[u];
    set<int> st;
    //enumerate move
    bool hav[21];
    memset(hav, 0, sizeof(hav));
    for (int i = 0; i < 20; i++) {
        if(u&(1<<i)){
            for (int j = i+1; j < 20; j++) {
                if(!(u&(1<<j))){
                    //can move,commit
                    u ^= 1<<i,u ^= 1<<j;
                    hav[dfs(u)] = true;
                    u ^= 1<<i,u ^= 1<<j;
                    break;
                }
            }
        }
    }
    //get mex
    for (int i = 0; i <= 20; i++) {
        if(!hav[i]){
            return sg[u] = i;
        }
    }
    return 0;
}
int n;
bool solve(){
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res ^= dfs(board[i]);
    }
    return res;
}

int main(){
    memset(sg, -1, sizeof(sg));
    for (int i = 0; i < (1<<20); i++) {
        dfs(i);
    }
    
    
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d",&n);
        for (int i = 1; i <= n; i++) {
            int cnt;
            scanf(" %d",&cnt);
            vector<bool> vec;
            vec.resize(20);
            for (int j = 0; j < cnt; j++) {
                int a;
                scanf(" %d",&a);
                vec[a-1] = true;
            }
            board[i] = encode(vec);
        }
        if(solve()){
            puts("YES");
        }else{
            puts("NO");
        }
    }
    return 0;
}