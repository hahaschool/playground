#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <cmath>
#include <map>
#include <complex>

using namespace std;

int n,m;
int dp[55][3005][15];//dp[dig][mod][lst] = maxrem
int cst[10] = {6,2,5,5,4,5,6,3,7,6};
int fac[55];
int mxd;
void printans(){
    int irem = 0,idig = -1,imod = 0,ilst = -1;
    for(int i = mxd; i > 0; i--){
        for(int j = 9;j >= 0; j--){
            if(dp[i][0][j] != -1){
                idig = i;
                ilst = j;
                irem = dp[i][0][j];
                break;
            }
        }
        if(ilst != -1){
            break;
        }
    }
    
    if(idig == -1){
        printf("-1");
        return;
    }
    if(ilst == 0){//keng
        printf("0");
        return;
    }
    
    int sel = 0;
    while (idig) {
        putchar('0'+ilst);
        sel += cst[ilst];
        idig--;
        imod = ((imod - ilst*fac[idig])%m+m)%m;
        for(int i = 9; i >= 0; i--){
            if(dp[idig][imod][i] >= sel){
                ilst = i;
                break;
            }
        }
    }
    
}
void solve(){
    //init
    mxd = n/2+1;
    for(int i = 0; i <= mxd; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k <  10; k++){
                dp[i][j][k] = -1;
            }
        }
    }
    fac[0] = 1;
    for(int i = 1; i <= mxd; i++){
        fac[i] = fac[i-1] * 10;
        fac[i] %= m;
    }
    
    for(int i = 0; i < 10; i++){
        int rem = n - cst[i];
        if(rem >= 0){
            dp[1][i%m][i] = rem;
        }
    }
    
    for(int i = 1; i <= mxd; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < 10; k++){
                if(dp[i][j][k] != -1){
                    int rem = dp[i][j][k];
                    for(int l = 0; l < 10; l++){
                        if(rem >= cst[l]){
                            int nxt = (l*fac[i]+j)%m;
                            dp[i+1][nxt][l] = max(dp[i+1][nxt][l],rem - cst[l]);
                        }
                    }
                }
            }
        }
    }
    printans();
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while(scanf(" %d",&n) != EOF){
        if(n == 0){
            break;
        }
        scanf(" %d",&m);
        printf("Case %d: ",++caseCnt);
        solve();
        puts("");
    }
    
    
    return 0;
}
