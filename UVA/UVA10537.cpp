//
//  UVA10537.cpp
//  playground
//
//  Created by 張正昊 on 2/2/2016.
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

const int MAXN = 256,MAXE = 2000005;
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
int head[MAXN],ed[MAXE],nxt[MAXE],q;
int m,n,ist,dst;
long long tar;
map<char,int> h;
char o[MAXN];
void gph_clear(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void gph_addEdge(int from,int to){
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

long long cost(long long a){
    long long ret = a/20;
    if(a % 20){
        ret++;
    }
    return ret;
}

long long calc(long long d){
    long long l = 0,r = INF,mid;
    while(l + 1 < r){
        mid = l + (r-l)/2;
        if(mid - cost(mid) >= d){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    if(l - cost(l) == d){
        return l;
    }else{
        return r;
    }
}

struct State{
    int i;
    long long dis;
    State(){
        
    };
    State(int _i,long long _dis){
        i = _i;
        dis = _dis;
    }
    bool operator < (const State & b) const{
        return dis > b.dis;
    }
};
priority_queue<State> que;
long long dis[MAXN];
bool vis[MAXN];
void dijkstra(int rt,long long rd){
    que.push(State(rt,rd));
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; i++){
        dis[i] = INF;
    }
    dis[rt] = rd;
    while(!que.empty()){
        int cur = que.top().i;
        que.pop();
        for(int i = head[cur];i;i = nxt[i]){
            int v = ed[i];
            if(isupper(o[cur])){
                //town
                long long att = calc(dis[cur]);
                if(att < dis[v]){
                    dis[v] = att;
                    if(!vis[v]){
                        que.push(State(v,dis[v]));
                        vis[v] = true;
                    }
                }
            }else{
                //villy
                if(dis[cur] + 1 < dis[v]){
                    dis[v] = dis[cur]+1;
                    if(!vis[v]){
                        que.push(State(v,dis[v]));
                        vis[v] = true;
                    }
                }
            }
        }
    }
}


stack<int> stk;
bool print_dfs(int u){
    vis[u] = true;
    if(u == dst){
        stk.push(u);
        return true;
    }
    for(int j = 1; j <= 2 ; j++){//fuck you!ABCDEF...abcdef... is the desired lex seq.
    for(int i = 0; i < 26; i++){
        
            int c = ((j&1)?'A':'a') + i;
            if(h.count(c)){
                int v = h[c];
                if(vis[v]){
                    continue;
                }
                bool flg = false;
                for(int k = head[u];k;k = nxt[k]){
                    if(ed[k] == v){
                        flg = true;
                        break;
                    }
                }
                if(flg){
                if(isupper(o[v])){
                    if(dis[u] - cost(dis[u]) == dis[v]){
                        if(print_dfs(v)){
                            stk.push(u);
                            return true;
                        }
                    }
                }else{
                    if(dis[u] - 1 == dis[v]){
                        if(print_dfs(v)){
                            stk.push(u);
                            return true;
                        }
                    }
                }
                }
            }
        }
    }
    return false;
}

void printans(){
    memset(vis, 0, sizeof(vis));
    while(!stk.empty()){
        stk.pop();
    }
    print_dfs(ist);
    while(!stk.empty()){
        putchar(o[stk.top()]);
        stk.pop();
        if(!stk.empty()){
            putchar('-');
        }
    }
    puts("");
}

void solve(){
    dijkstra(dst,tar);
    printf("%lld\n",dis[ist]);
    printans();
}

void mkhash(char a){
    if(!h.count(a)){
        h[a] = ++n;
        o[n] = a;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while(scanf(" %d",&m) != EOF){
        if(m == -1){
            break;
        }
        printf("Case %d:\n",++caseCnt);
        gph_clear();
        h.clear();
        n = 0;
        char a,b;
        for(int i = 1; i <= m; i++){
            scanf(" %c %c",&a,&b);
            mkhash(a),mkhash(b);
            gph_addEdge(h[a],h[b]);
            gph_addEdge(h[b],h[a]);
        }
        scanf(" %lld %c %c",&tar,&a,&b);
        mkhash(a),mkhash(b);
        ist = h[a];
        dst = h[b];
        solve();
    }
    
    
    
    return 0;
}