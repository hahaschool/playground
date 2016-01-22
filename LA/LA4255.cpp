//
//  LA4255.cpp
//  playground
//
//  Created by 張正昊 on 21/1/2016.
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

const int MAXN = 15,MAXE = 405;
int n;
char mat[MAXN][MAXN];
int head[MAXN],to[MAXE],nxt[MAXE],q;
void gph_clear(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void gph_addEdge(int _from,int _to){
    to[q] = _to;
    nxt[q] = head[_from];
    head[_from] = q++;
}

int topo_vis[MAXN];
stack<int> topo_res;
bool topo_dfs(int cur){
    topo_vis[cur] = -1;
    for(int i = head[cur]; i;i = nxt[i]){
        int nxt = to[i];
        if(topo_vis[nxt] == -1){
            return false;
        }else if(topo_vis[nxt] == 0){
            if(!topo_dfs(nxt)){
                return false;
            }
        }
    }
    topo_vis[cur] = 1;
    topo_res.push(cur);
    return true;
}
bool toposort(){
    while (!topo_res.empty()) {
        topo_res.pop();
    }
    memset(topo_vis, 0, sizeof(topo_vis));
    for(int i = 1; i <= n+1; i++){
        if(!topo_vis[i]){
            if(!topo_dfs(i)){
                return false;//loop happened
            }
        }
    }
    return true;
}

vector<pair<int, int> > equals;
void buildgph(){
    gph_clear();
    equals.clear();
    //assuming 1 is 0,2~n+1 is Si
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(mat[i][j] == '+'){
                gph_addEdge(j+1, i);
            }else if(mat[i][j] == '-'){
                gph_addEdge(i, j+1);
            }else if(mat[i][j] == '0'){
                equals.push_back(make_pair(j+1, i));
            }
        }
    }
}

int sum[MAXN];
void solve(){
    buildgph();
    toposort();
    memset(sum, 0, sizeof(sum));
    vector<int> seq;
    while (!topo_res.empty()) {
        seq.push_back(topo_res.top());
        topo_res.pop();
    }
    int zeropos = -1;
    for(int i = 0; i < seq.size(); i++){
        if(seq[i] == 1){
            zeropos = i;
            break;
        }
    }
    int cur = 0;
    for(int i = zeropos; i < seq.size(); i++){
        sum[seq[i]-1] = cur--;
    }
    cur = 0;
    for(int i = zeropos-1; i >= 0; i--){
        sum[seq[i]-1] = ++cur;
    }
    for(int i = 0; i < equals.size(); i++){
        sum[equals[i].first-1] = sum[equals[i].second-1];
    }
    for(int i = 1; i <= n; i++){
        printf("%d",sum[i]-sum[i-1]);
        if(i < n){
            putchar(' ');
        }else{
            puts("");
        }
    }
    
    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt; d++){
        scanf(" %d",&n);
        for(int i = 1; i <= n; i++){
            for(int j = i;j <= n; j++){
                scanf(" %c",&mat[i][j]);
            }
        }
        solve();
    }
    
    return 0;
}


