////
////  ASR1G.cpp
////  playground
////
////  Created by 張正昊 on 21/5/2016.
////  Copyright © 2016 Adam Chang. All rights reserved.
////
//
//#include <stdio.h>
//#include <iostream>
//#include <algorithm>
//#include <queue>
//#include <vector>
//#include <cstdlib>
//#include <cstdio>
//#include <string>
//#include <cstring>
//#include <ctime>
//#include <iomanip>
//#include <cmath>
//#include <set>
//#include <stack>
//#include <cmath>
//#include <map>
//#include <complex>
//
//using namespace std;
//
//const int MAXN = 100005,MAXE = 100005;
//int head[MAXN],ed[MAXE],nxt[MAXE],ind[MAXN],outd[MAXN],q;
//int n,m;
//void ade(int s,int t){
//    ed[q] = t;
//    nxt[q] = head[s];
//    head[s] = q++;
//    ind[t]++;
//    outd[s]++;
//}
//void gphclear(){
//    q = 2;
//    for (int i = 1; i <= n; i++) {
//        head[i] = ind[i] = outd[i] = 0;
//    }
//}
//
//int dp[MAXN];
//void solve(){
//    queue<int> que;
//    for (int i = 1; i <= n; i++) {
//        dp[i] = i;
//        if(ind[i] != 0 || outd[i] != 0){
//            if(ind[i] == 0){
//                que.push(i);
//            }
//        }
//    }
//    while (!que.empty()) {
//        int u = que.front();que.pop();
//        for (int i = head[u]; i; i=nxt[i]){
//            int v = ed[i];
//            dp[v] = min(dp[u],dp[v]);
//            ind[v]--;
//            if(!ind[v]){
//                que.push(v);
//            }
//        }
//    }
//    long long res = 0;
//    for (int i = 1; i <= n; i++) {
//        res += (long long)dp[i];
//    }
//    printf("%I64d\n",res);
//}
//
//int main(){
//    int caseCnt;
//    scanf(" %d",&caseCnt);
//    for (int d = 1; d <= caseCnt; d++) {
//        scanf(" %d %d",&n,&m);
//        gphclear();
//        for(int i = 1;i <= m; i++){
//            int a,b;
//            scanf(" %d %d",&a,&b);
//            ade(a,b);
//        }
//        solve();
//    }
//    
//    return 0;
//}
