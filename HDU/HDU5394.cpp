#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAXN = 2000005, MAXC = 4;

struct PalTree{
    int ch[MAXN][MAXC],len[MAXN],num[MAXN],fail[MAXN],cnt[MAXN];
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
        for(int i = q-1;i >= 0; i--){
            cnt[fail[i]] += cnt[i];
        }
    }
} pal;

int n;
int head[MAXN],nxt[MAXN],ed[MAXN],par[MAXN],q;
char chr[MAXN];
void gph_clr(){
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    q = 0;
}

void gph_ade(int u,int v){
    ed[q] = v;
    nxt[q] = head[u];
    head[u] = q++;
}

int N;

void dfs_buildpal(int u,int dep = 0){
    int orig_last = pal.last;
    /*
    for(int i=1;i <= dep; i++) putchar('\t');
    printf("Current in %d, orig_last = %d",u,orig_last);puts("");
    */
    for(int i = head[u]; ~i; i = nxt[i]){
        int v = ed[i];
        /*
        for(int i=1;i <= dep; i++) putchar('\t');
        printf("Heading for %d",v);puts("");
        */
        pal.addchar(chr[v]);
        dfs_buildpal(v,dep+1);
        pal.last = orig_last;
        pal.n--;
    }
}

void solve(){
    pal.init();
    scanf(" %d", &N);
    n = N+1;
    gph_clr();
    for(int i = 1;i <= N; i++){
        char arg1;
        int arg2;
        scanf(" %c %d", &arg1, &arg2);
        chr[i] = arg1;
        par[i] = arg2;
        gph_ade(par[i],i);
    }
    dfs_buildpal(0);
    long long res = 0;
    pal.count();
    /*
    for(int i = 0; i < pal.q; i++){
        printf("len[%d]=%d",i,pal.len[i]);
    }
    */
    for(int i = 2;i < pal.q; i++){
        res += (long long)pal.len[i] * pal.cnt[i];
    }
    cout << res << '\n';
}

int main(int argc, char *argv[]) {

    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        solve();
    }
    return 0;
}
