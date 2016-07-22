//
//  HDU5731.cpp
//  playground
//
//  Created by 張正昊 on 20/7/2016.
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

const int N = 16;
typedef long long LL;
const LL MODER = 1000000007;
map<int,LL> tab[2];
LL cnt[N+1][N+1];
LL res[N+1][N+1];
inline int lg2(int x){
    return !x ? -1 : 31 - __builtin_clz(x);
}
inline int lowbit(int x){
    return x&(-x);
}
void prep(){
    for (int i = 1; i <= N; i++) {
        tab[0].clear();
        tab[1].clear();
        int p = 0,q = 1;
        tab[p][0] = 1;
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k < i; k++) {
                swap(p, q);
                tab[p].clear();
                for (map<int,LL>::iterator it = tab[q].begin(); it != tab[q].end(); it++) {
                    int s = it->first;
                    LL d = it->second;
                    if(k && !(s&(1<<k)) && (s&(1<<(k-1)))) {
                        tab[p][s^(1<<(k-1))] += d%MODER;
                        tab[p][s^(1<<(k-1))] %= MODER;
                    }
                    tab[p][s^(1<<k)] += d%MODER;
                    tab[p][s^(1<<k)] %= MODER;
                }
            }
            cnt[j][i] = cnt[i][j] = tab[p][0];
        }
    }
    
    
    for (int i = 1; i <= N; i++) {
        for (int msk = 0; msk < (1<<(i-1)); msk++) {
            LL subcnt_all[N+1],subcnt_safe[N+1];
            for (int j = 1; j <= i; j++) {
                subcnt_all[j] = 1;
                int p = -1,mk = msk;
                mk |= 1<<(i-1);
                while (mk) {
                    int t = lowbit(mk);
                    mk ^= t;
                    t = lg2(t);
                    subcnt_all[j] *= cnt[j][t-p];
                    subcnt_all[j] %= MODER;
                    p = t;
                }
            }
            for (int j = 1; j <= i; j++) {
                subcnt_safe[j] = subcnt_all[j];
                for (int k = 1; k <= j-1; k++) {
                    subcnt_safe[j] -= subcnt_safe[k]*subcnt_all[j-k];
                    subcnt_safe[j] %= MODER;
                }
                if(__builtin_popcount(msk)&1) {
                    res[i][j] -= subcnt_safe[j];
                    if(i != j)res[j][i] -= subcnt_safe[j];
                    res[i][j] %= MODER,res[j][i] %= MODER;
                }
                else {
                    res[i][j] += subcnt_safe[j];
                    if(i != j)res[j][i] += subcnt_safe[j];
                    res[i][j] %= MODER,res[j][i] %= MODER;
                }
            }
        }
    }
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prep();
    int a,b;
    while (scanf(" %d %d",&a,&b) != EOF) {
        cout << (res[a][b]+MODER)%MODER << endl;
    }
    
#ifndef ONLINE_JUDGE
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
