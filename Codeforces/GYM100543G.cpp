#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAXN = 2000005, MAXC = 4;

struct PalTree{
    int ch[MAXN][MAXC],len[MAXN],num[MAXN],fail[MAXN],cnt[MAXN],par[MAXN];
    int str[MAXN],n;
    int q,last;

    int alloc(int plen){
        for (int i = 0; i < MAXC; i++) {
            ch[q][i] = 0;
        }
        len[q] = plen;
        num[q] = 0;
        fail[q] = 0;
        cnt[q] = 0;
        par[q] = -1;
        return q++;
    }

    void init(){
        q = 0;
        alloc(0);
        alloc(-1);
        last = 0;
        n = 0;
        str[n] = -1;
        fail[0] = 1;
    }

    int getfail(int x){
        while(str[n - len[x] - 1] != str[n]){
            x = fail[x];
        }
        return x;
    }

    void addchar(int c){
        c -= 'a';
        str[++n] = c;
        int cur = getfail(last);
        if(!ch[cur][c]){
            int now = alloc(len[cur] + 2);
            fail[now] = ch[getfail(fail[cur])][c];
            ch[cur][c] = now;
            par[now] = cur;
            num[now] = num[fail[now]] + 1;
        }
        last = ch[cur][c];
        cnt[last]++;
    }

    void count(){
        for(int i = q-1;i >= 0; i--){
            cnt[fail[i]] += cnt[i];
        }
    }
} pal;

char buf[MAXN];
int len;

int hf[MAXN],fl[MAXN],flmlen[MAXN],pos[MAXN];
int MAXLOG,anc[MAXN][20];
void failtree_build(){
    pal.fail[0] = 0; // Originally being 1
    for(int i = 2;i < pal.q; i++){
        int newfail = pal.fail[i];
        while(pal.len[newfail]%2){
            newfail = pal.fail[newfail];
        }
        pal.fail[i] = newfail;
    }
}

void prep(){
    MAXLOG = 1;
    while((1 << MAXLOG) <= pal.q){
        MAXLOG++;
    }
    for(int i = 0;i < pal.q; i++){
        anc[i][0] = pal.fail[i];
    }
    for(int i = 1;i < MAXLOG; i++){
        for(int j = 0;j < pal.q; j++){
            if(anc[j][i-1] == -1) anc[j][i] = -1;
            else anc[j][i] = anc[anc[j][i-1]][i-1];
        }
    }
}

int hfpos(int u){
    int targetlen = pal.len[u]/2;
    for(int proc = MAXLOG-1; proc >= 0; proc--){
        if(anc[u][proc] == -1) continue;
        if(pal.len[anc[u][proc]] >= targetlen) u = anc[u][proc];
        if(pal.len[u] == targetlen) break;
    }
    if(pal.len[u] > targetlen) return anc[u][0];
    else return u;
}

int solve(){
    int res = len;
    hf[0] = fl[0] = flmlen[0] = 0;
    for(int i = 2;i < pal.q; i++){
        if(pal.len[i]%2 == 0){
            hf[i] = hf[pal.par[i]] + 1;
            hf[i] = min(hf[i],flmlen[hfpos(i)]+pal.len[i]/2);
            fl[i] = hf[i] + 1;
            fl[i] = min(fl[i],fl[pal.par[i]] + 2);
            fl[i] = min(fl[i],flmlen[pal.fail[i]]+pal.len[i]);
            flmlen[i] = fl[i]-pal.len[i];
            res = min(res,fl[i] + len - pal.len[i]);
        }
    }
    return res;
}

int main(int argc, char *argv[]) {

    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        scanf(" %s",buf);
        len = strlen(buf);
        for(int i = 0;i < len; i++){
            if(buf[i] == 'A') buf[i] = 'a';
            else if(buf[i] == 'G') buf[i] = 'b';
            else if(buf[i] == 'C') buf[i] = 'c';
            else if(buf[i] == 'T') buf[i] = 'd';
        }
        pal.init();
        for(int i = 0;i < len; i++){
            pal.addchar(buf[i]);
            pos[i] = pal.last;
        }
        failtree_build();
        prep();
        cout << solve() << '\n';
    }

    return 0;
}
