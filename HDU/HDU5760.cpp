//
//  HDU5760.cpp
//  playground
//
//  Created by 張正昊 on 27/7/2016.
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

const int MAXN = 5005,MAXVAL = 20005;
int n;
int seq[MAXN],dsc[MAXVAL];
set<int> st;
typedef int LL;
const LL MODER = 1000000007;
LL nxt[MAXN],prv[MAXN];
LL dp_len[MAXN][MAXN],dp_cnt[MAXN][MAXN];


void solve(){
    for (int i = n; i >= 1; i--) {
        memset(prv, -1, sizeof(prv));
        memset(nxt, -1, sizeof(nxt));
        dp_len[i][i] = dp_cnt[i][i] = 1;
        int can_len = 0,can_cnt = 1;
        for (int j = i+1; j <= n; j++) {
            if(seq[i] == seq[j]){
                dp_len[i][j] = can_len+2;
                dp_cnt[i][j] = can_cnt;
            }
            if(seq[j] <= seq[i]){
                if(nxt[seq[j]] == -1) nxt[seq[j]] = j;
                int ppv = prv[seq[j]];prv[seq[j]] = j;
                if(dp_len[nxt[seq[j]]][prv[seq[j]]] > can_len){
                    can_len = dp_len[nxt[seq[j]]][prv[seq[j]]];
                    can_cnt = dp_cnt[nxt[seq[j]]][prv[seq[j]]];
                }else if(dp_len[nxt[seq[j]]][prv[seq[j]]] == can_len){
                    if(ppv != -1 && dp_len[nxt[seq[j]]][ppv] == can_len){
                        can_cnt -= dp_cnt[nxt[seq[j]]][ppv];
                        if(can_cnt < 0) can_cnt += MODER;
                    }
                    can_cnt += dp_cnt[nxt[seq[j]]][prv[seq[j]]];
                    if(can_cnt >= MODER) can_cnt -= MODER;
                }
            }
        }
    }
    
    int res_len = 0,res_cnt = 0;
    for(int i = 1;i <= *max_element(st.begin(), st.end());i++){
        int nxt,prv;
        for(nxt = 1;nxt <= n; nxt++){
            if(seq[nxt] == i){
                break;
            }
        }
        for(prv = n;prv >= 1; prv--){
            if(seq[prv] == i){
                break;
            }
        }
        if(dp_len[nxt][prv] > res_len){
            res_len = dp_len[nxt][prv];
            res_cnt = dp_cnt[nxt][prv];
        }else if(dp_len[nxt][prv] == res_len){
            res_cnt += dp_cnt[nxt][prv];
            if(res_cnt >= MODER) res_cnt -= MODER;
        }
    }
    
    printf("%d %d\n",res_len,res_cnt);
    
}

template <class T>
inline void scan_d(T &ret) {
    char c; ret=0;
    while((c=getchar())<'0'||c>'9');
    while(c>='0'&&c<='9') ret=ret*10+(c-'0'),c=getchar();
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    while(scanf(" %d",&n) != EOF){
        st.clear();
        int i = 1;
        for(i = 1;i <= n; i++){
            scan_d(seq[i]);
            st.insert(seq[i]);
        }
        i = 1;
        for(set<int>::iterator it = st.begin();it != st.end();it++,i++){
            dsc[*it] = i;
        }
        for(i = 1;i <= n; i++){
            seq[i] = dsc[seq[i]];
        }
        solve();
    }
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}