//
//  HDU5764.cpp
//  playground
//
//  Created by 張正昊 on 29/7/2016.
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
#include <functional>
#include <numeric>

using namespace std;

const int MAXN = 200005, MAXE = MAXN*2;
int head[MAXN],ed[MAXE],nxt[MAXE],val[MAXN],q;
int n;
void init(){
    for(int i = 1;i <= n; i++){
        head[i] = 0;
    }
    q = 2;
}
void ade(int s,int t){
    ed[q] = t;
    nxt[q] = head[s];
    head[s] = q++;
}

bool chain_vis[MAXN];//One chain can only be confirmed once
bool determine[MAXN];
bool dfs(int u,int chain_id,int p){
    chain_vis[chain_id] = true;
    bool self_chain_met = false;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ed[i];
        if(v != p){
            if(val[v] == chain_id){
                if(self_chain_met){
                    //Exception : Not a chain but a tree
                    return false;
                }else{
                    self_chain_met = true;
                    if(!dfs(v,val[v],u)) return false;
                }
            }else{
                if(val[v] > chain_id){
                    //Exception : Voilation of "parent > child" relation
                    return false;
                }
                if(chain_vis[val[v]]){
                    //Exception : One chain can only be confirmed once
                    return false;
                }
                if(!dfs(v,val[v],u)) return false;
            }
        }
    }
    if(!self_chain_met){
        //Current Point being the last of chain (or, leaf)
        determine[u] = true;
    }
    return true;
}

int find_max_chain(int u,int p){
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if(v != p && val[v] == n){
            return find_max_chain(v, u);
        }
    }
    return u;
}

vector<int> candidate;
set<int> st;
bool free_var[MAXN];
bool build_ans(int rt){
    memset(chain_vis, false, sizeof(chain_vis));
    memset(determine, false, sizeof(determine));
    if(!dfs(rt, n, -1)){
        return false;
    }
    st.clear();
    memset(free_var, true, sizeof(free_var));
    for(int i = 1;i <= n; i++){
        if(determine[i]){
            free_var[val[i]] = false;
        }
    }
    for (int i = 1;i <= n; i++) {
        if(free_var[i]){
            st.insert(i);
        }
    }
    candidate.clear();
    candidate.resize(n);
    for(int i = n;i >= 1; i--){
        if(determine[i]){
            candidate[i-1] = val[i];
        }else{
            if(st.size()){
                set<int>::iterator lb = st.lower_bound(val[i]);
                if(lb == st.end() || (*lb > val[i] && lb != st.begin())) --lb;
                if(lb != st.end() && *lb <= val[i]) {
                    candidate[i-1] = *lb;
                    st.erase(*lb);
                }else return false;
            }else{
                //Exception : Free variable not sufficant
                return false;
            }
        }
    }
    return true;
}

vector<int> ans;

void solve(){
    //Finding Max Chain
    if(*max_element(val+1, val+1+n) != n){
        puts(" Impossible");
        return;
    }
    int max_chain_end[2];
    for(int i = 1;i <= n; i++){
        if(val[i] == n){
            max_chain_end[0] = i;
            break;
        }
    }
    max_chain_end[1] = find_max_chain(max_chain_end[0], -1);
    max_chain_end[0] = find_max_chain(max_chain_end[1], -1);
    
    ans.clear();
    ans.resize(n, n);
    bool flg = false;
    if(build_ans(max_chain_end[0])){
        flg = true;
        ans = min(ans,candidate);
    }
    if(build_ans(max_chain_end[1])){
        flg = true;
        ans = min(ans,candidate);
    }
    if(!flg){
        puts(" Impossible");
        return;
    }
    for(int i = 0;i < ans.size(); i++){
        printf(" %d",ans[i]);
    }
    puts("");
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int __ = 1;__ <= caseCnt; __++){
        printf("Case #%d:",__);
        scanf(" %d",&n);
        init();
        for(int i = 1;i <= n; i++){
            scanf(" %d",&val[i]);
        }
        for(int i = 1;i < n; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            ade(a,b);
            ade(b,a);
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
