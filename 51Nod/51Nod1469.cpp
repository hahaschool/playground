#include <string>
#include <cstring>
#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 200005;

int mxn[MAXN],ch[MAXN][26],cnt[MAXN][27],par[MAXN],rt[MAXN];
int tot,last;
int alloc(){
    tot++;
    mxn[tot] = 0;
    rt[tot] = 0;
    par[tot] = -1;
    memset(ch[tot],-1,sizeof(ch[tot]));
    memset(cnt[tot],0,sizeof(cnt[tot]));
    return tot;
}
void copy(int src,int dst){
    mxn[dst] = mxn[src];
    for(int i = 0;i < 26; i++) ch[dst][i] = ch[src][i];
    par[dst] = par[src];
}
void init(){
    tot = -1;
    last = alloc();
}

int append(int x,int pos){
    x -= 'a';
    int p = last, np = alloc();
    cnt[np][26] = 1;
    mxn[np] = mxn[p] + 1;
    rt[np] = pos;
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

char str[MAXN];
int N;
int head[MAXN],ed[MAXN],nxt[MAXN],q = 2;
void ade(int u,int v){
    ed[q] = v;
    nxt[q] = head[u];
    head[u] = q++;
}
void dfs(int u){
    int s = u-1;
    //printf("rt[%d] = %d\n",s,rt[s]);
    for(int i = head[u];i;i = nxt[i]){
        dfs(ed[i]);
    }
    if(s)
    for(int i = head[u];i;i = nxt[i]){
        int t = ed[i]-1;
        rt[s] = max(rt[s],rt[t]);
        cnt[s][str[rt[t] - mxn[s]] - 'a'] += cnt[t][26];
    }
    for(int i = 0;i < 26;i++){
        //if(cnt[s][i])printf("cnt[%d][%d] = %d\n",s,i,cnt[s][i]);
        cnt[s][26] += cnt[s][i];
    }
}


int main(){

    scanf(" %s",str);
    N = strlen(str);
    init();
    for(int i = 0;i < N; i++){
        append(str[i],i);
    }
    for(int i = 0;i <= tot; i++){
        if(par[i] != -1){
            ade(par[i]+1,i+1);
            //cerr << par[i]+1 << " --> " << i+1 << endl;
        }
    }
    dfs(1);

    int res = 0;
    for(int i = 1;i <= tot; i++){
        if(cnt[i][26] > 1){
            bool pas = true;
            for(int j = 0;j < 26; j++){
                if(ch[i][j] != -1){
                    int v = ch[i][j];
                    if(cnt[v][26] > 1){
                        //printf("cnt[%d][%d] = %d\n",v,26,cnt[v][26]);
                        pas = false;
                        break;
                    }
                }
            }
            if(!pas) continue;
            for(int j = 0;j < 26; j++){
                if(cnt[i][j] > 1){
                    //printf("cnt[%d][%d] = %d\n",i,j,cnt[i][j]);
                    pas = false;
                    break;
                }
            }
            if(pas) res++;
        }
    }
    cout << res << endl;

    return 0;
}
