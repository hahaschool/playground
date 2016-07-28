//
//  HDU5755.cpp
//  playground
//
//  Created by 張正昊 on 27/7/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

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
int val[99][99];

int pos2id(int r,int c){
    if((r >= 1 && r <= n) && (c >= 1 && c <= m)) return (r-1)*m+c;
    return 0;
}


int equ,var;
int mat[999][999];
int aug[999];
void jordan(){
    int i,j,row,col,mxr;
    for (row = 1,col = 1; row <= equ && col <= var; row++,col++) {
        //Finding column pivot
        mxr = row;
        for (i = row+1; i <= equ; i++) {
            if(mat[i][col] > mat[mxr][col]){
                mxr = i;
            }
        }
        if(mxr != row){
            for(i = col;i <= var;i++){
                swap(mat[row][i], mat[mxr][i]);
            }
            swap(aug[row], aug[mxr]);
        }
        //Zero pivot, skip this column
        if(mat[row][col] == 0){
            row--;
            continue;
        }
        //Elimination procedure
        for (i = 1; i <= equ; i++) {
            if(i != row){
                if(mat[i][col] != 0){
                    aug[i] -= aug[row] * mat[row][col] * mat[i][col];
                    aug[i] %= 3;
                    if(aug[i] < 0) aug[i] += 3;
                    for (j = var; j >= col; j--) {
                        mat[i][j] -= mat[row][j] * mat[row][col] * mat[i][col];
                        mat[i][j] %= 3;
                        if(mat[i][j] < 0) mat[i][j] += 3;
                    }
                }
            }
        }
    }
}

int ans[999];
void solve(){
    memset(mat, 0, sizeof(mat));//ISSUE:initialize required
    memset(aug, 0, sizeof(aug));
    
    //build matrix for gauss-jordan elimination
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            //A_ij + 2X_ij + X_u + X_l + X_d + X_r = 0
            mat[pos2id(i, j)][pos2id(i, j)] = 2;
            mat[pos2id(i, j)][pos2id(i-1, j)] = 1;
            mat[pos2id(i, j)][pos2id(i, j-1)] = 1;
            mat[pos2id(i, j)][pos2id(i+1, j)] = 1;
            mat[pos2id(i, j)][pos2id(i, j+1)] = 1;
            aug[pos2id(i, j)] = (3-val[i][j])%3;
        }
    }
    //commit elimination
    equ = var = n*m;
    jordan();
    //build answer
    int row = 1,sum = 0;
    for (int col = 1; col <= var; col++) {
        if(mat[row][col] == 0){
            ans[col] = 0;
            continue;
        }
        ans[col] = mat[row][col] * aug[row];
        ans[col] %= 3;
        sum += ans[col];
        row++;
    }
    
    printf("%d\n",sum);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= ans[pos2id(i, j)]; k++) {
                printf("%d %d\n",i,j);
            }
        }
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d %d",&n,&m);
        for(int i = 1;i <= n; i++){
            for (int j = 1; j <= m; j++) {
                scanf(" %d",&val[i][j]);
            }
        }
        solve();
    }
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
