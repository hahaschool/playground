//
//  LA3713.cpp
//  playground
//
//  Created by 張正昊 on 28/1/2016.
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

struct TwoSAT{
    //position started from 1
    static const int MAXN = 100005;
    vector<int> gph[MAXN*2];
    stack<int> stk;
    bool mkr[MAXN*2];
    int n;
    void init(int _n){
        n = _n;
        for(int i = 0; i <= 2*n+1; i++){
            gph[i].clear();
            mkr[i] = false;
        }
        while(!stk.empty()){
            stk.pop();
        }
    }
    bool dfs(int x){
        if(mkr[x]){
            return true;
        }
        if(mkr[x^1]){
            return false;
        }
        stk.push(x);
        mkr[x] = true;
        for(int i = 0; i < gph[x].size(); i++){
            int v = gph[x][i];
            if(!dfs(v)){
                return false;
            }
        }
        return true;
    }
    void add_edge(int from,int to){
        gph[from].push_back(to);
    }
    //x = xval OR y = yval
    void add_clause(int x,int xval,int y,int yval){
        x = x*2+xval;
        y = y*2+yval;
        add_edge(x^1, y);
        add_edge(y^1, x);
    }
    bool solve(){
        for(int i = 2; i <= 2*n; i+=2){
            if(!mkr[i] && !mkr[i^1]){
                while(!stk.empty()){
                    stk.pop();
                }
                if(!dfs(i)){
                    while(!stk.empty()){
                        mkr[stk.top()] = false;
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
} tsat;

int n,m;
const int MAXN = 100005;
int age[MAXN];
int avg;

inline int type(int x){
    if(age[x] >= avg){
        return 1;//A or C
    }else{
        return 2;//B or C
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while(scanf(" %d %d",&n,&m) != EOF){
        if(!n && !m){
            break;
        }
        tsat.init(n);
        avg = 0;
        for(int i = 1; i <= n; i++){
            scanf(" %d",&age[i]);
            avg += age[i];
        }
        avg = ceil((double)avg/(double)n);
        for(int i = 1; i <= m; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            if(type(a) == type(b)){
                tsat.add_clause(a, 0, b, 0);
                tsat.add_clause(a, 1, b, 1);
            }else{
                tsat.add_clause(a, 1, b, 1);
            }
        }
        if(tsat.solve()){
            for(int i = 2; i <= 2*n; i+=2){
                if(tsat.mkr[i]){
                   puts("C");
                }
                if(tsat.mkr[i^1]){
                    if(type(i/2) == 1){
                        puts("A");
                    }else{
                        puts("B");
                    }
                }
            }
        }else{
            puts("No solution.");
        }
    }
    
    
    
    return 0;
}



