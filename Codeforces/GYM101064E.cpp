//
//  GYM101064E.cpp
//  playground
//
//  Created by 張正昊 on 6/9/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
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
#include <bitset>

#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);


using namespace std;

typedef long long LL;

const int MAXN = 1005,MAXMSK = 32788,SP = 10;

struct trieNode{
    int ch[SP];
    int freq;
    vector<int> ids;
    
    int last,fail;
    
    void init(){
        memset(ch, -1, sizeof(ch));
        freq = 0;
        ids.clear();
        last = fail = -1;
    }
} pool[MAXN];

int trie_tot = 0;
void trie_init(){
    pool[0].init();
    trie_tot = 1;
}
int trie_alloc(){
    pool[trie_tot].init();
    return trie_tot++;
}
void trie_insert(string str,int id){
    int len = str.size(),lst = 0;
    REP(i, len){
        if(pool[lst].ch[str[i]-'a'] == -1){
            pool[lst].ch[str[i]-'a'] = trie_alloc();
        }
        lst = pool[lst].ch[str[i]-'a'];
    }
    pool[lst].freq++;
    pool[lst].ids.push_back(id);
}
void ACA_buildfail(){
    queue<int> que;
    int root = 0;
    pool[root].fail = root;
    pool[root].last = root;
    REP(i, SP){
        if(pool[root].ch[i] == -1){
            pool[root].ch[i] = root;
        }else{
            pool[pool[root].ch[i]].fail = root;
            pool[pool[root].ch[i]].last = root;
            que.push(pool[root].ch[i]);
        }
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        REP(i, SP){
            if (pool[u].ch[i] == -1) {
                pool[u].ch[i] = pool[pool[u].fail].ch[i];
            }else{
                pool[pool[u].ch[i]].fail = pool[pool[u].fail].ch[i];
                pool[pool[u].ch[i]].last = pool[pool[pool[u].fail].ch[i]].freq?pool[pool[u].fail].ch[i]:pool[pool[pool[u].fail].ch[i]].last;
                que.push(pool[u].ch[i]);
            }
        }
    }
}

int n,m;
vector<string> neg,kid;
int dp[MAXMSK][MAXN];
int prv[MAXMSK][MAXN][2];
char prc[MAXMSK][MAXN];
bool inq[MAXMSK][MAXN];

bool mkr[MAXN],vis[MAXN];
bool mark(int u){
    int lst = u;
    set<int> idst;
    while (lst) {
        REP(i, pool[lst].ids.size()){
            idst.insert(pool[lst].ids[i]);
        }
        lst = pool[lst].last;
    }
    pool[u].freq = idst.size();
    pool[u].ids.clear();
    for (set<int>::iterator it = idst.begin(); it != idst.end(); it++) {
        pool[u].ids.push_back(*it);
    }
    if(pool[u].freq && pool[u].ids[0] < 0) mkr[u] = true;
    
    return false;
    
    /*
    vis[u] = true;
    if(mkr[u]) return true;
    sort(pool[u].ids.begin(), pool[u].ids.end());
    pool[u].ids.erase(unique(pool[u].ids.begin(), pool[u].ids.end()), pool[u].ids.end());
    if(pool[u].ids.size() && pool[u].ids[0] < 0) return mkr[u]=true;
    if(vis[pool[u].last]) return mkr[u]=mkr[pool[u].last];
    return mkr[u] = mark(pool[u].last);
     */
    
}

struct State{
    int msk,u;
};

queue<State> que;
void solve(){
    trie_init();
    REP(i, n) trie_insert(neg[i], i+1);
    REP(i, m) trie_insert(kid[i], -i-1);
    ACA_buildfail();
    memset(mkr, 0, sizeof(mkr));
    memset(vis, 0, sizeof(vis));
    REP(i, trie_tot) mark(i);
    
    memset(dp, 0x3f, sizeof(dp));
    memset(inq, 0, sizeof(inq));
    
    while(!que.empty()) que.pop();
    que.push({0,0});
    dp[0][0] = 0;
    inq[0][0] = true;
    while (!que.empty()) {
        int msk = que.front().msk,u = que.front().u;
        que.pop();
        inq[msk][u] = false;
        REP(i, SP){
            int v = pool[u].ch[i];
            if(mkr[v]) continue;
            int nmk = 0;
            if(pool[v].freq){
                REP(j, pool[v].ids.size()){
                    nmk |= 1 << (pool[v].ids[j]-1);
                }
            }
            if(dp[msk][u]+1 < dp[msk|nmk][v]){
                dp[msk|nmk][v] = dp[msk][u]+1;
                prv[msk|nmk][v][0] = msk;
                prv[msk|nmk][v][1] = u;
                prc[msk|nmk][v] = i;
                if(!inq[msk|nmk][v]){
                    que.push({msk|nmk,v});
                    inq[msk|nmk][v] = true;
                }
            }
        }
    }
    
    int mi = 0x3f3f3f3f,mii = -1;
    REP(i, trie_tot){
        if(dp[(1<<n)-1][i] < mi){
            mi = dp[(1<<n)-1][i];
            mii = i;
        }
    }
    if(mii == -1) {
        puts("-");
        return;
    }
    int cst = (1<<n)-1;
    stack<char> stk;
    while (mi--) {
        stk.push('a'+prc[cst][mii]);
        int tcs = cst;
        cst = prv[tcs][mii][0];
        mii = prv[tcs][mii][1];
    }
    while (stk.size()) {
        putchar(stk.top());
        stk.pop();
    }
    puts("");
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (cin >> n >> m) {
        neg.clear();neg.resize(n);
        kid.clear();kid.resize(m);
        REP(i,n) cin >> neg[i];
        REP(i,m) cin >> kid[i];
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
