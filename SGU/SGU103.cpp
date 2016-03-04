//
//  SGU103.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/16.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
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

using namespace std;

int str = 0,ter = 0;
int n = 0,m = 0;

struct edgeType{
    int to;
    int cost;
    edgeType(){
        to = 0;
        cost = 0;
    }
    edgeType(int ito,int icost){
        to = ito;
        cost = icost;
    }
};

struct vertexType{
    char color;
    int init;
    int blue;
    int purple;
    int pre;//for backtracking
    int dis;
    vector<edgeType> edge;
    vertexType(){
        color = 0;
        init = 0;
        blue = 0;
        purple = 0;
        pre = 0;
        dis = 0x3f3f3f3f;
        edge.clear();
    }
} vertex[305];

char getColor(int timepast,int a){
    vertexType &av = vertex[a];
    int atime = (timepast % (av.blue+av.purple)) - av.init;
    if (av.color == 'P') {
        if (atime < 0) {
            return 'P';
        }else if(atime < av.blue){
            return 'B';
        }else{
            return 'P';
        }
    }else{
        if (atime < 0) {
            return 'B';
        }else if(atime < av.purple){
            return 'P';
        }else{
            return 'B';
        }
    }
}
char getTime(int timepast,int a){
    vertexType &av = vertex[a];
    int atime = (timepast %(av.blue+av.purple)) - av.init;
    if (av.color == 'P') {
        if (atime < 0) {
            return -atime;
        }else if(atime < av.blue){
            return av.blue-atime;
        }else{
            return av.blue+av.purple-atime;
        }
    }else{
        if (atime < 0) {
            return -atime;
        }else if(atime < av.purple){
            return av.purple-atime;
        }else{
            return av.blue+av.purple-atime;
        }
    }
}

int waitTime(int a,int b){
    //from a to b
    vertexType &av = vertex[a];
    vertexType &bv = vertex[b];
    int atime = getTime(av.dis, a);
    int btime = getTime(av.dis, b);
    char acolor = getColor(av.dis,a);
    char bcolor = getColor(av.dis,b);
    if (acolor == bcolor) {
        return 0;
    }
    if (abs(atime - btime)) {
        return min(atime,btime);
    }else if(acolor == 'P'){
        if (abs(av.blue-bv.purple)) {
            return atime+min(av.blue,bv.purple);
        }else if(abs(av.purple-bv.blue)){
            return atime+av.blue+min(av.purple,bv.blue);
        }else{
            return -1;
        }
    }else if(acolor == 'B'){
        if (abs(av.purple-bv.blue)) {
            return atime+min(av.purple,bv.blue);
        }else if(abs(av.blue-bv.purple)){
            return atime+av.purple+min(av.blue,bv.purple);
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}

struct cmp{
    bool operator () (int a,int b){
        return vertex[a].dis > vertex[b].dis;
    }
};

void dijkstra(){
    vertex[str].dis = 0;
    priority_queue<int,vector<int>,cmp> q;
    q.push(str);
    bool vis[305];
    memset(vis, 0, sizeof(vis));
    while (!q.empty()) {
        int nown = q.top();
        q.pop();
        vis[nown] = true;
        vertexType &nowv = vertex[nown];
        for (int i = 0; i < nowv.edge.size(); i++) {
            int nextn = nowv.edge[i].to;
            vertexType &nextv = vertex[nextn];
            if (vis[nextn]) {
                continue;
            }
            int wait = waitTime(nown,nextn);
            if (wait == -1) {
                continue;
            }
            if (wait + nowv.dis + nowv.edge[i].cost < nextv.dis) {
                //relax
                nextv.dis = wait + nowv.dis + nowv.edge[i].cost;
                nextv.pre = nown;
                q.push(nextn);
            }
        }
    }
    
}



int main(){
    scanf(" %d %d %d %d",&str,&ter,&n,&m);
    for (int i = 1; i <= n; i++) {
        scanf(" %c %d %d %d",&vertex[i].color,&vertex[i].init,&vertex[i].blue,&vertex[i].purple);
    }
    for (int i = 1; i <= m; i++) {
        int a = 0,b = 0,c = 0;
        scanf(" %d %d %d",&a,&b,&c);
        vertex[a].edge.push_back(edgeType(b,c));
        vertex[b].edge.push_back(edgeType(a,c));
    }
    dijkstra();
    if (vertex[ter].dis == 0x3f3f3f3f) {
        printf("0\n");
        return 0;
    }
    printf("%d\n",vertex[ter].dis);
    stack<int> path;
    int curr = ter;
    while (curr) {
        path.push(curr);
        curr = vertex[curr].pre;
    }
    while (path.size()>1) {
        printf("%d ",path.top());
        path.pop();
    }
    printf("%d\n",path.top());
    path.pop();
    
    return 0;
}

