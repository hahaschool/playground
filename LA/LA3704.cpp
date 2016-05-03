//
//  LA3704.cpp
//  playground
//
//  Created by 張正昊 on 27/4/2016.
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

const long long MAXN = 505;
long long n,m,d,k;

long long seq[MAXN],lop[MAXN];

void domod(long long &a,long long&m){
    a %= m;
    if(a < 0) a += m;
}

void mul(long long *a,long long *b,long long *c){//a*b=c
    for (long long i = 0; i < n; i++) {
        c[i] = 0;
        long long cur = i;
        for (long long j = 0; j < n; j++) {
            c[i] += a[j]*b[cur];
            domod(c[i],m);
            cur--;
            if(cur < 0) cur += n;
        }
    }
}

long long fac[MAXN],tmp[MAXN];
void pow(long long *a,long long p,long long *c){//a^p=c
    c[0] = 1,fac[0] = a[0];
    for(long long i = 1; i < n; i++){
        c[i] = 0,fac[i] = a[i];
    }
    while (p) {
        if(p&1){
            mul(c, fac, tmp);
            for (long long i = 0; i < n; i++) {
                swap(c[i], tmp[i]);
            }
        }
        mul(fac, fac, tmp);
        swap(fac, tmp);
        p >>= 1;
    }
}

void print(){
    for (long long i = 0,k = n; i < n; i++,k--) {
        long long cur = k%n,res = 0;
        for (long long j = 0; j < n; j++,cur++,cur%=n) {
            
            res += seq[j]*lop[cur];
            domod(res, m);
        }
        printf("%lld",res);
        if (i == n-1) {
            puts("");
        }else{
            putchar(' ');
        }
    }
}
long long tmp2[MAXN];
int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    while (scanf(" %lld %lld %lld %lld",&n,&m,&d,&k) != EOF) {
        for (long long i = 0; i < n; i++) {
            scanf(" %lld",&seq[i]);
        }
        memset(lop, 0, sizeof(lop));
        lop[0] = 1;
        for (long long i = 1,j = n-1; i <= d; i++,j--) {
            lop[i] = lop[j] = 1;
        }
        pow(lop, k, tmp2);
        swap(lop, tmp2);
        print();
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
