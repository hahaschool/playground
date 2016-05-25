////
////  ASR1D.cpp
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
//long long N[66];
//long long solve(long long l,long long r,long long cl = -1,long long cr = -1,long long mid = -1,int rnk = -1,int cur = -1){
//    if(cl == -1){
//        return solve(l,r,1,(1LL<<60LL)-1LL,(1LL<<59LL),59,1);
//    }
//    if(cl == l && cr == r){
//        return N[rnk] + cur;
//    }
//    if (l <= mid && r >= mid) {
//        long long ret = cur;
//        if(mid > l){
//            ret += solve(l,mid-1LL,cl,mid-1LL,(cl+mid-1LL)>>1LL,rnk-1,1);
//        }
//        if(mid < r){
//            ret += solve(mid+1LL,r,mid+1LL,cr,(cr+mid+1LL)>>1LL,rnk-1,0);
//        }
//        return ret;
//    }else{
//        long long ret = 0;
//        if (mid > r) {
//            ret += solve(l, r, cl,mid-1LL,(cl+mid-1LL)>>1LL,rnk-1,1);
//        }
//        if (mid < l){
//            ret += solve(l,r,mid+1LL,cr,(cr+mid+1LL)>>1LL,rnk-1,0);
//        }
//        if(mid == l || mid == r){
//            ret += cur;
//        }
//        return ret;
//    }
//}
//
//int main(){
//    int caseCnt;
//    scanf(" %d",&caseCnt);
//    N[0] = 0;
//    for (int i = 1; i <= 60; i++) {
//        N[i] = N[i-1] + N[i-1] + 1;
//    }
//    for (int d = 1;d <= caseCnt; d++) {
//        long long a,b;
//        scanf(" %I64d %I64d",&a,&b);
//        printf("%I64d\n",solve(a, b));
//    }
//    return 0;
//}
