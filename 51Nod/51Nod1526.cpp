#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

static const int MAXN = 800005;
int ch[MAXN][26];
int pos[MAXN],neg[MAXN];
int tot,root;
int alloc(){
    tot++;
    memset(ch[tot],-1,sizeof(ch[tot]));
    pos[tot] = neg[tot] = 0;
    return tot;
}
void init(){
    tot = -1;
    root = alloc();
}
void insert(char *str,int mkr){
    int len = strlen(str);
    int cur = root;
    for(int i = 0;i < len; i++){
        if(ch[cur][str[i]-'a'] == -1)
            ch[cur][str[i]-'a'] = alloc();
        cur = ch[cur][str[i]-'a'];
    }
    if(mkr > 0) pos[cur] += mkr;
    else neg[cur] -= mkr;
}

int N;
char buf[MAXN];
long long res = 0;

struct State{
    int u,d,step,po,ne,i,v;
};
stack<State> stk;

void dfs(int u,int d){
    int po = pos[u],ne = neg[u];
    for(int i = 0;i < 26; i++){
        if(ch[u][i] != -1){
            int v = ch[u][i];
            dfs(v,d+1);
            po += pos[v];
            ne += neg[v];
        }
    }
    res += 1LL*min(po,ne)*d;
    int t = min(po,ne);
    pos[u] = po-t;
    neg[u] = ne-t;
    //printf("typ[%d] <-- %d\n",u,typ[u]);
}

void work(){
    stk.push((State){root,0,1,0,0,0,0});
    while(!stk.empty()){
        State cur = stk.top();stk.pop();
        //cerr << cur.u << ' ' << cur.po << ' ' << cur.ne << endl;
        if(cur.step == 1){
            cur.po = pos[cur.u], cur.ne = neg[cur.u];
            for(cur.i = 0; cur.i < 26; cur.i++){
                if(ch[cur.u][cur.i] != -1){
                    cur.v = ch[cur.u][cur.i];
                    cur.step = 2;
                    stk.push(cur);
                    stk.push((State){cur.v,cur.d+1,1,0,0,0,0});
                    break;
                }
            }
            cur.step = 3;
            stk.push(cur);
        }else if(cur.step == 2){
            cur.po += pos[cur.v];
            cur.ne += neg[cur.v];
            bool flg = false;
            cur.i++;
            for(;cur.i < 26;cur.i++){
                if(ch[cur.u][cur.i] != -1){
                    cur.v = ch[cur.u][cur.i];
                    stk.push(cur);
                    stk.push((State){cur.v,cur.d+1,1,0,0,0,0});
                    flg = true;
                }
                if(flg) break;
            }
            if(flg) continue;
            cur.step = 3;
            stk.push(cur);
        }else if(cur.step == 3){
            res += 1LL*min(cur.po,cur.ne)*cur.d;
            int t = min(cur.po,cur.ne);
            pos[cur.u] = cur.po-t;
            neg[cur.u] = cur.ne-t;
        }
    }
}

int main(int argc, char *argv[]){

    init();
    scanf(" %d",&N);
    for(int i = 1;i <= N; i++){
        scanf(" %s",buf);
        insert(buf,1);
    }
    for(int i = 1;i <= N; i++){
        scanf(" %s",buf);
        insert(buf,-1);
    }
    //dfs(root,0);
    work();
    cout << res << endl;

    return 0;
}
