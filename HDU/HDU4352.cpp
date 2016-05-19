//
//  HDU4352.cpp
//  playground
//
//  Created by 張正昊 on 6/5/2016.
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
//这个题最重要的思想是LIS的唯一表示方法
//诚然，对于给出的一个数，LIS的形态不止一个，但是我们可以利用nlogn求LIS时候用的思想
//维护一个“长度为k的LIS中最大的那个数最小是多少”的序列，就可以把某个数对应的LIS形态完整且唯一地表示出来
//同时这个数列又一定是单调递增的，这样我们就可以使用状态压缩
//如果想要合并LIS，比如说在233****，我们可以先求出233的唯一表示，然后枚举wildcard的状态表示，合并这两个表示的方法很简单，只要把后面wildcard那一部分的状态表示还原成“长度为k的LIS中最大的那个数最小是多少”的序列，然后挨个插入233对应的序列，重新构造出来一个新序列，如果这个新序列的popcount(1的个数)为k，就是我们要的答案的一部分了。
//设数位DP状态的时候，直接靠拢到记忆化搜索，这样就会设出下面那种用“与答案的距离”来量度的状态了

typedef long long LL;
int bit[20],dig;
int k;
int insert(int s,int v){
    for (int i = v; i <= 9; i++) {
        if (s&(1 << i)) {
            return (s^(1 << i))|(1 << v);
        }
    }
    return s|(1 << v);
}

LL dp[20][20][1050];//答案对应i长度LIS,wildcard长度j,已知部分的LIS CODE为k,满足这样条件的数在wildcard中有多少个
LL dfs(int cur,int Lc,bool wildcard,bool pre0){
    if(!cur) return (__builtin_popcount(Lc)==k)?1:0;
    if(wildcard && dp[k][cur][Lc] != -1) return dp[k][cur][Lc];
    LL ret = 0;
    int end = wildcard?9:bit[cur];
    for (int i = 0; i <= end; i++) {
        if(!i){
            if(pre0) ret += dfs(cur-1,Lc,true,pre0);
            else ret += dfs(cur-1,insert(Lc, i),(!end)?wildcard:true,pre0);
        }else{
            if(i < end) ret += dfs(cur-1,insert(Lc, i),true,false);
            else ret += dfs(cur-1,insert(Lc, i),wildcard,false);
        }
    }
    if(wildcard) dp[k][cur][Lc] = ret;
    return ret;
}

LL solve(LL x){
    dig = 0;
    while (x) {
        bit[++dig] = x%10;
        x /= 10;
    }
    return dfs(dig, 0, false, true);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    memset(dp, -1, sizeof(dp));
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int i = 1; i <= caseCnt; i++){
        printf("Case #%d: ",i);
        LL  a,b;
        cin >> a >> b >> k;
        cout << solve(b) - solve(a-1) << '\n';
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
