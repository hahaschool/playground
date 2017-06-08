#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAXN = 44;
int N[2],M[2];
char A[2][MAXN][MAXN];
int mxhe[MAXN][MAXN];
int res_siz,res_n,res_m,res_sel_r[2],res_sel_c[2];
//MDZZ:偏移量并不一定是往右下角的！如果把各个方向的偏移考虑在内根本不用对称着写
void sub_solve(int offset_r,int offset_c,int base){
    //cerr << "-----" << endl << offset_r << ' ' << offset_c << ":" << endl;
    int loc_n,loc_m,i,ai,bi,j,aj,bj;
    if(offset_r < 0) ai = 1-offset_r, bi = 1;
    else ai = 1, bi = 1+offset_r;
    // cerr << ai << ' ' << aj << ' ' << bi << ' ' << bj << endl;
    for(i = 1; ai <= N[base] && bi <= N[base^1]; i++,ai++,bi++){
        if(offset_c < 0) aj = 1-offset_c, bj = 1;
        else aj = 1, bj = 1+offset_c;
        for(j = 1; aj <= M[base] && bj <= M[base^1]; j++,aj++,bj++){
            mxhe[i][j] = (A[base][ai][aj] == A[base^1][bi][bj])?1:0;
        }
        loc_m = j-1;
        for(j = loc_m-1; j >= 1;j--){
            if(mxhe[i][j]) mxhe[i][j] += mxhe[i][j+1];
        }
    }
    loc_n = i-1;
    // cerr << loc_n << ' ' << loc_m << endl;
    static pair<int,int> stk[MAXN];
    static int stk_top;
    for(int cur = 1; cur <= loc_m; cur++){
        stk_top = 0;
        mxhe[0][cur] = mxhe[loc_n+1][cur] = 0;
        for(int i = 0;i <= loc_n+1; i++){
            //cerr << mxhe[i][cur] << ' ';
            //pop stk
            int acc = 0;
            while(stk_top && stk[stk_top].first >= mxhe[i][cur]){
                //attempt update res
                acc += stk[stk_top].second - stk[stk_top-1].second;
                if(stk_top-1 && acc*stk[stk_top].first > res_siz){
                    res_siz = acc*stk[stk_top].first;
                    res_sel_r[base] = stk[stk_top-1].second+1;
                    res_sel_r[base^1] = res_sel_r[base];
                    res_sel_c[base] = cur;
                    res_sel_c[base^1] = res_sel_c[base];
                    if(offset_r < 0) res_sel_r[base] -= offset_r;
                    else res_sel_r[base^1] += offset_r;
                    if(offset_c < 0) res_sel_c[base] -= offset_c;
                    else res_sel_c[base^1] += offset_c;
                    res_n = acc;
                    res_m = stk[stk_top].first;
                    //              cerr << "upd";
                }
                stk_top--;
            }
            //place stk
            stk[++stk_top] = make_pair(mxhe[i][cur],i);
        }
        // cerr << endl;
    }
}

void solve(){
    res_siz = 0;
    for(int i = -N[0]+1;i < N[1]; i++){
        for(int j = -M[0]+1;j < M[1]; j++){
            sub_solve(i,j,0);
            //sub_solve(i,j,1);
        }
    }
    if(res_siz){
        printf("%d %d\n",res_n,res_m);
        printf("%d %d\n",res_sel_r[0],res_sel_c[0]);
        printf("%d %d\n",res_sel_r[1],res_sel_c[1]);
    }else{
        puts("0 0");
    }
}

int main(int argc, char *argv[]){
    // freopen("money.in","r",stdin);
    //freopen("money.out","w",stdout);
    while(scanf(" %d %d",&N[0],&M[0]) != EOF){
        for(int i = 1;i <= N[0]; i++){
            for(int j = 1;j <= M[0]; j++){
                scanf(" %c",&A[0][i][j]);
            }
        }
        scanf(" %d %d",&N[1],&M[1]);
        for(int i = 1;i <= N[1]; i++){
            for(int j = 1;j <= M[1]; j++){
                scanf(" %c",&A[1][i][j]);
            }
        }
        solve();
    }
    return 0;
}
