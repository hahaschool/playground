#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

struct BipGph{
    static const int MAXN = 222;
    bool S[MAXN],T[MAXN],W[MAXN][MAXN];
    int Mx[MAXN],My[MAXN],Nx,Ny;
    bool aug(int u){
        S[u] = true;
        for(int v = 1; v <= Ny; v++){
            if (!T[v] && W[u][v]) {
                T[v] = true;
                if (!My[v] || aug(My[v])) {
                    My[v] = u;
                    Mx[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
    int hungary(){
        for (int i = 1; i<= Nx; i++) {
            S[i] = Mx[i] = 0;
        }
        for (int i = 1; i <= Ny; i++) {
            T[i] = My[i] = 0;
        }
        int ans = 0;
        for(int i = 1;i <= Nx; i++){
            for (int j = 1; j <= Nx; j++) {
                S[j] = 0;
            }
            for (int j = 1; j <= Ny; j++) {
                T[j] = 0;
            }
            if (aug(i)) {
                ans++;
            }
        }
        return ans;
    }
} matcher[2];

char predefine[111][111];
char modify[111][111];
int N,M;
pair<int,int> ud[111][111];
pair<int,int> rc[222][222];

void make(){
    for(int i = 1;i <= N; i++){
        for(int j = 1,k = N;j <= N; j++,k--){
            ud[i][j].first = ud[i][k].second = i+j-1;
        }
    }
    for(int i = 1;i <= N*2-1; i++){
        for(int j = 1;j <= N*2-1; j++){
            rc[i][j] = make_pair(0,0);
        }
    }
    for(int i = 1;i <= N; i++){
        for(int j = 1;j <= N; j++){
            rc[ud[i][j].first][ud[i][j].second] = make_pair(i,j);
        }
    }
}

void solve(){
    make();
    matcher[0].Nx = matcher[0].Ny = N;
    for(int i = 1;i <= N; i++){
        for(int j = 1;j <= N; j++){
            matcher[0].W[i][j] = 1;
        }
    }
    for(int i = 1;i <= N; i++){
        bool pred = false;
        for(int j = 1;j <= N; j++){
            if(predefine[i][j] == 'x' || predefine[i][j] == 'o'){
                pred = true;
                break;
            }
        }
        if(pred){
            for(int j = 1;j <= N; j++){
                matcher[0].W[i][j] = 0;
            }
        }
        pred = false;
        for(int j = 1;j <= N; j++){
            if(predefine[j][i] == 'x' || predefine[j][i] == 'o'){
                pred = true;
                break;
            }
        }
        if(pred){
            for(int j = 1;j <= N; j++){
                matcher[0].W[j][i] = 0;
            }
        }
    }

    matcher[1].Nx = matcher[1].Ny = N*2-1;
    for(int i = 1;i <= N*2-1; i++){
        for(int j = 1;j <= N*2-1; j++){
            matcher[1].W[i][j] = 0;
            if(rc[i][j].first && rc[i][j].second){
                matcher[1].W[i][j] = 1;
            }
        }
    }

    for(int i = 1;i <= N*2-1; i++){
        bool pred = false;
        for(int j = 1;j <= N*2-1; j++){
            int r = rc[i][j].first, c = rc[i][j].second;
            if(r && c){
                if(predefine[r][c] == '+' || predefine[r][c] == 'o'){
                    pred = true;
                    break;
                }
            }
        }
        if(pred){
            for(int j = 1;j <= N*2-1; j++){
                matcher[1].W[i][j] = 0;
            }
        }
        pred = false;
        for(int j = 1;j <= N*2-1; j++){
            int r = rc[j][i].first, c = rc[j][i].second;
            if(r && c){
                if(predefine[r][c] == '+' || predefine[r][c] == 'o'){
                    pred = true;
                    break;
                }
            }
        }
        if(pred){
            for(int j = 1;j <= N*2-1; j++){
                matcher[1].W[j][i] = 0;
            }
        }
    }

    int res = 0;
    for(int i = 1;i <= N; i++){
        for(int j = 1;j <= N; j++){
            modify[i][j] = 0;
            if(predefine[i][j] == '+' || predefine[i][j] == 'o') res++;
            if(predefine[i][j] == 'x' || predefine[i][j] == 'o') res++;
        }
    }
    //cerr << res << endl;
    matcher[0].hungary();
    for(int i = 1;i <= N; i++){
        if(matcher[0].Mx[i]){
            if(predefine[i][matcher[0].Mx[i]] == '+')  modify[i][matcher[0].Mx[i]] = 'o',res++;
            else modify[i][matcher[0].Mx[i]] = 'x',res++;
        }
    }
    //cerr << res << endl;
    matcher[1].hungary();
    for(int i = 1;i <= N*2-1; i++){
        if(matcher[1].Mx[i]){
            int r = rc[i][matcher[1].Mx[i]].first, c = rc[i][matcher[1].Mx[i]].second;
            if(r && c){
                //cerr << r << "-->" << c << endl;
                if(modify[r][c] == 'x' || predefine[r][c] == 'x') modify[r][c] = 'o',res++;
                else modify[r][c] = '+',res++;
            }
        }
    }
    int cnt = 0;
    for(int i = 1;i <= N; i++){
        for(int j = 1;j <= N; j++){
            if(modify[i][j]) cnt++;
        }
    }
    cout << res << ' ' << cnt << '\n';
    for(int i = 1;i <= N; i++){
        for(int j = 1;j <= N; j++){
            if(modify[i][j]){
                cout << modify[i][j] << ' ' << i << ' ' << j << '\n';
            }
        }
    }
}

int main(int argc, char *argv[]){

    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        scanf(" %d %d",&N,&M);
        for(int i = 1;i <= N; i++){
            for(int j = 1;j <= N; j++){
                predefine[i][j] = 0;
            }
        }
        for(int i = 1;i <= M; i++){
            char pd;
            int r,c;
            scanf(" %c %d %d",&pd,&r,&c);
            predefine[r][c] = pd;
        }
        printf("Case #%d: ",d);
        solve();
    }

    return 0;
}
