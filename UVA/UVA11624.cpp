//
//  UVA11624.cpp
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

const int MAXN = 1005;
const int dir4[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int n,m;
char board[MAXN][MAXN];
int fire[MAXN][MAXN];

bool isIn(int y,int x){
    if(y < 1 || y > n || x < 1 || x > m){
        return false;
    }
    return true;
}

bool isValid(int y,int x){
    if(y < 1 || y > n || x < 1 || x > m || board[y][x] == '#'){
        return false;
    }
    return true;
}

void preProc(){
    memset(fire, 0x3f, sizeof(fire));
    queue<pair<int, int> > que;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(board[i][j] == 'F'){
                fire[i][j] = 0;
                que.push(make_pair(i, j));
            }
        }
    }
    while (!que.empty()) {
        int cy = que.front().first,cx = que.front().second;
        que.pop();
        for(int i = 0; i < 4 ; i++){
            int ny = cy + dir4[i][0];
            int nx = cx + dir4[i][1];
            if(isValid(ny,nx) && fire[ny][nx] > fire[cy][cx] + 1){
                fire[ny][nx] = fire[cy][cx] + 1;
                que.push(make_pair(ny, nx));
            }
        }
    }
}

int vis[MAXN][MAXN];

int solve(){
    preProc();
    memset(vis, 0x3f, sizeof(vis));
    queue<pair<int, int> > que;
    for(int i = 1; i<= n; i++){
        int j = 1;
        for(; j<= n; j++){
            if(board[i][j] == 'J'){
                que.push(make_pair(i, j));
                vis[i][j] = 0;
                break;
            }
        }
        if(j != n+1){
            break;
        }
    }
    
    while(!que.empty()){
        int cy = que.front().first,cx = que.front().second;
        que.pop();
        for(int i = 0; i < 4 ; i++){
            int ny = cy + dir4[i][0];
            int nx = cx + dir4[i][1];
            if(isIn(ny, nx)){
                if(isValid(ny,nx) && vis[ny][nx] > vis[cy][cx] + 1 && vis[cy][cx] + 1 < fire[ny][nx]){
                    vis[ny][nx] = vis[cy][cx] + 1;
                    que.push(make_pair(ny, nx));
                }
            }else{
                return vis[cy][cx] + 1;
            }
        }
    }
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt;d++){
        scanf(" %d %d",&n,&m);
        memset(board, 0, sizeof(board));
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                scanf(" %c",&board[i][j]);
            }
        }
        int res = solve();
        if(res == -1){
            puts("IMPOSSIBLE");
        }else{
            printf("%d\n",res);
        }
    }
    return 0;
}