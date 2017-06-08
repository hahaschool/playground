#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAXN = 100005,MAXC = 26;

struct PalTree{
    int ch[MAXN][MAXC],len[MAXN],num[MAXN],fail[MAXN];
    long long cnt[MAXN];
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
            num[now] = num[fail[now]] + 1;
        }
        last = ch[cur][c];
        cnt[last]++;
    }

    void count(){
        for(int i = q-1; i >= 0; i--){
            cnt[fail[i]] += cnt[i];
        }
    }

}pal;

char buf[MAXN];
int len,anc[MAXN][20];
long long palfac[MAXN];
int MAXLOG;

void prep(){
    MAXLOG = 1;
    while((1 << MAXLOG) <= pal.q) MAXLOG++;
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

int get(int u){
    int targetlen = pal.len[u]/2;
    for(int proc = MAXLOG-1; proc >= 0; proc--){
        if(anc[u][proc] == -1) continue;
        if(pal.len[anc[u][proc]] >= targetlen) u = anc[u][proc];
        if(pal.len[u] == targetlen) return u;
    }
    return -1;
}

int main(int argc, char *argv[]) {

    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        scanf(" %s",buf);
        pal.init();
        len = strlen(buf);
        for(int i = 0;i < len; i++){
            pal.addchar(buf[i]);
        }
        pal.count();
        prep();
        palfac[0] = 0;
        palfac[1] = 0;
        for(int i = 2;i < pal.q; i++){
            if(pal.len[i] == 1) palfac[i] = 1;
            int att = get(i);
            if(att != -1) palfac[i] = palfac[att]+1;
            else palfac[i] = 1;
        }
        long long res = 0;
        for(int i = 2;i < pal.q; i++){
            res += palfac[i] * pal.cnt[i];
        }
        cout << res << '\n';
    }

    return 0;
}
