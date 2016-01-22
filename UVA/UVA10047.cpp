//
//  10047.cpp
//  playground
//
//  Created by 張正昊 on 21/1/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

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

const int MAXN = 30;
int n,m;
char board[MAXN][MAXN];

bool isValid(int y,int x){
    if(y < 1 || y > n || x < 1 || x > m || board[y][x] == '#'){
        return false;
    }
    return true;
}


int dis[MAXN][MAXN][5][4];//dis[y][x][wheel(01234)][dir(ULDR)]
int dir[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};//ULDR
int Ty = -1,Tx = -1,Sy = -1,Sx = -1;
inline int tl(int dir){
    return ((dir + 1)%4+4)%4;
}
inline int tr(int dir){
    return ((dir - 1)%4+4)%4;
}
inline int fwd(int whl){
    return ((whl + 1)%5+5)%5;
}

struct State{
    int y,x,w,d;
    State(int _y,int _x,int _w,int _d){
        y = _y;
        x = _x;
        w = _w;
        d = _d;
    }
};
int solve(){
    queue<State> que;
    que.push(State(Sy,Sx,0,0));
    memset(dis, 0x3f, sizeof(dis));
    dis[Sy][Sx][0][0] = 0;
    while (!que.empty()) {
        State cur = que.front();
        que.pop();
        //attempting turn left
        if(dis[cur.y][cur.x][cur.w][tl(cur.d)] > dis[cur.y][cur.x][cur.w][cur.d] + 1){
            dis[cur.y][cur.x][cur.w][tl(cur.d)] = dis[cur.y][cur.x][cur.w][cur.d] + 1;
            que.push(State(cur.y,cur.x,cur.w,tl(cur.d)));
        }
        
        //attempting turn right
        if(dis[cur.y][cur.x][cur.w][tr(cur.d)] > dis[cur.y][cur.x][cur.w][cur.d] + 1){
            dis[cur.y][cur.x][cur.w][tr(cur.d)] = dis[cur.y][cur.x][cur.w][cur.d] + 1;
            que.push(State(cur.y,cur.x,cur.w,tr(cur.d)));
        }
        
        //attempting go straight
        int ny = cur.y + dir[cur.d][0];
        int nx = cur.x + dir[cur.d][1];
        if(isValid(ny, nx) && dis[ny][nx][fwd(cur.w)][cur.d] > dis[cur.y][cur.x][cur.w][cur.d] + 1){
            dis[ny][nx][fwd(cur.w)][cur.d] = dis[cur.y][cur.x][cur.w][cur.d] + 1;
            que.push(State(ny, nx, fwd(cur.w), cur.d));
        }
    }
    int ret = 0x3f3f3f3f;
    for(int i = 0; i < 4; i++){
        ret = min(ret, dis[Ty][Tx][0][i]);
    }
    return ret;
    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while(scanf(" %d %d",&n,&m) != EOF){
        if(!n && !m){
            break;
        }
        if(caseCnt){
            puts("");
        }
        printf("Case #%d\n",++caseCnt);
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                scanf(" %c",&board[i][j]);
                if(board[i][j] == 'S'){
                    Sy = i,Sx = j;
                }
                if(board[i][j] == 'T'){
                    Ty = i,Tx = j;
                }
            }
        }
        int res = solve();
        if(res == 0x3f3f3f3f){
            puts("destination not reachable");
        }else{
            printf("minimum time = %d sec\n",res);
        }
    }
    return 0;
}

