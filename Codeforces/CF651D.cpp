//
//  CF651D.cpp
//  playground
//
//  Created by 張正昊 on 7/3/2016.
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

const int MAXN = 500005;
long long dir[MAXN];//1 for hori, 0 for vect
long long n,a,b,t;//number walk rotate time
long long cstsum[MAXN*2];



bool judge(int len){
    int startpos = n - len + 2;
    int endpos = n+1;
    long long ltr = len - 1;
    long long rtr = 0;
    for(int i = startpos;i <= endpos; i++){
        long long curt = cstsum[i + len - 1] - cstsum[i-1];
        curt += (ltr+rtr)*a;
        curt += min(ltr,rtr)*a;
        if (curt <= t) {
            return true;
        }
        ltr--,rtr++;
    }
    return false;
}

void prep(){
    for(int i = 1; i<= n; i++){
        cstsum[i] = cstsum[i+n] = 1+b*dir[i];
    }
    for(int i = 1; i <= 2*n; i++){
        cstsum[i] = cstsum[i-1] + cstsum[i];
    }
}

void solve(){
    prep();
    int l = 1,r = n,mid;
    while (l + 1 < r) {
        mid = l + (r-l)/2;
        if (judge(mid)) {
            l = mid;
        }else{
            r = mid-1;
        }
    }
    if (judge(r)) {
        printf("%d\n",r);
    }else if(judge(l)){
        printf("%d\n",l);
    }else{
        puts("0");
    }
}

int main(){
    cin >> n >> a >> b >> t;
    for(int i = 1; i<= n; i++){
        char q;
        scanf(" %c",&q);
        if (q == 'w') {
            dir[i] = 1;
        }else{
            dir[i] = 0;
        }
    }
    solve();
    
    return 0;
}