//
//  HDU1693.cpp
//  playground
//
//  Created by 張正昊 on 3/5/2016.
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
int board[MAXN][MAXN];


struct HashTable{
    static const int HASHMOD = 49999;
    typedef long long VALTYPE;
    VALTYPE hash[HASHMOD+100],value[HASHMOD+100];
    int top,stk[HASHMOD+100];
    int locate(const VALTYPE x){
        int h = x % HASHMOD;
        while(hash[h] != -1 && hash[h] != x){
            h++;
        }
        return h;
    }
    void insert(const VALTYPE key,const VALTYPE val,int h = -1){
        if(h == -1) h = locate(key);
        if(hash[h] == -1){
            hash[h] = key;
            value[h] = val;
            stk[++top] = h;
        }
    }
    void set(const VALTYPE key,const VALTYPE val){
        int h = locate(key);
        if(hash[h] == -1){
            insert(key, val, h);
        }else{
            value[h] = val;
        }
    }
    VALTYPE find(const long long key){
        int h = locate(key);
        return (hash[h] == key)?value[h]:-1;
    }
    void clear(){
        while(top){
            hash[stk[top--]] = -1;
        }
    }
    HashTable(){
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
void decode(int *arr,long long code,int n){
    long long msk = (1 << CODEBLOCK_SIZE) - 1;
    for (int i = 1; i <= n; i++) {
        arr[i] = (int)(code & msk);
        code >>= CODEBLOCK_SIZE;
    }
}

struct DisjointSet{
    static const int DJMAX = 66;
    int par[DJMAX],siz[DJMAX],n,vn;
    void reset(int _n,int _vn){
        //前vn个点是虚拟点，后面的是实际点
        n = _n,vn = _vn;
        for(int i = 1;i <= n+vn; i++){
            par[i] = i;
            siz[i] = (i <= vn)?0:1;
        }
    }
    int find(int x){
        //原始查找
        return (par[x] == x)?x:par[x] = find(par[x]);
    }
    int get(int x){
        //查找实际点所属虚拟点
        return find(x+vn);
    }
    void unify(int a,int b){
        //合并两个实际点
        int pa = find(a+vn),pb = find(b+vn);
        if (pb > vn) swap(pa, pb);
        siz[pb] += siz[pa];
        par[pa] = pb;
    }
    void link(int a,int p){
        //把实际点连接到虚拟点上
        int pa = find(a+vn),pb = find(p);
        siz[pb] += siz[pa];
        par[pa] = pb;
    }
    int spare(){
        //查找空虚拟点
        for(int i = 1; i <= vn; i++){
            if(!siz[i]) return i;
        }
        return -1;
    }
} dj;

int blksiz,plgsiz;
int plug[MAXN];
void build_block(){
    //将插头信息导入并查集
    dj.reset(blksiz,plgsiz);
    for(int i = 1;i <= plgsiz;i++){
        if(plug[i]){
            dj.link(i, plug[i]);
        }
    }
}
void merge_block(int a,int b){
    //合并插头所属联通分量
    dj.unify(a, b);
    plug[a] = dj.get(a);
    plug[b] = dj.get(b);
}
void create_block(int a){
    //在无所属的a插头处创建联通分量
    dj.link(a, dj.spare());
    plug[a] = dj.get(a);
}
int project[MAXN];
void commit_plug(){
    int tot = 0;
    for (int i = 1; i <= blksiz; i++) {
        project[i] = 0;
    }
    for (int i = 1; i <= plgsiz; i++) {
        if(plug[i] && !project[dj.get(i)]){
            project[dj.get(i)] = ++tot;
        }
    }
    for(int i = 1;i <= plgsiz;i++){
        if(plug[i]){
            plug[i] = project[dj.get(i)];
        }
    }
}

long long update(int tick,long long prev){
    long long code = encode(plug, plgsiz);
    long long cur = tab[tick].find(code);
    if(cur == -1){
        tab[tick].insert(code, prev);
        return code;
    }else{
        tab[tick].set(code, cur+prev);
        return -1;
    }
}

void nextrow_shift(){
    for(int i = plgsiz;i >= 1; i--){
        plug[i] = plug[i-1];
    }
}


int n,m;
long long solve(){
    plgsiz = blksiz = m+1;
    queue<long long> que[2];
    int tick = 0;
    tab[tick].clear();
    int si = 0, sj = 0, fi = 0, fj = 0;
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m;j++){
            if (board[i][j] == 1) {
                fi = i,fj = j;
                if(!si && !sj){
                    if(board[i][j+1] == 1 && board[i+1][j] == 1){
                        decode(plug, 0, plgsiz);
                        build_block();
                        create_block(j);
                        merge_block(j, j+1);
                        commit_plug();
                        que[tick].push(update(tick, 1));
                        si = i,sj = j+1;
                    }else{
                        return 0;
                    }
                }
            }
        }
    }
    
    for (int i = si; i <= n; i++) {
        for (int j = sj; j <= m; j++) {
            si = sj = 1;
            tick ^= 1;
            tab[tick].clear();
            while (!que[tick^1].empty()) {
                long long s = que[tick^1].front();
                que[tick^1].pop();
                long long prv = tab[tick^1].find(s);
                decode(plug, s, plgsiz);
                build_block();
                int &left = plug[j],&up = plug[j+1];
                if (board[i][j] != 1) {
                    //当前所处障碍格子，只要转移状态就可以了
                    left = up = 0;
                    if (j == m) nextrow_shift();
                    long long nxt = update(tick, prv);
                    if(nxt != -1) que[tick].push(nxt);
                }else{
                    if(left && up){
                        //因为是多回路问题所以无论上左两个插头的联通分量怎样都可以连接
                        merge_block(j, j+1);
                        left = up = 0;
                        commit_plug();
                        if(j == m) nextrow_shift();
                        long long nxt = update(tick, prv);
                        if(nxt != -1) que[tick].push(nxt);
                    }else if(left){
                        if (board[i][j+1] == 1) {
                            //尝试把左插头延长到右边
                            swap(left, up);
                            long long nxt = update(tick, prv);
                            if(nxt != -1) que[tick].push(nxt);
                            swap(left, up);
                        }
                        if (board[i+1][j] == 1){
                            //尝试把左插头延长到下边
                            if(j == m) nextrow_shift();
                            long long nxt = update(tick, prv);
                            if(nxt != -1) que[tick].push(nxt);
                        }
                    }else if(up){
                        if(board[i][j+1] == 1){
                            //尝试把上插头延长到右边
                            long long nxt = update(tick, prv);
                            if(nxt != -1) que[tick].push(nxt);
                        }
                        if(board[i+1][j] == 1){
                            //尝试把上插头延长到下边
                            swap(left, up);
                            if(j == m) nextrow_shift();
                            long long nxt = update(tick, prv);
                            if(nxt != -1) que[tick].push(nxt);
                            swap(left, up);
                        }
                    }else{
                        if (board[i][j] == 1 && board[i+1][j] == 1 && board[i][j+1] == 1) {
                            //尝试创建新联通分量
                            create_block(j);
                            merge_block(j, j+1);
                            commit_plug();
                            if(j == m) nextrow_shift();
                            long long nxt = update(tick, prv);
                            if(nxt != -1) que[tick].push(nxt);
                        }
                    }
                }
            }
            if(i == fi && j == fj){
                return max(0LL,tab[tick].find(0));
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
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        scanf(" %d %d",&n,&m);
        memset(board, 0, sizeof(board));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf(" %d",&board[i][j]);
            }
        }
        long long res = solve();
        printf("Case %d: There are %lld ways to eat the trees.\n",d,res);
    }
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
