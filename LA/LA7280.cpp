//
//  LA7280.cpp
//  playground
//
//  Created by 張正昊 on 12/9/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
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
#include <functional>
#include <numeric>
#include <bitset>

#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_R(i,t) for(i = t-1;i >= 0; i--)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define REP_1R(i,t) for(int i = t;i >= 1; i--)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);

using namespace std;

typedef long long LL;
typedef long double LD;

const int MAXN = 255;
int R,C,Q;
int brd[MAXN][MAXN];
int qry[11];
int sum[MAXN][MAXN];

//解说：
//转化问题，注意到题目要求实际上是选定的子矩阵中位数中较大的那个(如果有)要大于等于h
//再次转化，我们把所有大于等于h的项目赋值1，否则赋值-1
//这样问题变为选定一个尽量大的子矩阵，使得子矩阵的和大于等于0
//
//首先考虑枚举一维，我们要枚举子矩阵的开始行数和有多少行，代价是O(R^2)
//然后相当于在矩阵中形成了一个从s行到t行的卡尺
//我们要在这个卡尺中找到一个列区间，这个列区间的所有数加在一起大于等于0
//
//我们想到前缀和处理的话，可以用O(C)的代价得到每一列在卡尺内的数加和
//这样问题转化为给出了一个正负混合的区间，找到一个最长的区间使区间和大于等于0
//
//这个问题比较经典，我们考虑这个数组的前缀和
//如果找一个区间大于等于0的话，实际上相当于我们在前缀和数组上找到一个较大的前缀和对应的最右位置，和找到一个较小的前缀和的最左位置
//这提示我们一个很朴素的方法
//如果开个map,存储不同的前缀和对应的最左位置和最右位置,然后从大到小枚举前缀和作为右端点，在比当前枚举的前缀和中小的点中找最左的左端点，就可以得到当前枚举的前缀和对应的最长区间
//这样做的话，复杂度是O(n^logn)的，然而这个题并不能过
//
//我们考虑进一步优化，我们发现，上面的过程相当于给出了一个曲线(曲线的y轴是前缀和大小，x轴是数组下标)，在曲线上找两个点，左边是较低的点，右边是较高的点
//观察一下这个曲线，如果我们尝试一个右端点，可以和这个右端点配上的左端点一定是右端点左下区域最靠左的那个
//我们把这些可能的左端点标记一下，会发现这些点其实是单调的，即越往右越低（从起点开始，把比起点低的标记，然后比刚才的点低的标记...以此类推）
//同样的，我们可以把"有意义的右端点"也标记出来，也是单调的，越往右越低
//这样，相当于在两个标记带上，找一个左端点，找一个右端点，组成尽量长的区间
//这种单调性提示我们用Two Pointers
//
//尺取这里就比较简单了，每一次尝试向右移进右端点，如果左端点不合适，移进左端点直到合适，同时更新答案。
//
//这样的话，单次卡尺使用尺取法是O(C)的复杂度
//总复杂度O(R^2C)，少了个log，可以过了


void solve(){
    REP_1(q, Q){
        int h = qry[q];
        REP_1(i, R) REP_1(j, C) sum[i][j] = (brd[i][j] >= h)?1:-1;
        REP_1(j, C) REP_1(i, R) sum[i][j] += sum[i-1][j];
        int res = 0;
        static int psm[MAXN],l[MAXN],r[MAXN],ltot,rtot;
        for(int s = 1;s <= R; s++){
            for(int t = s;t <= R; t++){
                REP_1(i, C) psm[i] = sum[t][i] - sum[s-1][i] + psm[i-1];
                ltot = rtot = 0;
                l[++ltot] = 0;
                REP_1(i, C) if(psm[i] < psm[l[ltot]]) l[++ltot] = i;
                r[++rtot] = C;
                REP_1R(i, C) if(psm[i] > psm[r[rtot]]) r[++rtot] = i;
                
                int lp = 1,rp = rtot;
                while (rp) {
                    while (psm[l[lp]] > psm[r[rp]]) lp++;
                    res = max(res,(t-s+1)*(r[rp]-l[lp]));
                    rp--;
                }
            }
        }
        printf("%d\n",res);
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    CASE_LOOP{
        printf("Case %d:\n",__);
        scanf(" %d %d",&R,&C);
        REP_1(i, R) REP_1(j, C) scanf(" %d",&brd[i][j]);
        scanf(" %d",&Q);
        REP_1(i, Q) scanf(" %d",&qry[i]);
        solve();
    }
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
