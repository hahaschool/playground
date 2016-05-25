////
////  ASR1B.cpp
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
//const int MAXN = 17;
//int stat[MAXN];
//bool mkr[MAXN];
//vector<int> dyn;
//int N;
//int check(){
//    int cur = 0;
//    int tmp[MAXN];
//    for (int i = 0; i < N; i++) {
//        if (mkr[i]) {
//            tmp[i] = stat[i];
//        }else{
//            tmp[i] = dyn[cur++];
//        }
//    }
//    int ret = 0;
//    for (int i = 1; i < N; i++) {
//        ret += tmp[i]*tmp[i-1];
//    }
//    return ret;
//}
//
//void solve(){
//    int ret = -0x3f3f3f3f;
//    sort(dyn.begin(), dyn.end());
//    ret = max(check(),ret);
//    while (next_permutation(dyn.begin(), dyn.end())) {
//        ret = max(check(),ret);
//    }
//    ret = max(check(),ret);
//    printf("%d\n",ret);
//}
//
//
//int main(){
//#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r", stdin);
//    clock_t clk = clock();
//#endif
//    
//
//    int caseCnt;
//    scanf(" %d",&caseCnt);
//    for (int d = 1; d <= caseCnt; d++) {
//        printf("Case #%d:\n",d);
//        scanf(" %d",&N);
//        memset(stat, 0, sizeof(stat));
//        memset(mkr, 0, sizeof(mkr));
//        dyn.clear();
//        for (int i = 1; i <= N; i++) {
//            int a,b;
//            scanf(" %d %d",&a,&b);
//            if(b == -1){
//                dyn.push_back(a);
//            }else{
//                stat[b] = a;
//                mkr[b] = true;
//            }
//        }
//        solve();
//    }
//#ifndef ONLINE_JUDGE
//    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
//#endif
//
//    return 0;
//}
