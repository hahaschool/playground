//
//  UVA11468.cpp
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

const int MAXN = 505,MAXH = 100,MAXL = 105;
inline int hah(char ch){
    if (isalpha(ch)) {
        if (isupper(ch)) {
            return ch - 'A';
        }else{
            return ch - 'a' + 26;
        }
    }else{
        return ch - '0' + 55;
    }
}
struct Node{
    int ch[MAXH];
    bool virt[MAXH];
    int fail,last,freq;
    void init(){
        memset(ch, 0, sizeof(ch));
        memset(virt, 0,sizeof(virt));
        fail = last = -1;
        freq = 0;
    }
} trie[MAXN];
int tot = 1,rt = 1;
void trie_init(){
    tot = 1;
    trie[rt].init();
}
void trie_insert_word(char* buf){
    int l = (int)strlen(buf);
    int ls = rt;
    for(int i = 0;i < l;i++){
        if(trie[ls].ch[hah(buf[i])]){
            ls = trie[ls].ch[hah(buf[i])];
        }else{
            trie[++tot].init();
            trie[ls].ch[hah(buf[i])] = tot;
            ls = tot;
        }
    }
    trie[ls].freq++;
}
void aca_buildfail(){
    queue<int> que;
    trie[rt].fail = trie[rt].last = rt;
    for(int i = 0; i < MAXH; i++){
        int &v = trie[rt].ch[i];
        if (!v) {
            v = rt;
            trie[rt].virt[i] = true;
            continue;
        }
        trie[v].fail = rt;
        trie[v].last = rt;
        que.push(v);
    }
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(int i = 0; i < MAXH;i++){
            int &v = trie[u].ch[i];
            if (!v) {
                v = trie[trie[u].fail].ch[i];
                trie[u].virt[i] = true;
                continue;
            }
            trie[v].fail = trie[trie[u].fail].ch[i];
            trie[v].last = trie[trie[v].fail].freq? trie[v].fail:trie[trie[v].fail].last;
            //注意这里，使用last确认这个节点的祖先是否是某个单词的末端（last保证了端点都是匹配末端）
            //例子：SHER 中的E的last 指向 HE，如果匹配到了SHE，虽然这个时候E这个点并没有freq计数，但是已经匹配了HE，导致失败
            //所以在这里应该追踪last指针，检查在这个状态中是不是已经匹配到了别的单词
            //AC自动计综合DP中这里非常容易犯错误！
            //
            //在AC自动机中，一个节点对应了不止一个模式串，last指针指向了后缀相同的情况
            //比如SHER -> HER -> ER -> R
            if (trie[trie[v].last].freq) {
                trie[v].freq++;
            }
            que.push(v);
        }
    }
}

int n,m,L;
struct RDMCHR{
    int ch;
    double p;
};
vector<RDMCHR> chls;

char buf[30];

double dp[MAXN][MAXL];
bool vis[MAXN][MAXL];

void solve(){
    memset(dp, 0, sizeof(dp));
    dp[rt][0] = 1;
    for(int i = 0; i < L;i++){
        for(int j = 1; j <= tot; j++){
            if (trie[j].freq) {
                continue;
            }
            for(int k = 0; k < chls.size(); k++){
                int chr = chls[k].ch;
                double pr = chls[k].p;
                dp[trie[j].ch[chr]][i+1] += dp[j][i] * pr;
            }
        }
    }
    double res = 0;
    for(int i = 1; i <= tot; i++){
        if (trie[i].freq) {
            continue;
        }
        res += dp[i][L];
    }
    printf("%.6lf\n",res);
    
    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        printf("Case #%d: ",d);
        trie_init();
        chls.clear();
        scanf(" %d",&n);
        for(int i = 1;i <= n; i++){
            scanf(" %s",buf);
            trie_insert_word(buf);
        }
        aca_buildfail();
        scanf(" %d",&m);
        for(int i = 1; i<= m; i++){
            char cc;
            double pp;
            scanf(" %c %lf",&cc,&pp);
            chls.push_back({hah(cc),pp});
        }
        scanf(" %d",&L);
        solve();
    }
    return 0;
}
