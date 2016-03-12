//
//  CF346B.cpp
//  playground
//
//  Created by 張正昊 on 12/3/2016.
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

const int MAXN = 105;
string A,B,V;
int lenA,lenB,lenV;
int dp[MAXN][MAXN][MAXN];
struct State{
    int i,j,k,p;
} prv[MAXN][MAXN][MAXN];
int lt[MAXN];

void getNext(){
    for (int i=1; i<lenV; ++i)
    {
        int j=i;
        while (j>0)
        {
            j=lt[j];
            if (V[j]==V[i])
            {
                lt[i+1]=j+1;
                break;
            }
        }
    }
    lt[0] = -1;
}

inline void UPD(int i,int j,int k,int ii,int jj,int kk){
    if (dp[i][j][k] < dp[ii][jj][kk]) {
        dp[i][j][k] = dp[ii][jj][kk];
        prv[i][j][k] = prv[ii][jj][kk];
    }
}

inline void UPD2(int i,int j,int k,int ii,int jj,int kk,int pp){
    if (dp[i][j][k] < dp[ii][jj][kk] + 1) {
        dp[i][j][k] = dp[ii][jj][kk] + 1;
        prv[i][j][k] = {ii,jj,kk,pp};
    }
}

int main(){
    cin >> A >> B >> V;
    lenA = (int)A.size(),lenB = (int)B.size(),lenV = (int)V.size();
    getNext();
    for (int i = 1; i <= lenA; i++) {
        for (int j = 1; j <= lenB; j++) {
            UPD(i,j,0,i,j-1,0);
            UPD(i,j,0,i-1,j,0);
            for(int k = 1;k <= lenV; k++){
                UPD(i,j,k,i-1,j,k);
                UPD(i,j,k,i,j-1,k);
                
                if (A[i-1] == B[j-1]) {
                    if (A[i-1] == V[k-1]) {
                        UPD2(i,j,k,i-1,j-1,k-1,j);
                    }else{
                        //should use kmp
                        int tk = lt[k-1] + 1;
                        while (tk) {
                            if (A[i-1] == V[tk-1]) {
                                UPD2(i,j,tk,i-1,j-1,k-1,j);
                                break;
                            }else{
                                tk = lt[tk-1] + 1;
                            }
                        }
                        if (!tk) {
                            UPD2(i,j,tk,i-1,j-1,k-1,j);
                        }
                    }
                }
            }
        }
    }
    int res = 0,mii = -1;
    for (int i = 0; i < lenV; i++) {
        if (dp[lenA][lenB][i] > res) {
            res = dp[lenA][lenB][i];
            mii = i;
        }
    }
    State cst = prv[lenA][lenB][mii];
    stack<char> stk;
    while (cst.p) {
        stk.push(B[cst.p-1]);
        cst = prv[cst.i][cst.j][cst.k];
    }
    if (stk.empty()) {
        puts("0");
        return 0;
    }
    while (!stk.empty()) {
        putchar(stk.top());
        stk.pop();
    }
    puts("");
    return 0;
}