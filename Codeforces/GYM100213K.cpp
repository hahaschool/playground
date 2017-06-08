#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 111;
int N,R,C,P;
double S;
int FRM_R[MAXN],FRM_C[MAXN],TO_R[MAXN],TO_C[MAXN];
double DEP[MAXN];
int board[MAXN][MAXN];

int head[MAXN],ed[MAXN*MAXN],nxt[MAXN*MAXN],q;
double len[MAXN*MAXN];
void gphclr(){
    memset(head,0,sizeof(head));
    q = 2;
}
void gphade(int u,int v, double l){
    ed[q] = v;
    len[q] = l;
    nxt[q] = head[u];
    head[u] = q++;
    //cerr << u << "---->" << v << endl;
}

void buildgph(){
    gphclr();
    /*
     for(int i = 0;i <= R+1; i++){
     for(int j = 0;j <= C+1; j++){
     cerr << board[i][j];
     }cerr << endl;
     }*/
    for(int i = 1;i <= N; i++){
        int cnt[MAXN];
        memset(cnt,0,sizeof(cnt));
        //Detect Upper/Lower Bound
        for(int j = FRM_C[i]; j <= TO_C[i]; j++)
            cnt[board[FRM_R[i]-1][j]]++, cnt[board[TO_R[i]+1][j]]++;
        //Detect Left/Right Bound
        for(int j = FRM_R[i]; j <= TO_R[i]; j++)
            cnt[board[j][FRM_C[i]-1]]++, cnt[board[j][TO_C[i]+1]]++;
        for(int j = 1;j <= N; j++)
            if(cnt[j]) gphade(i,j,cnt[j]);
        if(cnt[N+1]) gphade(i,N+1,cnt[N+1]), gphade(N+1,i,cnt[N+1]);
        /*
         for(int j = 1;j <= N+1 ; j++)
         cerr << cnt[j];cerr<<endl;
         */
    }
}

const double EPS = 1e-10;
double remain[MAXN];
inline bool full(int x){
    return remain[x] < EPS;
}

bool done(){
    for(int i = 1;i <= N; i++){
        if(!full(i)) return false;
    }
    return true;
}

double augment(){
    double met[MAXN];
    for(int u = 1;u <= N+1; u++){
        met[u] = 0;
        if(!full(u)){
            for(int i = head[u]; i; i = nxt[i]){
                int v = ed[i];
                if(v != N+1 && full(v))
                    met[u] += len[i];
            }
        }
    }
    double smet = 0;
    for(int i = 1;i <= N+1; i++){
        smet += met[i];
    }
    double flw[MAXN],mitim = 1e11;
    for(int i = 1;i <= N; i++){
        if(full(i)) continue;
        flw[i] = met[i]*S/smet;
        mitim = min(mitim, remain[i]/flw[i]);
    }
    for(int i = 1;i <= N; i++){
        if(full(i)) continue;
        remain[i] -= mitim * flw[i];
    }
    return mitim;
}

void solve(){
    double res = 0;
    res += remain[P]/S;
    remain[P] = 0;
    remain[N+1] = 1e11;
    buildgph();
    while(!done()){
        /*
         cerr << "working" << endl;
         for(int i = 1;i <= N; i++){
         cerr << remain[i] << ' ';
         }cerr << endl;
         */
        res += augment();
    }
    printf("%.20lf\n",res);
}

int main(int argc, char *argv[]){
    freopen("swimming.in","r",stdin);
    freopen("swimming.out","w",stdout);
    while(scanf(" %d %d %d %d %lf",&N,&R,&C,&P,&S) != EOF){
        for(int i = 0;i < MAXN; i++){
            for(int j = 0;j < MAXN; j++){
                board[i][j] = N+1;
            }
        }
        for(int i = 1;i <= N; i++){
            scanf(" %d %d %d %d %lf",&FRM_R[i],&FRM_C[i],&TO_R[i],&TO_C[i],&DEP[i]);
            FRM_R[i]++,FRM_C[i]++;
            for(int j = FRM_R[i]; j <= TO_R[i]; j++){
                for(int k = FRM_C[i]; k <= TO_C[i]; k++){
                    board[j][k] = i;
                }
            }
            remain[i] = (DEP[i]/10.0) * (double)(TO_R[i]-FRM_R[i]+1) * (double)(TO_C[i]-FRM_C[i]+1) * 100;
        }
        solve();
    }
    
    return 0;
}
