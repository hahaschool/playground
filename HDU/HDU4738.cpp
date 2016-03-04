//
//  HDU4738.cpp
//  playground
//
//  Created by 張正昊 on 18/8/15.
//  Copyright (c) 2015 Adam Chang. All rights reserved.
//

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

#define MAXN 1005
#define MAXE 2000005

struct EDGE
{
    int u, v, w;
    int next;
};

int first[MAXN], rear;
EDGE edge[MAXE];

void init(int n)
{
    memset(first, -1, sizeof(first[0])*(n+1));
    rear = 0;
}

void insert(int tu, int tv, int tw)
{
    edge[rear].u = tu;
    edge[rear].v = tv;
    edge[rear].w = tw;
    edge[rear].next = first[tu];
    first[tu] = rear++;
    edge[rear].u = tv;
    edge[rear].v = tu;
    edge[rear].w = tw;
    edge[rear].next = first[tv];
    first[tv] = rear++;
}


int pre[MAXN], low[MAXN];
bool vis_e[MAXE];      //是否访问了边
bool is_bridge[MAXE];  //是否是桥
int dfs_clock;
int res = 909303;
void dfs(int cur)
{
    pre[cur] = low[cur] = ++dfs_clock;
    for(int i = first[cur]; ~i; i = edge[i].next)
    {
        //便利以当前点出发的所有边
        int tv = edge[i].v;
        if(!pre[tv])
        {
            //如果这条边连接着的节点还没有访问过，那就进到这个节点里面
            vis_e[i] = vis_e[i^1] = true;
            dfs(tv);
            low[cur] = min(low[cur], low[tv]);
            if(pre[cur] < low[tv]){
                //当前边连着的这个节点处理完毕了，如果发现这个节点的low值还是比当前节点大，说明这个节点及其联通部分没有指向已访问任何节点的回边，也就是说割开当前这条边，这个节点以及其联通的部分就和当前节点裂开了，这条边也就理所当然的是割边
                is_bridge[i] = is_bridge[i^1] = true;
                res = min(res,edge[i].w);//更新答案用的
            }
        }
        else
            if(pre[tv] < pre[cur] && !vis_e[i])
            {
                //这里是如果当前这条边是一条回边，那么就要更新当前节点的low值了
                vis_e[i] = vis_e[i^1] = true;
                low[cur] = min(low[cur], pre[tv]);
            }
    }
}

void find_bridge(int n)
{
    res = 909303;
    dfs_clock = 0;
    memset(pre, 0, sizeof(pre[0])*(n+1));
    memset(vis_e, 0, sizeof(vis_e[0])*rear);
    memset(is_bridge, 0, sizeof(is_bridge[0])*rear);
    dfs(1);
}

int main(){
    int n = 0,m = 0;
    while (scanf(" %d %d",&n,&m) != EOF) {
        if (n == 0 && m == 0) {
            break;
        }
        init(n);
        for (int i = 1; i <= m; i++) {
            int u = 0,v = 0,w = 0;
            scanf(" %d %d %d",&u,&v,&w);
            insert(u, v, w);
        }
        find_bridge(n);
        if (dfs_clock < n) {
            cout << 0 << endl;
        }else if (res == 909303) {
            cout << -1 << endl;
        }else if(res == 0){
            cout << 1 << endl;
        }else {
            cout << res << endl;
        }
    }
}
