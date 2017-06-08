#include <iostream>
#include <string>
#include <cstring>
#include <functional>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <set>
#include <ctime>
#include <vector>

using namespace std;

const int MAXN = 300005,MAXC = 26;

struct ExtPalTree{
    int ch[MAXN][MAXC];
    int fail[MAXN],len[MAXN],cnt[MAXN],num[MAXN];
    int str[MAXN*2],lb,rb;
    int q,last[2];//0: Llast 1: Rlast
    long long res;
    int alloc(int plen){
        for(int i = 0;i < MAXC; i++){
            ch[q][i] = 0;
        }
        fail[q] = cnt[q] = num[q] = 0;
        len[q] = plen;
        return q++;
    }

    void init(){
        lb = MAXN-1, rb = MAXN;
        q = last[0] = last[1] = 0;
        alloc(0);
        alloc(-1);
        str[rb] = str[lb] = -1;
        fail[0] = 1;
        res = 0;
    }

    int getfail(int x,int dir){
        if(dir == 0)
            while(str[lb+1] != str[lb+len[x]+2])
                x = fail[x];
        else
            while(str[rb-1] != str[rb-len[x]-2])
                x = fail[x];
        return x;
    }

    void addchar(int c,int dir){
        c -= 'a';
        if(dir == 0) str[lb--] = c, str[lb] = -1;
        else str[rb++] = c, str[rb] = -1;
        int cur = getfail(last[dir], dir);
        if(!ch[cur][c]){
            int now = alloc(len[cur] + 2);
            fail[now] = ch[getfail(fail[cur],dir)][c];
            ch[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last[dir] = ch[cur][c];
        if(len[last[dir]] == rb - lb - 1) last[dir^1] = last[dir];
        cnt[last[dir]]++;
    }

    void count(){
        for(int i = q-1;i >= 0; i--){
            cnt[fail[i]] += cnt[i];
        }
        for(int i = 2;i < q; i++){
            res = max(res,(long long)cnt[i] * (long long)len[i]);
        }
    }
}pal;

char buf[MAXN];

int main(int argc, char *argv[]){

    while(scanf(" %s",buf) != EOF){
        pal.init();
        int len = strlen(buf);
        for(int i = 0;i < len; i++){
            pal.addchar(buf[i],1);
        }
        pal.count();
        cout << pal.res << '\n';
    }

		return 0;
}
