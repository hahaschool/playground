//
//  LA3211.cpp
//  playground
//
//  Created by 張正昊 on 27/1/2016.
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

static const int MAXN = 2105;
vector<int> gph[MAXN*2];
bool mark[MAXN*2];
stack<int> stk;
int n;
void init(int _n){
    n = _n;
    for(int i = 0;i < 2*MAXN; i++){
        gph[i].clear();
    }
    memset(mark, false, sizeof(mark));
    while(!stk.empty()){
        stk.pop();
    }
}
void gph_addEdge(int from,int to){
    gph[from].push_back(to);
}
bool dfs(int x){
    if(mark[x^1]){
        return false;
    }
    if(mark[x]){
        return true;
    }
    stk.push(x);
    mark[x] = true;
    for(int i = 0;i < gph[x].size();i++){
        int v = gph[x][i];
        if(!dfs(v)){
            return false;
        }
    }
    return true;
}
//x = xval or y = yval
void add_clause(int x,int xval,int y,int yval){
    x = x*2+xval;
    y = y*2+yval;
    gph_addEdge(x^1, y);
    gph_addEdge(y^1, x);
}
bool solve(){
    for(int i = 0;i < 2*n;i+=2){
        if(!mark[i] && !mark[i+1]){
            while(!stk.empty()){
                stk.pop();
            }
            if(!dfs(i)){
                while(!stk.empty()){
                    mark[stk.top()] = false;
                    stk.pop();
                }
                if(!dfs(i+1)){
                    return false;
                }
            }
        }
    }
    return true;
}
pair<int, int> plane[MAXN];

bool test(int mid){
    init(n);
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            //early : 1 late : 0
            if (abs(plane[i].first-plane[j].first) < mid) {
                add_clause(i, 0, j, 0);
            }
            if (abs(plane[i].first-plane[j].second) < mid) {
                add_clause(i, 0, j, 1);
            }
            if (abs(plane[i].second-plane[j].first) < mid) {
                add_clause(i, 1, j, 0);
            }
            if (abs(plane[i].second-plane[j].second) < mid) {
                add_clause(i, 1, j, 1);
            }
            
        }
    }
    return solve();
}

int glbmx = 0;
int work(){
    int l = 0,r = glbmx,mid;
    while (l + 1 < r) {
        mid = (l+r)/2;
        if(test(mid)){
            l = mid;
        }else{
            r = mid-1;
        }
    }
    if(test(r)){
        return r;
    }else{
        return l;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&n) != EOF) {
        glbmx = 0;
        for(int i = 1; i <= n; i++){
            scanf(" %d %d",&plane[i].first,&plane[i].second);
            glbmx = max(plane[i].first,max(plane[i].second,glbmx));
        }
        printf("%d\n",work());
    }
    
    return 0;
}