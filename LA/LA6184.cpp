//
//  LA6184.cpp
//  playground
//
//  Created by 張正昊 on 6/3/2016.
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

long long n,m,a,b,c,t;

struct Mat
{
    int n, m;
    long long x[55][55];
    Mat(){
        
    }
    Mat(int _n, int _m, int one = 0)
    {
        n = _n;
        m = _m;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                x[i][j] = (i == j) ? one : 0;
    }
};

Mat mul(Mat &a, Mat &b)
{
    Mat c(a.n, b.m);
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < b.m; j++)
        {
            for (int k = 0; k < a.m; k++)
            {
                c.x[i][j] = c.x[i][j] + (a.x[i][k] * b.x[k][j]);
            }
            c.x[i][j] %= m;
        }
    return c;
}

Mat quick_pow(Mat a, long long b)
{
    Mat ret(a.n, a.n, 1);
    while (b)
    {
        if (b & 1)
            ret = mul(ret, a);
        b >>= 1;
        a = mul(a, a);
    }
    return ret;
}

long long seq[55];
Mat A,B;

int main(){
//#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r", stdin);
//#endif
    while (scanf(" %lld %lld %lld %lld %lld %lld",&n,&m,&a,&b,&c,&t) != EOF) {
        if (!n && !m && !a && !b && !c && !t) {
            break;
        }
        A = Mat(n+2,n+2,0);
        B = Mat(n+2,1,0);
        for(int i = 1; i<= n; i++){
            scanf(" %lld",&seq[i]);
        }
        for(int i = 0; i < n+2; i++){
            A.x[0][i] = 0;
        }
        for(int i = 1; i < n+1; i++){
            A.x[i][i-1] = a;
            A.x[i][i] = b;
            A.x[i][i+1] = c;
        }
        for(int i = 0; i < n+2; i++){
            A.x[n+1][i] = 0;
        }
        B.x[0][0] = 0;
        for(int i = 1;i < n+1; i++){
            B.x[i][0] = seq[i];
        }
        B.x[n+1][0] = 0;
        Mat C = quick_pow(A, t);
        Mat D = mul(C, B);
        for(int i = 1; i <= n; i++){
            printf("%lld",D.x[i][0]);
            if (i != n) {
                putchar(' ');
            }else{
                puts("");
            }
        }
    }
    
    return 0;
}



