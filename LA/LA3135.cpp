//
//  LA3135.cpp
//  playground
//
//  Created by 張正昊 on 14/3/2016.
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
int tot = 0;
struct Event{
    int q,t,u;
    bool operator < (const Event &b) const{
        if(t != b.t) return t > b.t;
        return q > b.q;
    }
} evt[MAXN];

priority_queue<Event> que;

int main(){
//#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r", stdin);
//#endif
    char buf[20];
    int k = 0;
    while (scanf(" %s",buf)) {
        if (buf[0] == '#') {
            scanf(" %d",&k);
            break;
        }else{
            ++tot;
            scanf(" %d %d",&evt[tot].q,&evt[tot].t);
            evt[tot].u = evt[tot].t;
        }
    }
//Not a good solution: Memory so large,can still pass UVA/LA(cuz. no ML)
//    for (int i = 1; i <= tot; i++) {
//        for(int j = 1; j <= k; j++){
//            que.push({evt[i].q,evt[i].t*j});
//        }
//    }
//    for(int i = 1; i<= k; i++){
//        printf("%d\n",que.top().q);
//        que.pop();
//    }
    
    //Consider this
    for (int i = 1; i <= tot; i++) {
        que.push({evt[i].q,evt[i].t,evt[i].u});
    }
    for (int i = 1; i <= k; i++) {
        printf("%d\n",que.top().q);
        Event ne = {que.top().q,que.top().t + que.top().u,que.top().u};
        que.pop();
        que.push(ne);
    }
    
    return 0;
}
