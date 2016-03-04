//
//  SPOJ SUBLEX.cpp
//  playground
//
//  Created by Adam Chang on 2015/08/10.
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

#define MAXN 90005

struct SAM_State{
    int mxn;
    int cnt;
    int id;
    SAM_State *to[26];
    SAM_State *parent;
    void init(int _mxn){
        mxn = _mxn;
        memset(to, NULL, sizeof(to));
        parent = NULL;
        cnt = 0;
        id = 0;
    }
} idx[2*MAXN];

int totalNode = 0;
int len = 0;
SAM_State *idx_sorted[2*MAXN];

SAM_State* SAM_Append(SAM_State *last,SAM_State *root,int ch){
    SAM_State *p = last;
    SAM_State *np = &idx[++totalNode];
    np -> mxn = p -> mxn + 1;
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

void SAM_Init(int n){
    for (int i = 0; i <= n ; i++) {
        idx[i].init(0);
    }
    totalNode = 0;
}

SAM_State* SAM_Build(char* str){
    len = (int)strlen(str);
    SAM_Init(2*len);
    SAM_State *root = &idx[0];
    SAM_State *last = root;
    for (int i = 0; i < len; i++) {
        last = SAM_Append(last, root, str[i] - 'a');
    }
    return root;
}

int cnt[MAXN*2];
void SAM_Toposort(){
    for (int i = 0; i <= totalNode; i++) {
        idx[i].id = i;
        cnt[idx[i].mxn]++;
    }
    for (int i = 1; i <= len; i++) {
        cnt[i] += cnt[i-1];
    }
    for (int i = 0; i <= totalNode; i++) {
        idx_sorted[--cnt[idx[i].mxn]] = &idx[i];
    }
}

int childID[MAXN*2][26];
int childVal[MAXN*2][26];
char childCh[MAXN*2][26];
int childCnt[MAXN*2];
void SAM_Buildgraph(){
    for (int i = totalNode; i >= 0; i--) {
        SAM_State *cur = idx_sorted[i];
        int curid = cur -> id;
        for (int j = 0; j < 26; j++) {
            if (cur -> to[j] != NULL) {
                SAM_State *nxt = cur -> to[j];
                int nxtid = nxt -> id;
                childID[curid][childCnt[curid]] = nxtid;
                childVal[curid][childCnt[curid]] = nxt -> cnt + 1;
                childCh[curid][childCnt[curid]] = j + 'a';
                cur -> cnt += nxt -> cnt + 1;
                childCnt[curid]++;
            }
        }
    }
}

char ans[MAXN];
void get_ans(int k){
    int pos = 0;
    SAM_State *cur = &idx[0];
    while (k) {
        for (int i = 0; i < childCnt[cur -> id]; i++) {
            if (childVal[cur -> id][i] < k) {
                k -= childVal[cur -> id][i];
            }else {
                k--;
                ans[pos] = childCh[cur -> id][i];
                cur = &idx[childID[cur -> id][i]];
                pos++;
                break;
            }
        }
    }
    ans[pos] = '\0';
    puts(ans);
}

char a[MAXN];
int main(){
    scanf(" %s",a);
    SAM_Build(a);
    SAM_Toposort();
    SAM_Buildgraph();
    int q = 0;
    scanf(" %d",&q);
    for (int i = 1; i <= q; i++) {
        int k = 0;
        scanf(" %d",&k);
        get_ans(k);
    }
    return 0;
}