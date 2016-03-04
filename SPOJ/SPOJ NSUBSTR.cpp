//
//  SPOJ NSUBSTR.cpp
//  playground
//
//  Created by Adam Chang on 2015/08/09.
//  Copyright © 2015年 Adam Chang. All rights reserved.
//

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

using namespace std;

struct SAM_State{
    int mxn;
    int dp;
    SAM_State *to[26];
    SAM_State *parent;
    void init(int _mxn){
        mxn = _mxn;
        memset(to, NULL, sizeof(to));
        parent = NULL;
        dp = 0;
    }
} idx[500005];

int totalNode = 0;
int mxmxn = 0;
SAM_State *idx_sorted[500005];

SAM_State* SAM_Append(SAM_State *last,SAM_State *root,int ch){
    SAM_State *p = last;
    SAM_State *np = &idx[++totalNode];
    np -> mxn = p -> mxn + 1;
    mxmxn = max(mxmxn, np -> mxn);
    while (p && p -> to[ch] == NULL) {
        p -> to[ch] = np;
        p = p -> parent;
    }
    if (p != NULL) {
        SAM_State *q = p -> to[ch];
        if (q -> mxn == p -> mxn + 1) {
            np -> parent = q;
        }else{
            SAM_State *nq = &idx[++totalNode];
            *nq = *q;
            nq -> mxn = p -> mxn + 1;
            q -> parent = nq;
            np -> parent = nq;
            while (p && p -> to[ch] == q) {
                p -> to[ch] = nq;
                p = p -> parent;
            }
        }
    }else{
        np -> parent = root;
    }
    last = np;
    return last;
}

void init(int n){
    for (int i = 0; i <= n ; i++) {
        idx[i].init(0);
    }
    totalNode = 0;
    mxmxn = 0;
}

SAM_State* SAM_Build(char* str){
    int len = (int)strlen(str);
    init(2*len);
    SAM_State *root = &idx[0];
    SAM_State *last = root;
    for (int i = 0; i < len; i++) {
        last = SAM_Append(last, root, str[i] - 'a');
    }
    return root;
}

int cnt[250005];
void toposort(){
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= totalNode; i++) {
        cnt[idx[i].mxn]++;
    }
    for (int i = 1; i <= mxmxn; i++) {
        cnt[i] += cnt[i-1];
    }
    for (int i = 0; i <= totalNode; i++) {
        idx_sorted[--cnt[idx[i].mxn]] = &idx[i];
    }
}

char a[250005];
int res[250005];
int main(){
    scanf(" %s",a);
    SAM_State *sam = SAM_Build(a);
    toposort();
    for (int i = 0; i < mxmxn; i++) {
        sam = sam -> to[a[i] - 'a'];
        cout << sam -> mxn << "+" << endl;
        sam -> dp++;
    }
    for (int i = totalNode; i >= 0; i--) {
        if (idx_sorted[i] -> parent != NULL) {
            idx_sorted[i] -> parent -> dp += idx_sorted[i] -> dp;
        }
    }
    for (int i = 0;i <= mxmxn; i++) {
        res[i] = 0;
    }
    for (int i = 0; i <= totalNode; i++) {
        res[idx[i].mxn] = max(idx[i].dp,res[idx[i].mxn]);
    }
    for (int i = 1; i <= mxmxn; i++) {
        printf("%d\n",res[i]);
    }
    return 0;
}
