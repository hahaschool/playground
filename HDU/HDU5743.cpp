//
//  HDU5743.cpp
//  playground
//
//  Created by 張正昊 on 24/7/2016.
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

const int MAXN = 44;
struct DisjointSet{
    int par[MAXN*2];
    int n;
    void init(int _n){
        n = _n;
        for(int i = 1;i <= 2*n;i++){
            par[i] = i;
        }
    }
    int find(int x){
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void link(int a,int b){
        int pa = find(a), pb = find(b);
        par[pa] = pb;
    }
    bool isdiff(int a,int b){
        int pa = find(a), pb = find(b);
        int opp_a = a+n,opp_b = b+n;
        int opp_pa = find(opp_a), opp_pb = find(opp_b);
        return (opp_pa == pb && opp_pb == pa);
    }
    bool issame(int a,int b){
        int pa = find(a), pb = find(b);
        int opp_a = a+n,opp_b = b+n;
        int opp_pa = find(opp_a), opp_pb = find(opp_b);
        return (pa == pb && opp_pa == opp_pb);
    }
    bool diff(int a,int b){
        int opp_a = a+n,opp_b = b+n;
        if(issame(a, b)) return false;
        link(a, opp_b);
        link(b, opp_a);
        return true;
    }
    bool same(int a,int b){
        int opp_a = a+n,opp_b = b+n;
        if(isdiff(a, b)) return false;
        link(a, b);
        link(opp_a, opp_b);
        return true;
    }
} dj;


int n,m;
typedef map<int, vector<int> > _MP;
typedef long long LL;
const LL MODER = 1000000007;
LL cnt[MAXN][2],fst[MAXN][2];
const int INF = 0x3f3f3f3f;
_MP mp;
vector<int> vec[MAXN];
bool vis[1 << 20];

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d %d",&n,&m);
        dj.init(n+1);
        mp.clear();
        for (int i = 1; i <= n; i++) {
            int l,r;
            scanf(" %d %d",&l,&r);
            cnt[i][0] = cnt[i][1] = (r-l+1)>>1;
            if((l&1)==(r&1)) cnt[i][l&1]++;
            fst[i][0]=cnt[i][0]?(l&1?(l+1):l):-1;
            fst[i][1]=cnt[i][1]?(l&1?l:(l+1)):-1;
        }
        bool legal = true;
        for (int i = 1; i <= m; i++) {
            int l,r,c;
            scanf(" %d %d %d",&l,&r,&c);
            if(c) legal &= dj.diff(r+1, l);
            else legal &= dj.same(r+1, l);
        }
        if(!legal){
            puts("0");
            puts("-1");
            continue;
        }
        for (int i = 0; i <= n; i++) {
            int l = i+1, r = i+1+n+1;
            int pl = dj.find(l), pr = dj.find(r);
            mp[pl].push_back(i);
            mp[pr].push_back(-i);
        }
        
        
        for (_MP::iterator it = mp.begin(); it != mp.end();) {
            if(it->second.size() == 1){
                it = mp.erase(it);
            }else{
                it++;
            }
        }
        
        
        for(_MP::iterator it = mp.begin();it != mp.end();it++){
            for (_MP::iterator itt = it; itt != mp.end(); itt++) {
                if(it->second.size() == itt->second.size()){
                    bool flg = true;
                    for (int i = 0; i < it->second.size(); i++) {
                        if(it->second[i] + itt->second[i]){
                            flg = false;
                            break;
                        }
                    }
                    if(flg){
                        mp.erase(itt);
                        break;
                    }
                }
            }
        }
        int cur = 0;
        int msk_c = (1 << mp.size()) - 1;
        for (_MP::iterator it = mp.begin(); it != mp.end(); it++,cur++) {
            if(count(it->second.begin(), it->second.end(), 0)){
                if((it->second[1] > 0 && dj.isdiff(1, 1+abs(it->second[1]))) ||
                   (it->second[1] < 0 && dj.issame(1, 1+abs(it->second[1]))) ){
                    for (int i = 0; i < it->second.size(); i++) {
                        it->second[i] *= -1;
                    }
                }
                it->second.erase(find(it->second.begin(),it->second.end(),0));
                msk_c ^= 1 << cur;
            }
            vec[cur] = it->second;
        }
        
        LL res = 0;
        for (int i = 0; i < (1 << mp.size()); i++) vis[i] = false;
        vector<LL> sol,can;
        sol.resize(n);can.resize(n);
        fill(sol.begin(), sol.end(), INF);
        for (int _msk = 0; _msk < (1 << mp.size()); _msk++) {
            //Enumerate
            static int req[MAXN];memset(req, -1, sizeof(req));req[0] = 0;
            int msk = _msk & msk_c;
            if(vis[msk]) continue;vis[msk] = true;
            for (int i = 0; i < mp.size(); i++) {
                int dig = (msk&(1<<i))?1:0;
                for (int j = 0; j < vec[i].size(); j++) {
                    if(vec[i][j] > 0) req[vec[i][j]] = dig;
                    else req[-vec[i][j]] = dig^1;
                }
            }
            
            
            //DP to get contrib
            static LL dp[MAXN][2];memset(dp, 0, sizeof(dp));
            dp[0][0] = 1;
            for (int i = 1; i <= n; i++) {
                if(req[i] == -1){
                    dp[i][0] = dp[i-1][0]*cnt[i][0] + dp[i-1][1]*cnt[i][1];
                    dp[i][0] %= MODER;
                    dp[i][1] = dp[i-1][0]*cnt[i][1] + dp[i-1][1]*cnt[i][0];
                    dp[i][1] %= MODER;
                }else if(req[i] == 1){
                    dp[i][1] = dp[i-1][0]*cnt[i][1] + dp[i-1][1]*cnt[i][0];
                    dp[i][1] %= MODER;
                }else if(req[i] == 0){
                    dp[i][0] = dp[i-1][0]*cnt[i][0] + dp[i-1][1]*cnt[i][1];
                    dp[i][0] %= MODER;
                }
            }
            res += dp[n][0] + dp[n][1];
            res %= MODER;
            
            //Build lexicographically lowest solution
            for (int s = 0; s < 2; s++) {
                fill(can.begin(), can.end(), INF);
                if(!dp[1][s]) continue;
                can[0] = fst[1][s];
                int pre = s;
                bool flg = true;
                for (int i = 2; i <= n; i++) {
                    //Attempt place 0
                    if(dp[i][pre] && fst[i][0] != -1){
                        if(fst[i][0] < can[i-1]){
                            can[i-1] = fst[i][0];
                        }
                    }
                    //Attempt place 1
                    if(dp[i][pre^1] && fst[i][1] != -1){
                        if(fst[i][1] < can[i-1]){
                            pre ^= 1;
                            can[i-1] = fst[i][1];
                        }
                    }
                    if(can[i-1] == INF){
                        flg = false;
                        break;
                    }
                }
                if(flg) sol = min(can,sol);
                
            }
        }
        if(!res){
            puts("0");
            puts("-1");
            continue;
        }
        printf("%lld\n",(res%MODER+MODER)%MODER);
        printf("%d",sol[0]);
        for (int i = 1; i < sol.size(); i++) {
            printf(" %d",sol[i]);
        }
        puts("");
    }
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
