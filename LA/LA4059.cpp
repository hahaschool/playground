//
//  LA4059.cpp
//  playground
//
//  Created by 張正昊 on 5/3/2016.
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

const int MAXN = 1005,MAXE = 2000005;
int head[MAXN],ed[MAXE],nxt[MAXE],deg[MAXN],q;
int n,m,t;
void clr(){
    for(int i = 1; i<= n; i++){
        head[i] = deg[i] = 0;
    }
    q = 2;
}
void addedge(int from,int to){
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

struct disjointSet{
    int par[MAXN];
    void init(){
        for(int i = 1; i<= n; i++){
            par[i] = i;
        }
    }
    int find(int a){
        if(par[a] == a){
            return a;
        }
        return par[a] = find(par[a]);
    }
    void link(int a,int b){
        int pa = find(a);
        int pb = find(b);
        par[pa] = pb;
    }
    bool check(int a,int b){
        return find(a) == find(b);
    }
} djset;

map<int,vector<int> > mp;
void solve(){
    mp.clear();
    for(int i = 1;i <= n; i++){
        mp[djset.find(i)].push_back(i);
    }
    int ans = m-1;
    for (map<int,vector<int> >::iterator it = mp.begin(); it != mp.end(); it++) {
        vector<int> &vec = it->second;
        if (vec.size() <= 1) {
            continue;
        }
        ans++;
        int oddcnt = 0;
        for(int i = 0; i < vec.size(); i++){
            if (deg[vec[i]] % 2) {
                oddcnt++;
            }
        }
        if (oddcnt > 2) {
            ans += (oddcnt-2)/2;
        }
    }
    printf("%d\n",ans*t);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while(scanf(" %d %d %d",&n,&m,&t) != EOF && n+m+t){
        printf("Case %d: ",++caseCnt);
        if(m == 0){
            puts("0");
            continue;
        }
        clr();
        djset.init();
        for(int i = 1; i<= m; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            addedge(a, b);
            addedge(b, a);
            deg[a]++,deg[b]++;
            djset.link(a, b);
        }
        solve();
    }
    
    
    return 0;
}
