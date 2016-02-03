//
//  UVA11374.cpp
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

const int MAXN = 505,MAXE = 2010;
int head[MAXN],nxt[MAXE],ed[MAXE],q,cst[MAXE];
int mat[MAXN][MAXN];
int n,s,e,m,k;
const int INF = 0x3f3f3f3f;

void init(){
    q = 2;
    for(int i = 1; i <= n; i++){
        head[i] = 0;
        for(int j = 1; j <= n; j++){
            mat[i][j] = INF;
        }
        mat[i][i] = 0;
    }
}

void addEdge(int from,int to,int len){
    cst[q] = len;
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

void floyd(){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i<= n; i++){
            for(int j = 1; j <= n; j++){
                mat[i][j] = min(mat[i][j],mat[i][k]+mat[k][j]);
            }
        }
    }
}

stack<int> stk;
bool vis[MAXN];
bool printroute(int start,int dest,int cur = -1){
    if(cur == -1){
        while(!stk.empty()){
            stk.pop();
        }
        printroute(start, dest,start);
        while (!stk.empty()) {
            printf("%d",stk.top());
            if(stk.size() != 1){
                putchar(' ');
            }
            stk.pop();
        }
        return true;
    }
    vis[cur] = true;
    if(cur == dest){
        stk.push(cur);
        return true;
    }
    for(int i = head[cur];i;i = nxt[i]){
        int v = ed[i];
        if(!vis[v] && mat[start][cur] + cst[i] == mat[start][v]){
            if(printroute(start, dest,v)){
                stk.push(cur);
                return true;
            }
        }
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while(scanf(" %d %d %d",&n,&s,&e) != EOF){
        init();
        if(caseCnt++){
            puts("");
        }
        scanf(" %d",&m);
        for(int i = 1; i <= m; i++){
            int a,b,c;
            scanf(" %d %d %d",&a,&b,&c);
            addEdge(a,b,c);
            addEdge(b,a,c);
            mat[a][b] = min(mat[a][b],c);
            mat[b][a] = min(mat[a][b],c);
        }
        floyd();
        scanf(" %d",&k);
        int ans = mat[s][e];
        bool via = false;
        int via_a = -1,via_b = -1,via_c = -1;
        for(int i = 1; i<=k;i++){
            int a,b,c;
            scanf(" %d %d %d",&a,&b,&c);
            if(mat[s][a] + c + mat[b][e] < ans){
                ans = mat[s][a] + c + mat[b][e];
                via_a = a,via_b = b,via_c = c;
                via = true;
            }
            //ISSUE: Only dealt with unidirectional
            if(mat[s][b] + c + mat[a][e] < ans){
                ans = mat[s][b] + c + mat[a][e];
                via_a = b,via_b = a,via_c = c;
                via = true;
            }
        }
        
        if(via){
            memset(vis, 0, sizeof(vis));
            printroute(s,via_a);
            putchar(' ');
            //ISSUE: should clear vis again here!
            //reason: if you visited some node in the first round,then pass the via edge,then you may be unable to visit some node visited but not selected in the first round.
            memset(vis, 0, sizeof(vis));
            printroute(via_b,e);
            printf("\n%d\n%d\n",via_a,ans);
        }else{
            memset(vis, 0, sizeof(vis));
            printroute(s,e);
            puts("\nTicket Not Used");
            printf("%d\n",ans);
        }
        
    }
    
    return 0;
}



