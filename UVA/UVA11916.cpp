//
//  UVA11916.cpp
//  playground
//
//  Created by 張正昊 on 17/4/2016.
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

#pragma mark - Extended Baby-Step-Gaint-Step Algorithm (exBSGS)

struct Hashtable{//Mod Based Hash Table
    static const int HASHMOD = 1200611;//A Prime
    long long top, hash[HASHMOD+100], value[HASHMOD+100], stk[1 << 16];
    int locate(const long long x){
        int h = x % HASHMOD;
        while(hash[h] != -1 && hash[h] != x){
            h++;
        }
        return h;
    }
    void insert(const long long key,const long long val){
        int h = locate(key);
        if(hash[h] == -1){
            hash[h] = key;
            value[h] = val;
            stk[++top] = h;
        }
    }
    long long find(const long long key){
        int h = locate(key);
        return (hash[h] == key)?value[h]:-1;
    }
    void clear(){
        while(top){
            hash[stk[top--]] = -1;
        }
    }
    Hashtable(){
        top = 0;
        memset(hash, -1, sizeof(hash));
    }
} hashtab;

struct Triple{
    long long x,y,z;
    Triple(const long long _x,const long long _y,const long long _z){
        x = _x;
        y = _y;
        z = _z;
    }
    Triple(){
        x = y = z = 0;
    }
};

Triple exgcd(const long long a,const long long b){
    //for inv use(A/B % C):let a = B,b = C,return.x = inv,return.z = gcd
    //for solve use:return.x = specx,return.y = specy,returnz = gcd
    if (b == 0) {
        return Triple(1,0,a);
    }
    Triple last = exgcd(b, a%b);
    return Triple(last.y, last.x - a / b * last.y, last.z);
}

long long exBSGS(long long A,long long B,long long C){
    //A^x=B(mod C)
    //Ensure B is legal
    B %= C;
    if (B < 0) {
        B += C;
    }
    //Procceed A,B,C to normal BSGS if C is not prime
    long long tmp = 1 % C, cnt = 0, D = 1 % C;
    for (int i = 0; i < 64; i++) {
        if (tmp == B) {
            return i;
        }
        tmp = tmp * A % C;
    }
    
    for (Triple res; (res = exgcd(A, C)).z != 1; cnt++) {
        if (B % res.z) {
            return -1;
        }
        B /= res.z;
        C /= res.z;
        D = D * A / res.z % C;
    }
    //Normal BSGS
    long long sqrtn = (long long)(ceil(sqrt(C)));
    hashtab.clear();
    long long base = 1 % C;
    for (int i = 0; i < sqrtn; i++) {
        hashtab.insert(base, i);
        base = base * A % C;
    }
    long long j = -1,i = 0;
    for (; i < sqrtn; i++) {
        Triple res = exgcd(D, C);
        long long c = C / res.z;
        res.x = (res.x * B/res.z % c + c) % c;
        j = hashtab.find(res.x);
        if (j != -1) {
            return i * sqrtn + j + cnt;
        }
        D = D * base % C;
    }
    return -1;
}


#pragma mark -

const long long MODER = 100000007;

long long mul_mod(long long a,long long b, long long m){
    long long ret = (a*b)%m;
    if (ret < 0) {
        ret += m;
    }
    return ret;
}

long long pow_mod(long long a,long long p,long long m){
    long long cp = p,fac = a,ret = 1;
    while (cp) {
        if(cp & 1){
            ret = mul_mod(ret, fac, m);
        }
        fac = mul_mod(fac, fac, m);
        cp >>= 1;
    }
    return ret;
}

long long N,K,B,R,M;
struct Block{
    long long n,m;//n is col,m is row
    bool operator < (const Block &b) const{
        if(n != b.n) return n < b.n;
        return m < b.m;
    }
} blk[505];

long long segment(long long len){
    if (len <= 0) {
        return 1;
    }
    return mul_mod(pow_mod(K-1, len-1, MODER), K, MODER);
}

long long inv(long long a,long long m){
    return pow_mod(a, m-2, m);
}

long long solve(){
    long long preset = 1;
    sort(blk+1, blk+1+B);
    blk[B+1] = {N,M+1LL};
    long long cur = 1,prv = 0;
    for (int i = 1; i <= B+1; i++) {
        if (blk[i].n != cur) {
            preset = mul_mod(segment(M - prv), preset, MODER);
            preset = mul_mod(pow_mod(segment(M), blk[i].n - cur - 1, MODER), preset, MODER);
            preset = mul_mod(segment(blk[i].m-1), preset, MODER);
            cur = blk[i].n,prv = blk[i].m;
        }else{
            preset = mul_mod(segment(blk[i].m - prv - 1), preset, MODER);
            prv = blk[i].m;
        }
    }
    if (preset == R) {
        return M;
    }
    long long common = N,rare = 1;
    for (int i = 1; i <= B; i++) {
        if (blk[i].m == M) {
            common--;
            rare = mul_mod(rare, K, MODER);
        }
    }
    if (B) {
        preset = mul_mod(mul_mod(pow_mod(K-1, common, MODER), rare, MODER), preset, MODER);
    }else{
        preset = mul_mod(mul_mod(pow_mod(K, common, MODER), rare, MODER), preset, MODER);
    }
    M++;
    if (preset == R) {
        return M;
    }
    R = mul_mod(inv(preset,MODER), R, MODER);
    long long P = pow_mod(K-1, N, MODER);
    M += exBSGS(P, R, MODER);
    return M;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt;d++){
        scanf(" %lld %lld %lld %lld",&N,&K,&B,&R);
        M = 0;
        for (int i = 1; i <= B; i++) {
            scanf(" %lld %lld",&blk[i].m,&blk[i].n);
            M = max(M,blk[i].m);
        }
        printf("Case %d: %lld\n",d,solve());
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

