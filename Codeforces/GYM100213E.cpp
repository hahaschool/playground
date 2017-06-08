#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 1010*1010;
int par[MAXN*2],siz[MAXN*2];
void dj_init(){
    for(int i = 0;i < MAXN; i++){
        par[i] = MAXN+i;
        par[i+MAXN] = i+MAXN;
        siz[i] = 1;
        siz[i+MAXN] = 1;
    }
}

int dj_find(int x){
    if(par[x] == x) return x;
    else return par[x] = dj_find(par[x]);
}

void dj_link(int a,int b){
    //a --> b
    int pa = dj_find(a), pb = dj_find(b);
    par[pa] = pb;
    siz[pb] += siz[pa];
}

int N,S;
int dir[2][6][2] = {{{0,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}},
                    {{0,1},{1,1},{1,0},{0,-1},{-1,0},{-1,1}}};
inline int cvt(const int x, const int y){
    return (x+504)*1010+(y+504);
}
bool land[MAXN];
int main(int argc, char *argv[]){
    //freopen("islands.in","r",stdin);
    //freopen("islands.out","w",stdout);
    while(scanf(" %d %d",&N,&S) != EOF){
        dj_init();
        for(int i = 0;i < MAXN; i++){
            land[i] = false;
        }
        for(int i = 1;i <= N; i++){
            int x,y;
            scanf(" %d %d",&x,&y);
            if(land[cvt(x,y)]) continue;
            else{
                int cnt = 0;
                set<int> st;
                vector<int> vec;
                vec.resize(6);
                for(int i = 0;i < 6; i++){
                    vec[i] = cvt(x+dir[x&1][i][0], y+dir[x&1][i][1]);
                    if(land[vec[i]])
                        if(!st.count(dj_find(vec[i]))){
                            st.insert(dj_find(vec[i]));
                            cnt += siz[dj_find(vec[i])];
                        }
                }
                if(cnt+1 <= S){
                    land[cvt(x,y)] = true;
                    for(int i = 0;i < 6; i++){
                        if(land[vec[i]] && dj_find(vec[i]) != dj_find(cvt(x,y)))
                            dj_link(cvt(x,y),vec[i]);
                    }
                }
            }
        }
        set<int> stid;
        vector<int> vecsiz;
        for(int i = 0;i < MAXN; i++){
            if(land[i]){
                if(!stid.count(dj_find(i))){
                    stid.insert(dj_find(i));
                    vecsiz.push_back(siz[dj_find(i)]);
                }
            }
        }
        sort(vecsiz.begin(),vecsiz.end());
        printf("%d\n",stid.size());
        for(int i = 0;i < vecsiz.size(); i++){
            printf("%d",vecsiz[i]);
            if(i == vecsiz.size()-1) puts("");
            else putchar(' ');
        }
    }

    return 0;
}
