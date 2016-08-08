
//
//  HDU5801.cpp
//  playground
//
//  Created by 張正昊 on 8/8/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
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

using namespace std;

#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_1(i,t) for(int i = 1;i <= t; i++)

typedef long long LL;

const int MAXN = 100005;
char str[MAXN];int len_str;


struct TrieNode{
    int frq,siz;
    int ch[26];
    TrieNode(){
        frq = siz = 0;
        memset(ch, -1, sizeof(ch));
    }
} pool[MAXN*5];

int tot;
int rt[22][MAXN];//rt[PALI_LEN][TERMINAL_POS(STARTING FROM 1)]
int cur[22];

void trie_init(){
    for (int i = 1; i <= 20; i++) {
        cur[i] = 0;
        rt[i][0] = 0;
    }
    pool[0] = TrieNode();
    tot = 1;
}
int trie_alloc(){
    pool[tot] = TrieNode();
    return tot++;
}

void trie_insert(int id,int ver,int l,int r){
    if(cur[id] != ver-1){
        for (int i = cur[id]+1; i <= ver-1; i++) {
            rt[id][i] = rt[id][i-1];
        }
    }
    int lst = rt[id][ver] = trie_alloc();
    pool[lst] = pool[rt[id][ver-1]];
    for (int i = l; i <= r; i++) {
        pool[lst].siz++;
        int np = trie_alloc();
        if(pool[lst].ch[str[i]-'a'] != -1){
            pool[np] = pool[pool[lst].ch[str[i]-'a']];
        }
        lst = pool[lst].ch[str[i]-'a'] = np;
    }
    pool[lst].frq++;
    pool[lst].siz++;
    cur[id] = ver;
}

int trie_query(int id,int lvr,int rvr,char* pat,int pat_len){
    int lst_l = rt[id][lvr], lst_r = rt[id][rvr];
    for(int i = 0;i < pat_len; i++){
        if(lst_l != -1) lst_l = pool[lst_l].ch[pat[i]-'a'];
        if(lst_r != -1) lst_r = pool[lst_r].ch[pat[i]-'a'];
    }
    int lsz = lst_l == -1?0:pool[lst_l].siz;
    int rsz = lst_r == -1?0:pool[lst_r].siz;
    return rsz - lsz;
}

inline bool ispanlidrome(int l,int r){
    while (l < r) {
        if(str[l] != str[r]) return false;
        l++,r--;
    }
    return true;
}

void prep(){
    len_str = strlen(str);
    for (int len = 1; len <= 20; len++) {
        for (int l = 0,r = l+len-1; r < len_str; l++,r++) {
            if(ispanlidrome(l, r)){
                int t = r,s = r - len/2 + 1;
                if(len&1){
                    s--;
                }
                trie_insert(len, t+1, s, t);
            }
        }
    }
    for (int len = 1; len <= 20; len++) {
        for (int i = cur[len]+1; i <= len_str; i++) {
            rt[len][i] = rt[len][i-1];
        }
    }
}


char pat[MAXN];int len_pat;
int L,R;
void solve(){
    len_pat = strlen(pat);
    int res = 0;
    for(int len = len_pat*2-1;len <= 20; len++){
        int s = L+len-1,t = R;
        if(s > t) break;
        res += trie_query(len, s-1, t, pat, len_pat);
    }
    printf("%d\n",res);
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %s",str) != EOF) {
        trie_init();
        prep();
        int q;
        scanf(" %d",&q);
        REP(i,q){
            scanf(" %d %d %s",&L,&R,pat);
            solve();
        }
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
