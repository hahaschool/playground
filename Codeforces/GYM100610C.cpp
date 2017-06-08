#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 200005;
int N;
int seq[MAXN];

bool vis[MAXN];
vector<vector<int> > groups;
void groupDecomp(){
    for(int i = 1;i <= N; i++){
        if(!vis[i]){
            vis[i] = true;
            groups.push_back(vector<int>());
            int cur = groups.size()-1;
            groups[cur].push_back(i);
            int p = seq[i];
            while(p != i){
                vis[p] = true;
                groups[cur].push_back(p);
                p = seq[p];
            }
        }
    }
}

vector<int> divider[MAXN];
void dividerProc(){
    for(int i = 1;i <= 200000; i++){
        for(int j = i;j <= 200000; j+=i){
            divider[j].push_back(i);
        }
    }
}

int sync[MAXN];
int g[MAXN];
void solve(){
    sync[groups[0].size()] = 1;
    for(int i = 0; i < groups[0].size(); i++){
        g[groups[0][i]] = groups[0][i];
    }
    for(int i = 1;i < groups.size(); i++){
        //looking for sync
        bool synced = false;
        int syncwith = -1;
        for(int j = 0; j < divider[groups[i].size()].size(); j++){
            if(sync[divider[groups[i].size()][j]]){
                if(!synced || groups[sync[divider[groups[i].size()][j]]-1][0] < groups[syncwith][0] ){
                    synced = true;
                    syncwith = sync[divider[groups[i].size()][j]]-1;
                }
            }
        }
        if(synced){
            for(int j = 0,k = 0; j < groups[i].size(); j++,k = (k+1)%groups[syncwith].size()){
                g[groups[i][j]] = groups[syncwith][k];
            }
        }else{
            for(int j = 0;j < groups[i].size(); j++){
                g[groups[i][j]] = groups[i][j];
            }
            sync[groups[i].size()] = i+1;
        }
    }
    for(int i = 1;i <= N; i++){
        printf("%d",g[i]);
        if(i == N) puts("");
        else putchar(' ');
    }
}

int main(int argc, char *argv[]){
    //freopen("commuting.in","r",stdin);
    //freopen("commuting.out","w",stdout);
    scanf(" %d",&N);
    for(int i = 1;i <= N; i++){
        scanf(" %d",&seq[i]);
    }
    groupDecomp();
    dividerProc();
    solve();

    return 0;
}
