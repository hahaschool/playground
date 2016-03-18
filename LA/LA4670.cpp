//
//  LA4670.cpp
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

const int MAXH = 26,MAXN = 1000006;
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
} trie[MAXN];
int rt = 1,tot = 1;
void trie_init(){
    tot = 1;
    trie[rt].init();
}
void trie_insert(string word,int id){
    int len = (int)word.size();
    int ls = rt;
    for (int i = 0; i < len; i++) {
        if (trie[ls].ch[word[i] - 'a']) {
            ls = trie[ls].ch[word[i] - 'a'];
        }else{
            trie[ls].ch[word[i] - 'a'] = ++tot;
            trie[tot].init();
            ls = tot;
        }
    }
    trie[ls].freq++;
    trie[ls].id.push_back(id);
}
void aca_buildfail(){
    queue<int> que;
    for(int i = 0; i < MAXH; i++){
        int v = trie[rt].ch[i];
        if (!v) {
            trie[rt].ch[i] = rt;
            continue;
        }
        trie[v].fail = trie[v].last = rt;
        que.push(v);
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < MAXH; i++) {
            int v = trie[u].ch[i];
            if (!v) {
                //确实化失配边
                trie[u].ch[i] = trie[trie[u].fail].ch[i];
                continue;
            }
            que.push(v);
            trie[v].fail = trie[trie[u].fail].ch[i];//vfail = ufail->i
            trie[v].last = trie[trie[v].fail].freq ? trie[v].fail : trie[trie[v].fail].last;//vlast = vfail : vfail->last
        }
    }
}


int n;
string buf[155];
char str[1000006];
int cnt[155];

void solve(){
    int len = (int)strlen(str);
    int cr = rt;
    memset(cnt, 0, sizeof(cnt));
    int mxd = 0;
    for (int i = 0; i < len; i++) {
        cr = trie[cr].ch[str[i] - 'a'];
        if (trie[cr].freq) {
            for (int j = 0; j < trie[cr].id.size(); j++) {
                mxd = max(mxd,++cnt[trie[cr].id[j]]);
            }
        }
    }
    cout << mxd << '\n';
    for(int i = 1;i <= n; i++){
        if (cnt[i] == mxd) {
            cout << buf[i] << '\n';
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&n) != EOF && n) {
        trie_init();
        for (int i = 1; i <= n; i++) {
            cin >> buf[i];
            trie_insert(buf[i],i);
        }
        aca_buildfail();
        scanf(" %s",str);
        solve();
    }
    return 0;
}
