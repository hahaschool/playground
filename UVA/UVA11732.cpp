//
//  UVA11732.cpp
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

inline int ha(char c){
    if (c == '\0') {
        return 909303;
    }
    if (isupper(c)) {
        return c - 'A';
    }else{
        return c - 'a' + 26;
    }
}

const int MAXN = 4000005,MAXE = 4000005;
int head[MAXN],dep[MAXN],par[MAXN],ed[MAXE],nxt[MAXN],ch[MAXE],q = 2,tot = 1;
long long freq[MAXN];
struct Arrange{
    int dep,id;
    bool operator < (const Arrange &b) const{
        return dep > b.dep;
    }
} arr[MAXN];

int rt = 1;
void insert_word(char *word){
    int l = (int)strlen(word) + 1;
    int last = rt;
    for (int i = 0; i < l; i++) {
        bool done = false;
        for (int j = head[last]; j; j = nxt[j]) {
            int v = ed[j];
            int c = ch[j];
            if (c == ha(word[i])) {
                last = v;
                done = true;
                break;
            }
        }
        if (!done) {
            ed[q] = ++tot;
            ch[q] = ha(word[i]);
            nxt[q] = head[last];
            head[last] = q++;
            
            head[tot] = 0;
            dep[tot] = dep[last] + 1;
            par[tot] = last;
            freq[tot] = 0;
            last = tot;
        }
    }
    freq[last]++;
}

long long stat(){
    long long ret = 0;
    for (int i = 1; i <= tot; i++) {
        arr[i] = {dep[i],i};
    }
    sort(arr+1,arr+1+tot);
    for (int i = 1; i <= tot; i++) {
        freq[par[arr[i].id]] += freq[arr[i].id];
    }
    for (int i = 1; i <= tot; i++) {
        //stat match
        if(i > 1)
        ret += freq[i] * (freq[i] - 1);
        //stat unmatch
        long long tp = 0;
        bool leaf = false;
        for (int j = head[i]; j; j = nxt[j]) {
            int v = ed[j];
            ret += freq[v] * tp;
            tp += freq[v];
            leaf = true;
        }
    }
    return ret;
}

int n;
char buf[1005];

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while (scanf(" %d",&n) != EOF && n) {
        q = 2;
        tot = 1;
        head[rt] = 0;
        dep[rt] = 0;
        par[rt] = 0;
        freq[rt] = 0;
        for (int i = 1; i <= n; i++) {
            scanf(" %s",buf);
            insert_word(buf);
        }
        printf("Case %d: %lld\n",++caseCnt,stat());
    }
    return 0;
}
