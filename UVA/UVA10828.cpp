//
//  UVA10828.cpp
//  playground
//
//  Created by 張正昊 on 27/4/2016.
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
int n,ind[MAXN],outd[MAXN];
vector<int> prv[MAXN];
void init(){
    for (int i = 1; i <= n; i++) {
        ind[i] = outd[i] = 0;
        prv[i].clear();
    }
}
void ade(int f,int t){
    prv[t].emplace_back(f);
    ind[t]++,outd[f]++;
}

typedef double Matrix[MAXN][MAXN];

Matrix Mat;
bool inf[MAXN];

const double EPS = 1e-11;//精度要求－11
int dcmp(double a,double b){
    if(abs(a-b) < EPS) return 0;
    else return (a>b)?1:-1;
}
bool isZero(double a){
    return abs(a) < EPS;
}
void jordan(Matrix A,int equ,int var){
    int row,col;
    for (row = 0,col = 0; row < equ && col < var; row++,col++) {
        //PART1:找到当前以及下面行中主元最大的那一行，把它提到当前行上来，如果主元最大为0，说明是自由元，维持行数不变，跳过
        int maxrow = row;
        for(int i = row+1;i < equ; i++){
            if (fabs(A[i][col]) > fabs(A[maxrow][col])) {
                maxrow = i;
            }
        }
        
        if (maxrow != row) {
            for(int i = col;i <= var; i++){
                swap(A[row][i], A[maxrow][i]);
            }
        }
        if (isZero(A[maxrow][col])) {
            //row--;
            //如果使用row--，需要进行阶梯判断
            //否则进行对角线判断
            continue;
        }
        
        
        //PART2:除了主元所在行之外的其他行都进行消元
        for (int i = 0; i < equ; i++) {
            if (i != row) {
                if (!isZero(A[i][col])) {
                    for (int j = var; j >= col; j--) {
                        A[i][j] -= A[row][j]/A[row][col] * A[i][col];
                    }
                }
            }
        }
    }
    //方程组有唯一解时，只有主对角线的系数不为0
    //方程组有无穷解时，用画阶梯的方法找确定变元，剩下的是自由元
    //当确定变元系数为0 增广系数为0 说明这个变量没有依赖的方程
    //当确定变元系数为0 增广系数不为0 说明这个变量联结了矛盾方程
}

double res[MAXN];
void prepare(){
    for (int i = 0; i < n; i++) {
        inf[i] = false;
        for (int j = 0; j <= n; j++) {
            Mat[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        Mat[i][i] -= 1;
        for (int j = 0; j < prv[i+1].size(); j++) {
            Mat[i][prv[i+1][j]-1] += 1.0/(double)outd[prv[i+1][j]];
        }
        if (!i) Mat[i][n] -= 1;
    }
    
    jordan(Mat, n, n);
    
    for (int i = n-1; i >= 0 ; i--) {
        if (isZero(Mat[i][i]) && !isZero(Mat[i][n])) {
                inf[i] = true;
        }
        for (int j = i+1; j < n; j++) {
            if (!isZero(Mat[i][j]) && inf[j]) {
                inf[i] = true;
            }
        }
        res[i] = (isZero(Mat[i][i]))?0:Mat[i][n]/Mat[i][i];
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    int caseCnt = 0;
    while (scanf(" %d",&n) != EOF && n) {
        init();
        printf("Case #%d:\n",++caseCnt);
        int ff,tt;
        while (scanf(" %d %d",&ff,&tt) && ff+tt) {
            ade(ff, tt);
        }
        prepare();
        int q;
        scanf(" %d",&q);
        for (int i = 1; i <= q; i++) {
            int qq;
            scanf(" %d",&qq);
            if (inf[qq-1]) {
                puts("infinity");
                continue;
            }
            printf("%.3lf\n",abs(res[qq-1]));
        }
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}