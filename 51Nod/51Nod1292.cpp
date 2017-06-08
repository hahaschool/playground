#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

struct SuffixAutomaton{
    static const int MAXN = 1500005,MAXC = 26;
    int mxn[MAXN],ch[MAXN][MAXC],par[MAXN],cnt[MAXN];
    int tot,last;

    int alloc(){
        tot++;
        mxn[tot] = 0;
        memset(ch[tot],-1,sizeof(ch[tot]));
        par[tot] = -1;
        cnt[tot] = 0;
        return tot;
    }
    void copy(int src,int dst){
        mxn[dst] = mxn[src];
        for(int i = 0; i < MAXC; i++) ch[dst][i] = ch[src][i];
        par[dst] = par[src];
    }
    void init(){
        tot = -1;
        last = alloc();
    }
    int append(int x){
        x -= 'a';
        int p = last,np = alloc();
        cnt[np]++;
        mxn[np] = mxn[p] + 1;
        while(p != -1 && ch[p][x] == -1){
            ch[p][x] = np;
            p = par[p];
        }
        if(p != -1){
            int q = ch[p][x];
            if(mxn[q] == mxn[p] + 1){
                par[np] = q;
            }else{
                int nq = alloc();
                copy(q,nq);
                mxn[nq] = mxn[p] + 1;
                par[q] = par[np] = nq;
                while(p != -1 && ch[p][x] == q){
                    ch[p][x] = nq;
                    p = par[p];
                }
            }
        }else{
            par[np] = 0;
        }
        return last = np;
    }
} sam;

const int MAXN = 1500005;
char str[MAXN];
int n;

int dep[MAXN];
int head[MAXN],ed[MAXN],nxt[MAXN],q = 2;
void ade(int u,int v){
    ed[q] = v;
    nxt[q] = head[u];
    head[u] = q++;
}
void dfs(int u,int d){
    dep[u] = d;
    for(int i = head[u];i;i = nxt[i]){
        dfs(ed[i],d+1);
    }
    for(int i = head[u];i;i = nxt[i]){
        sam.cnt[u-1] += sam.cnt[ed[i]-1];
    }
}

int main(int argc, char *argv[]){

    scanf(" %s",str);
    n = strlen(str);
    long long res = 0;
    sam.init();
    for(int i = 0;i < n; i++){
        sam.append(str[i]);
    }
    for(int i = sam.tot; i > 0; i--){
        if(sam.par[i] != -1){
            ade(sam.par[i]+1,i+1);
        }
    }
    dfs(1,0);
    /*
    for(int i = 1;i <= sam.tot; i++){
        res = max(res, 1LL * sam.mxn[i] * sam.cnt[i]);
    }
    */
    int cur = 0;
    for(int i = 0;i < n; i++){
        cur = sam.ch[cur][str[i]-'a'];
        res = max(res,1LL*sam.mxn[cur]*sam.cnt[cur]);
    }
    cout << res << endl;

    return 0;
}
