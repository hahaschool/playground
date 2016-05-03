//
//  URAL1519.cpp
//  playground
//
//  Created by 張正昊 on 1/5/2016.
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

const int MAXN = 15;
int n,m;
int blksiz,plugsiz;
char board[MAXN][MAXN];

struct Hashtable{
    static const int HASHMOD = 49999;//670987;
    long long top,hash[HASHMOD+100],value[HASHMOD+100],stk[HASHMOD+100];
    int locate(const long long x){
        int h = x % HASHMOD;
        while(hash[h] != -1 && hash[h] != x){
            h++;
        }
        return h;
    }
    void insert(const long long key,const long long val){
        int h = locate(key);
        if(hash[h] == -1){
            hash[h] = key;
            value[h] = val;
            stk[++top] = h;
        }
    }
    void set(const long long key,const long long val){
        int h = locate(key);
        if(hash[h] == -1){
            insert(key, val);
        }else{
            value[h] = val;
        }
    }
    long long find(const long long key){
        int h = locate(key);
        return (hash[h] == key)?value[h]:-1;
    }
    void clear(){
        while(top){
            hash[stk[top--]] = -1;
        }
    }
    Hashtable(){
        top = 0;
        memset(hash, -1, sizeof(hash));
    }
} tab[2];

const int CODEBLOCK_SIZE = 3;
long long encode(int *code,int n){
    long long ret = 0;
    for (int i = 1; i <= n; i++) {
        long long delta = code[i];
        delta <<= CODEBLOCK_SIZE*(i-1);
        ret += delta;
    }
    return ret;
}
void decode(long long code,int *arr,int n){
    long long msk = (1 << CODEBLOCK_SIZE) - 1;
    for (int i = 1; i <= n; i++) {
        arr[i] = (int)(code & msk);
        code >>= CODEBLOCK_SIZE;
    }
}

struct DisjointSet{
    static const int DJMAX = 66;
    int par[DJMAX],siz[DJMAX],vn,n;
    void reset(int vnn,int nn){
        vn = vnn,n = nn;
        for(int i = 1;i <= vn+n; i++){
            par[i] = i;
            siz[i] = (i <= vn)?0:1;
        }
    }
    int find(int a){
        return (par[a] == a)?a:par[a] = find(par[a]);
    }
    int get(int a){
        return find(a+vn);
    }
    void unify(int a,int b){
        int pa = find(a+vn),pb = find(b+vn);
        if(pb > vn) swap(pa,pb);
        siz[pb] += siz[pa];
        par[pa] = pb;
    }
    void link(int a,int p){//link to virtual
        int pa = find(a+vn),pb = find(p);
        siz[pb] += siz[pa];
        par[pa] = pb;
    }
} dj;

