//
//  POJ3685.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/12.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

/*
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

inline long long f(long long i,long long j){
    return i*i+j*j+100000*i+i*j-100000*j;
}
bool ok(long long MID,long long n,long long m){
    long long cnt = 0;
    for (int j = 1; j <= n; j++) {
        long long high = n+1,low = 1,mid = (n+2)/2;
        while (high > low) {
            
            if (f(mid,j) >= MID) {
                high = mid;
            }else{
                low = mid+1;
            }
            mid = (high+low)>>1;
        }
        cnt += mid-1;
    }
    return cnt >= m;
}


int main(){
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for (int xi = 1;xi <= caseCnt; xi++) {
        long long n = 0,m = 0;
        scanf(" %lld %lld",&n,&m);
        long long high = 1e12,low = -1e12,mid = 0;
        
        while (high > low) {
            if (ok(mid,n,m)) {
                high = mid;
            }else{
                low = mid+1;
            }
            mid = (high+low)>>1;
        }
        printf("%lld\n",mid-1);
    }
    return 0;
    
}
*/