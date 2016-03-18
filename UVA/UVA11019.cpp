//
//  UVA11019.cpp
//  playground
//
//  Created by 張正昊 on 18/3/2016.
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

const int MAXN = 1010,MAXBUF = 105,MAXH = 256;
int n,m,x,y;
char str[MAXN][MAXN],buf[MAXBUF][MAXBUF];

int match[MAXN][MAXN];

struct Node{
    int ch[MAXH];
    int fail,last,freq;
    vector<int> id;
    void init(){
        memset(ch, 0, sizeof(ch));
        fail = last = -1;
        freq = 0;
        id.clear();
    }
} trie[MAXN*MAXN];
int rt = 1,tot = 1;
void trie_init(){
    tot = 1;
    trie[tot].init();
}
void trie_insert(char* word,int id){
    int len = (int)strlen(word);
    int ls = rt;
    for(int i = 0; i < len; i++){
        if(trie[ls].ch[word[i]]){
            ls = trie[ls].ch[word[i]];
            continue;
        }
        trie[ls].ch[word[i]] = ++tot;
        trie[tot].init();
        ls = tot;
    }
    trie[ls].freq++;
    trie[ls].id.push_back(id);
}
void aca_buildfail(){
    queue<int> que;
    for(int i = 0; i< MAXH; i++){
        int &v = trie[rt].ch[i];
        if(!v){
            v = rt;
            continue;
        }
        trie[v].fail = trie[v].last = rt;
        que.push(v);
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for(int i = 0; i < MAXH; i++){
            int &v = trie[u].ch[i];
            if(!v){
                v = trie[trie[u].fail].ch[i];
                continue;
            }
            trie[v].fail = trie[trie[u].fail].ch[i];
            trie[v].last = trie[trie[v].fail].freq? trie[v].fail : trie[trie[v].fail].last;
            que.push(v);
        }
    }
}

void solve(){
    memset(match, 0, sizeof(match));
    for(int i = 1; i<= n; i++){
        int cur = rt;
        for(int j = 0; j < m; j++){
            cur = trie[cur].ch[str[i][j]];
            if (trie[cur].freq) {
                for (int k = 0; k < trie[cur].id.size(); k++) {
                    if (i-trie[cur].id[k]+1 > 0 && j+2-y > 0 && i-trie[cur].id[k]+1 <= n && j+2-y <= m) {
                        match[i-trie[cur].id[k]+1][j+2-y]++;
                    }
                }
            }
        }
    }
    int res = 0;
    for(int i = 1; i<= n; i++){
        for (int j = 1; j<= m; j++) {
            if (match[i][j] >= x) {
                res++;
            }
        }
    }
    printf("%d\n",res);
}



int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        trie_init();
        scanf(" %d %d",&n,&m);
        for(int i = 1; i<= n; i++){
            scanf(" %s",str[i]);
        }
        scanf(" %d %d",&x,&y);
        for(int i = 1; i <= x; i++){
            scanf(" %s",buf[i]);
            trie_insert(buf[i],i);
        }
        aca_buildfail();
        solve();
    }
    
    return 0;
}
