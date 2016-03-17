//
//  LA3942.cpp
//  playground
//
//  Created by 張正昊 on 17/3/2016.
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

const int MAXN = 4000005,MAXLEN = 300005,MAXBUF = 105;
struct Node{
    int ch[26];
    int freq;
    void init(){
        memset(ch, -1, sizeof(ch));
        freq = 0;
    }
} trie[MAXN];

int rt = 0,tot = 0;

char str[MAXLEN],buf[MAXBUF];
int n;
void trie_insert_rev(char *word){
    int len = (int)strlen(word);
    reverse(buf, buf+len);
    int last = rt;
    for (int i = 0; i < len; i++) {
        if (trie[last].ch[word[i] - 'a'] == -1) {
            trie[last].ch[word[i] - 'a'] = ++tot;
            trie[tot].init();
            last = tot;
        }else{
            last = trie[last].ch[word[i] - 'a'];
        }
    }
    trie[last].freq++;
}
void trie_init(){
    tot = 0;
    trie[tot].init();
}

const int MODER = 20071027;

int dp[MAXLEN];
void solve(){
    int len = (int)strlen(str);
    dp[0] = 1;
    for (int i = 1; i <= len; i++) {
        int last = rt;
        int dpn = 0;
        for (int j = i; j >= 1; j--) {
            last = trie[last].ch[str[j-1] - 'a'];
            if (last == -1) {
                break;
            }else{
                if (trie[last].freq) {
                    dpn += dp[j-1];
                    dpn %= MODER;
                }
            }
        }
        dp[i] = dpn % MODER;
        //printf("dp[%d] = %d\n",i,dp[i]);
    }
    printf("%d\n",dp[len]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while (scanf(" %s",str) != EOF) {
        trie_init();
        printf("Case %d: ",++caseCnt);
        scanf(" %d",&n);
        for (int i = 1; i <= n; i++) {
            scanf(" %s",buf);
            trie_insert_rev(buf);
        }
        solve();
    }
    
    
    return 0;
}