int plug[MAXN];
void build_block(int vn,int n){
    dj.reset(vn,n);
    for(int i = 1;i <= n; i++){
        if(plug[i]){
            dj.link(i, plug[i]);
        }
    }
}
void merge_block(int a,int b){
    dj.unify(a, b);
    plug[a] = dj.get(a);
    plug[b] = dj.get(b);
}
void create_block(int a){
    for (int i = 1; i <= dj.vn; i++) {
        if (!dj.siz[i]) {
            dj.link(a, i);
            break;
        }
    }
    plug[a] = dj.get(a);
}
int project[MAXN];
void commit_plug(int vn,int n){
    int tot = 0;
    for (int i = 1; i <= vn; i++) {
        project[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        if (plug[i] && !project[dj.get(i)]) {
            project[dj.get(i)] = ++tot;
        }
    }
    for (int i = 1; i <= n; i++) {
        if(plug[i]){
            plug[i] = project[dj.get(i)];
        }
    }
    
}

int tmp[MAXN];

long long update(int tick,long long prv){
    long long code = encode(plug, plugsiz);
    long long cur = tab[tick].find(code);
    if (cur == -1) {
        cur = prv;
        tab[tick].insert(code, prv);
        return code;
    }else{
        tab[tick].set(code, cur+prv);
        return 0;
    }
}

void nextrow_shift(int plugsiz){
    for(int i = plugsiz+1; i >= 1; i--){
        plug[i] = plug[i-1];
    }
}

long long solve(){
    queue<long long> que[2];
    int tick = 0;
    tab[tick].clear();
    tab[tick^1].clear();
    int finali = 0,finalj = 0,initi = 0,initj = 0;
    blksiz = m,plugsiz = m+1;
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++){
            if(board[i][j] == '.'){
                finali = i,finalj = j;
                if (!initi) {
                    if (board[i][j+1] == '.' && board[i+1][j] == '.') {
                        decode(0, plug, plugsiz);
                        build_block(blksiz, plugsiz);
                        create_block(j);
                        merge_block(j, j+1);
                        commit_plug(blksiz, plugsiz);
                        que[tick].push(update(tick, 1));
                        initi = i,initj = j+1;
                    }else{
                        return 0;
                    }
                }
            }
        }
    }
    
    for (int i = initi; i <= n; i++) {
        for (int j = initj; j <= m; j++) {
            initj = 1;
            tick ^= 1;
            tab[tick].clear();
            while (!que[tick^1].empty()) {
                long long s = que[tick^1].front();
                que[tick^1].pop();
                long long cur = tab[tick^1].find(s);
                decode(s, plug, plugsiz);
                build_block(blksiz,plugsiz);
                int &left = plug[j],&up = plug[j+1];
                if (board[i][j] != '.') {
                    //障碍格，单纯迁移状态即可
                    left = up = 0;
                    if(j == m) nextrow_shift(plugsiz);
                    long long nxt = update(tick, cur);
                    if (nxt) que[tick].push(nxt);
                }else{
                    if (left && up) {
                        //左插头和上插头都有
                        if (left == up) {
                            //左插头和上插头所属同一个联通快,合并将会给整个回路封口，只有在最后一个非障碍格子方可合并
                            if (i == finali && j == finalj) {
                                merge_block(j, j+1);
                                commit_plug(blksiz, plugsiz);
                                left = up = 0;
                                if (j == m) nextrow_shift(plugsiz);
                                long long nxt = update(tick, cur);
                                if (nxt) que[tick].push(nxt);
                            }
                        }else{
                            //左插头和上插头属于不同的联通快，尝试合并
                            merge_block(j, j+1);
                            commit_plug(blksiz, plugsiz);
                            left = up = 0;
                            if (j == m) nextrow_shift(plugsiz);
                            long long nxt = update(tick, cur);
                            if (nxt) que[tick].push(nxt);
                        }
                    } else if(left){
                        if (board[i][j+1] == '.') {
                            //尝试延长左插头到右边
                            swap(up, left);
                            long long nxt = update(tick, cur);
                            if (nxt) que[tick].push(nxt);
                            swap(up, left);
                        }
                        if (board[i+1][j] == '.') {
                            //尝试延长左插头到下边
                            if (j == m) nextrow_shift(plugsiz);
                            long long nxt = update(tick, cur);
                            if (nxt) que[tick].push(nxt);
                        }
                        
                    } else if(up){
                        if(board[i][j+1] == '.'){
                            //尝试延长上插头到右边
                            long long nxt = update(tick, cur);
                            if (nxt) que[tick].push(nxt);
                        }
                        if(board[i+1][j] == '.'){
                            //尝试延长上插头到下边
                            swap(up, left);
                            if (j == m) nextrow_shift(plugsiz);
                            long long nxt = update(tick, cur);
                            if (nxt) que[tick].push(nxt);
                        }
                    } else{
                        if (board[i][j] == '.' && board[i][j+1] == '.' && board[i+1][j] == '.') {
                            //尝试创建新联通分量
                            create_block(j);
                            merge_block(j, j+1);
                            commit_plug(blksiz, plugsiz);
                            long long nxt = update(tick, cur);
                            if (nxt) que[tick].push(nxt);
                        }
                    }
                }
                if(i == finali && j == finalj){
                    return tab[tick].find(0);
                }
            }
        }
    }
    return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    scanf(" %d %d",&n,&m);
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= m; j++){
            scanf(" %c",&board[i][j]);
        }
    }
    printf("%lld\n",solve());
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    return 0;
}
