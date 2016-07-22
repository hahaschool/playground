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

typedef long long LL;
struct Point{
    LL first,second,times;
    double rad;
    bool operator < (const Point &b) const{
        return rad < b.rad;
    }
};

const int MAXN = 1005;
const LL MODER = 1000000007;
const double EPS = 1e-12;
int n;
Point pt[MAXN];

LL pow2[MAXN];
void prep(){
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = pow2[i-1] * 2LL;
        pow2[i] %= MODER;
    }
}
Point radpt[MAXN];

LL offset;
void solve(){
    LL res = 0;
    for (int bas = 1; bas <= n; bas++) {
        LL contrib = 0;
        LL bas_x = pt[bas].first,bas_y = pt[bas].second,bas_times = pt[bas].times;
        for (int i = 1; i <= n; i++) {
            if(i == bas){
                radpt[i] = {0,0,bas_times,-1};
                continue;
            }
            radpt[i].first = pt[i].first - bas_x;
            radpt[i].second = pt[i].second - bas_y;
            radpt[i].times = pt[i].times;
            radpt[i].rad = atan2(radpt[i].second,radpt[i].first);
        }
        sort(radpt+1, radpt+1+n);
        
        for (int i = 1; i <= n; i++) {
            if(radpt[i].rad < 0 || abs(radpt[i].rad) < EPS) continue;
            int cnt = 0;
            int j;
            for (j = i; j <= n; j++) {
                if(abs(radpt[i].rad-radpt[j].rad) < EPS){
                    cnt += radpt[j].times;
                }else break;
            }
            i = --j;
            contrib += pow2[cnt] - 1;
            contrib %= MODER;
        }
        contrib *= pow2[bas_times]-1;
        contrib %= MODER;
        res += contrib;
        res %= MODER;
    }
    printf("%lld\n",(((res+offset)%MODER)+MODER)%MODER);
}

map<pair<LL, LL>,LL> mp;

int main(int argc, const char * argv[]){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prep();
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        int q;
        scanf(" %d",&q);
        mp.clear();
        for (int i = 1; i <= q; i++) {
            LL a,b;
            scanf(" %lld %lld",&a,&b);
            mp[make_pair(a, b)]++;
        }
        offset = 0;
        n = 1;
        for (map<pair<LL, LL>,LL>::iterator it = mp.begin(); it != mp.end(); it++,n++) {
            pt[n] = {it->first.first,it->first.second,it->second,0};
            offset += pow2[it->second] - it->second - 1;
            offset %= MODER;
        }n--;
        solve();
    }
#ifndef ONLINE_JUDGE
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
