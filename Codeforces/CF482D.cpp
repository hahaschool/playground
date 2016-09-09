//
//  CF482D.cpp
//  playground
//
//  Created by 張正昊 on 29/8/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

/*
 去重这里不是很好理解，升序进入染色和降序进入染色的区别其实是颜色交替发生反转
 考虑这种情况 ->ABA->BAB->ABA->
 反转之后 <-ABA<-BAB<-ABA<-
 结果是一样的，也就是说如果有奇数个奇数子树的话，从左染从右染都是一样的
 然后考虑 ->ABAB->ABAB->AB->
 反转 <-ABAB<-ABAB<-AB<-
 这样结果也是一样的，也就是说所有节是偶数节的话，从左染从右染是一样的
 
 我们来研究下别的情况为什么都不一样
 1.如果总的子树点数是奇数的话，首先染到子树的颜色等于最后染到子树的颜色
 2.如果总的子树点数是偶数的话，首先染到子树的颜色相异于最后染到子树的颜色
 我们的染色配置，除了上面的两种情况，就剩下：奇偶混合，偶数个奇数这两种情况
 
 对于偶数个奇数的情况，遂意举个例子一个就可以发现从左染从右染不一样。
 对于奇偶混合的情况，我们考虑把这些子树奇偶性相同的合并到一起成为一个区段，根据上面的1.2.两条结论，通过奇数区段之后，第一个染进去的颜色和接下来的染色会发生交替，通过偶数区段之后，染色不会发生交替。
 要想构造出来从左到右还是从右到左染，初始颜色和终结颜色都相同的情况，等价于构造一个大的偶数区段，然而我们又要求含有奇数区段，这就要求含有“偶数个奇数“的区段，而这样的区段又是显然不一样的。
 
 综上，只有开头说的两种情况会导致向左染向右染结果相同，在计数的时候要减掉
 
 
 */

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
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;


using namespace std;

typedef long long LL;

const int MAXN = 100005;
const LL MODER = 1000000007;

int n;
int par[MAXN];
LL dp[MAXN][2];
vector<int> son[MAXN];

void solve(){
    for(int u = n;u >= 1; u--){
        dp[u][1] = 1;
        dp[u][0] = 0;
        int siz = son[u].size();
        REP(i,siz){
            int v = son[u][i];
            LL a = dp[u][0]*dp[v][0] + dp[u][1]*dp[v][1];
            LL b = dp[u][1]*dp[v][0] + dp[u][0]*dp[v][1];
            dp[u][0] += a;
            dp[u][1] += b;
            dp[u][0] %= MODER,dp[u][1] %= MODER;
        }
        dp[u][0] += dp[u][0];
        dp[u][1] += dp[u][1];
        dp[u][0] %= MODER, dp[u][1] %= MODER;
        LL allEven = 1,oddOdd[2] = {1,0};
        REP(i, siz){
            int v = son[u][i];
            allEven = allEven + allEven * dp[v][0];
            allEven %= MODER;
            LL a = oddOdd[0] + oddOdd[1] * dp[v][1];
            LL b = oddOdd[1] + oddOdd[0] * dp[v][1];
            oddOdd[0] = a % MODER;
            oddOdd[1] = b % MODER;
        }
        dp[u][1] -= allEven;
        dp[u][1] %= MODER;
        if(dp[u][1] < 0) dp[u][1] += MODER;
        dp[u][0] -= oddOdd[1];
        dp[u][0] %= MODER;
        if(dp[u][0] < 0) dp[u][0] += MODER;
    }
    cout << (dp[1][0] + dp[1][1]) % MODER << '\n';
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    scanf(" %d",&n);
    for(int i = 2;i <= n; i++){
        scanf(" %d",&par[i]);
        son[par[i]].emplace_back(i);
    }
    solve();
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
