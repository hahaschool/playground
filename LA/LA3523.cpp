//
//  LA3523.cpp
//  playground
//
//  Created by 張正昊 on 21/1/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <algorithm>
#include <cmath>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 1005, MAXE = 4000006;
int mat[MAXN][MAXN];
int ed[MAXE], nxt[MAXE], head[MAXN], q;
int n, m;
void gph_clear()
{
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }
    q = 2;
}
void gph_addEdge(int from, int to)
{
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

int pre[MAXN], dfn, bccid[MAXN];
bool isCut[MAXN];
struct Edge {
    int u, v;
    Edge(int a, int b)
    {
        u = a, v = b;
    }
};
vector<vector<int> > bcc;
stack<Edge> tmpstk;
int bcc_dfs(int u, int par)
{
    int lowu = pre[u] = ++dfn;
    int child = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ed[i];
        if (!pre[v]) {
            child++;
            tmpstk.push(Edge(u, v));
            int lowv = bcc_dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv >= pre[u]) {
                //articulation happened
                isCut[u] = true;
                bcc.push_back(vector<int>());
                while (true) {
                    Edge x = tmpstk.top();
                    tmpstk.pop();
                    if (bccid[x.u] != bcc.size() - 1) {
                        bcc[bcc.size() - 1].push_back(x.u);
                        bccid[x.u] = (int)bcc.size() - 1;
                    }
                    if (bccid[x.v] != bcc.size() - 1) {
                        bcc[bcc.size() - 1].push_back(x.v);
                        bccid[x.v] = (int)bcc.size() - 1;
                    }
                    if (x.u == u && x.v == v) {
                        break;
                    }
                }
            }
        }
        else if (pre[v] < pre[u] && v != par) {
            tmpstk.push(Edge(u, v));
            lowu = min(lowu, pre[v]);
        }
    }
    if (par < 0 && child == 1)
        isCut[u] = 0;
    return lowu;
}
void bcc_get()
{
    dfn = 0;
    bcc.clear();
    for (int i = 1; i <= n; i++) {
        pre[i] = 0;
        isCut[i] = false;
        bccid[i] = -1;
    }
    for (int i = 1; i <= n; i++) {
        if (!pre[i]) {
            bcc_dfs(i, -1);
        }
    }
}

int color[MAXN];
bool bip_tent(int u)
{
    for (int i = 1; i <= n; i++) {
        color[i] = 0;
    }
    queue<int> que;
    que.push(u);
    color[u] = 1;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ed[i];
            if (!color[v]) {
                color[v] = -color[u];
                que.push(v);
            }
            else {
                if (color[v] + color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void build_gph()
{
    gph_clear();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (mat[i][j]) {
                gph_addEdge(i, j);
            }
        }
    }
}
bool mkr[MAXN];
void solve()
{
    build_gph();
    bcc_get();
    int res = 0;
    for (int i = 1; i <= n; i++) {
        mkr[i] = false;
    }
    for (int i = 0; i < bcc.size(); i++) {
        gph_clear();
        for (int j = 0; j < bcc[i].size(); j++) {
            for (int k = 0; k < bcc[i].size(); k++) {
                if (mat[bcc[i][j]][bcc[i][k]]) {
                    gph_addEdge(bcc[i][j], bcc[i][k]);
                }
            }
        }
        if (!bip_tent(bcc[i][0])) {
            for (int j = 0; j < bcc[i].size(); j++) {
                mkr[bcc[i][j]] = true;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!mkr[i]) {
            res++;
        }
    }
    printf("%d\n", res);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif

    while (scanf(" %d %d", &n, &m) != EOF) {
        if (n == 0 && m == 0) {
            break;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                mat[i][j] = 1;
            }
            mat[i][i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf(" %d %d", &a, &b);
            mat[a][b] = 0;
            mat[b][a] = 0;
        }
        solve();
    }
    return 0;
}