//
//  LA7274.cpp
//  playground
//
//  Created by 張正昊 on 30/8/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

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

const int MAXN = 100005;
int seq[MAXN];
int n;
priority_queue<LL,vector<LL>,greater<LL> > que;

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    CASE_LOOP{
        scanf(" %d",&n);
        while(que.size()) que.pop();
        REP_1(i, n){
            scanf(" %d",&seq[i]);
            que.push(seq[i]);
        }
        LL res = 0;
        while(que.size() > 1){
            LL a = que.top();que.pop();
            LL b = que.top();que.pop();
            que.push(a+b);
            res += a+b;
        }
        printf("%lld\n",res);
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
