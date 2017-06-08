#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

/*
  Note:
  Root being 0, node indexed from 0~tot;
*/
static const int MAXN = 100005, MAXC = 26;
int mxn[MAXN],ch[MAXN][MAXC],par[MAXN],cnt[MAXN][2];
int tot,last;
int alloc(){
    tot++;
    mxn[tot] = 0;
    memset(ch[tot],-1,sizeof(ch[tot]));
    par[tot] = -1;
    cnt[tot][0] = cnt[tot][1] = 0;
    return tot;
}
void copy(int src,int dst){
    mxn[dst] = mxn[src];
    for(int i = 0;i < MAXC; i++) ch[dst][i] = ch[src][i];
    par[dst] = par[src];
}
void init(){
    tot = -1;
    last = alloc();
}

int append(int x,int id){
    x -= 'a';
    int p = last;
    //MultiSAM
    if(ch[p][x] != -1){
        int np = ch[p][x];
        if(mxn[np] == mxn[p] + 1){
            cnt[np][id] = 1;
            return last = np;
        }else{
            int q = alloc();
            copy(np,q);
            mxn[q] = mxn[p] + 1;
            par[np] = q;
            while(p != -1 && ch[p][x] == np){
                ch[p][x] = q;
                p = par[p];
            }
            cnt[q][id] = 1;
            return last = q;
        }
    }
    //RegularSAM
    int np = alloc();
    cnt[np][id] = 1;
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
            //cnt[nq][id] = 1;
            copy(q,nq);
            mxn[nq] = mxn[p] + 1;
            par[q] = par[np] = nq;
            while(q != -1 && ch[p][x] == q){
                ch[p][x] = nq;
                p = par[p];
            }
        }
    }else{
        par[np] = 0;
    }
    return last = np;
}

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
        cnt[u-1][0] += cnt[ed[i]-1][0];
        cnt[u-1][1] += cnt[ed[i]-1][1];
    }
}

string A,B;

int main(int argc, char *argv[]){

    cin >> A >> B;
    init();
    for(int i = 0;i < A.size(); i++){
        append(A[i],0);
        //cout << A[i] << ' ' << append(A[i],0) << endl;
    }
    last = 0;
    for(int i = 0;i < B.size(); i++){
        append(B[i],1);
        //cout << B[i] << ' ' << append(B[i],1) << endl;
    }
    memset(dep,0,sizeof(dep));
    
    for(int u = tot; u > 0; u--){
        //cerr << u << ' ' << cnt[u][0] << ' ' << cnt[u][1] << endl;
        if(par[u] != -1){
            ade(par[u]+1,u+1);
        }
    }
    dfs(1,0);
    int res = 0x3f3f3f3f;
    for(int u = tot; u > 0 ; u--){
        if(par[u] != -1){
            //cerr << u  << ' ' << par[u] <<' '  <<  mxn[u] << ':';
            //cerr << cnt[u][0] << ' ' << cnt[u][1] << endl;
            if(cnt[u][0] == 1 && cnt[u][1] == 1){
                res = min(res,mxn[par[u]]+1);
            }
        }
    }
    if(res == 0x3f3f3f3f) cout << -1 << endl;
    else cout << res << endl;
    return 0;
}
