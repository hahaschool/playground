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
const int MAXN = 100005;
LL n;
LL seq[MAXN];

void solve(){
    LL WiSQ = 0,Wi = 0;
    for (int i = 1; i <= n; i++) {
        WiSQ += seq[i] * seq[i];
        Wi += abs(seq[i]);
    }
    LL upper = n*WiSQ - Wi*Wi;
    LL lower = n;
    printf("%lld/%lld\n",upper/__gcd(upper,lower),lower/__gcd(upper,lower));
}

int main(int argc, const char * argv[]){
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1;d <= caseCnt; d++) {
        scanf(" %lld",&n);
        for (int i = 1; i <= n; i++) {
            scanf(" %lld",&seq[i]);
        }
        solve();
    }
    return 0;
}