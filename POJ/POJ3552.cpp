//
//  POJ3552.cpp
//  playground
//
//  Created by 張正昊 on 17/8/15.
//  Copyright © 2015 Adam Chang. All rights reserved.
//
/*
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>

using namespace std;

const int MAXN = 1005;

int n = 0, m = 0;
vector<int> to[MAXN];
vector<int> to2[MAXN];

void add_edge(int a, int b){
    to[a].push_back(b);
    to[b].push_back(a);
}

void add_edge2(int a, int b){
    to2[a].push_back(b);
    to2[b].push_back(a);
}


void remove_duplicate(vector<int> *to){
    for (int i = 1; i <= n; i++) {
        sort(to[i].begin(), to[i].end());
        to[i].erase(unique(to[i].begin(), to[i].end()), to[i].end());
    }
}

int sdcc_belong[MAXN];
stack<int> sdcc_stk;
int sdcc_dfn[MAXN];
int sdcc_low[MAXN];
vector<vector<int> > sdcc;
int sdcc_cnt = 0;

void sdcc_tarjan(int cur, int par){
    sdcc_dfn[cur] = sdcc_low[cur] = sdcc_cnt++;
    sdcc_stk.push(cur);
    for (int i = 0; i < to[cur].size(); i++) {
        int nxt = to[cur][i];
        if (nxt == par) {
            continue;
        }
        if (!sdcc_dfn[nxt]) {
            //如果对面点还没有进入过，那就进去
            sdcc_tarjan(nxt, cur);
            sdcc_low[cur] = min(sdcc_low[cur], sdcc_low[nxt]);
        }else {
            //如果对面点进去过，那么考虑是不是回边，如果是的话要更新当前节点low值
            sdcc_low[cur] = min(sdcc_low[cur], sdcc_dfn[nxt]);
        }
    }
    //我们这样处理问题不会受重边影响，因为我们考虑的中心是边联通分量内部的点而非外部的割点，这样我们只需要关心当前这个点及其联通部分是不是有指向之前的点的回边就可以，只要没有回边，就说明边双联通分量已经走完了，可以收割
    if (sdcc_low[cur] == sdcc_dfn[cur]) {
        //当前节点及其联通部分没有任何指向父亲部分的回边了，可以收割和当前节点连着的所有节点为一个双联通分量了
        //generate sdcc
        int last;
        sdcc.push_back(vector<int>());
        int sdccid = (int)sdcc.size();
        do{
            last = sdcc_stk.top();
            sdcc_stk.pop();
            sdcc[sdccid-1].push_back(last);
            sdcc_belong[last] = sdccid;
        }while (cur != last);
    }
}

void get_sdcc(){
    memset(sdcc_belong, 0, sizeof(sdcc_belong));
    while (!sdcc_stk.empty()) {
        sdcc_stk.pop();
    }
    memset(sdcc_dfn, 0, sizeof(sdcc_dfn));
    memset(sdcc_low, 0, sizeof(sdcc_low));
    sdcc.clear();
    sdcc_cnt = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!sdcc_dfn[i]) {
            sdcc_tarjan(i,0);
        }
    }
}

int main(){
    scanf(" %d %d",&n, &m);
    for (int i = 1; i <= n; i++) {
        to[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        int a = 0, b = 0;
        scanf(" %d %d",&a, &b);
        add_edge(a, b);
    }
    get_sdcc();
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < to[i].size(); j++) {
            if (sdcc_belong[to[i][j]] != sdcc_belong[i]) {
                add_edge2(sdcc_belong[to[i][j]], sdcc_belong[i]);
            }
        }
    }
    remove_duplicate(to2);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (to2[i].size() == 1) {
            res++;
        }
    }
    cout << (res+1)/2 << endl;
    return 0;
}
*/
/*
 int scc_belong[MAXN];
 stack<int> scc_stk;
 bool scc_instk[MAXN];
 int scc_dfn[MAXN];
 int scc_low[MAXN];
 vector<vector<int> > scc;
 int scc_cnt = 0;
 
 void scc_tarjan(int cur){
 scc_dfn[cur] = ++scc_cnt;
 scc_low[cur] = scc_dfn[cur];
 scc_instk[cur] = true;
 scc_stk.push(cur);
 for (int i = 0; i < to[cur].size(); i++) {
 int nxt = to[cur][i];
 if (!scc_dfn[nxt]) {
 scc_tarjan(nxt);
 scc_low[cur] = min(scc_low[cur], scc_low[nxt]);
 }else if(scc_instk[nxt]){
 scc_low[cur] = min(scc_low[cur], scc_low[nxt]);
 }
 }
 if (scc_low[cur] == scc_dfn[cur]) {
 //generate scc
 int last;
 scc.push_back(vector<int>());
 int sccid = (int)scc.size();
 do{
 last = scc_stk.top();
 scc_stk.pop();
 scc_instk[last] = false;
 scc[sccid-1].push_back(last);
 scc_belong[last] = sccid;
 }while (last != cur);
 }
 }
 
 void get_scc(){
 memset(scc_belong, 0, sizeof(scc_belong));
 while (!scc_stk.empty()) {
 scc_stk.pop();
 }
 memset(scc_instk, 0, sizeof(scc_instk));
 memset(scc_dfn, 0, sizeof(scc_dfn));
 memset(scc_low, 0, sizeof(scc_low));
 scc.clear();
 scc_cnt = 0;
 for (int i = 1; i <= n; i++) {
 if (!scc_dfn[i]) {
 scc_tarjan(i);
 }
 }
 }
 */