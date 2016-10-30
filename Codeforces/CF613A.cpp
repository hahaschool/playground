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
#define REP_R(i,t) for(int i = t-1;i >= 0; i--)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define REP_1R(i,t) for(int i = t;i >= 1; i--)
#define REP_ST(i,s,t) for(int i = s;i <= t; i++)
#define REP_STR(i,s,t) for(int i = s;i >= t; i--)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);


using namespace std;

typedef unsigned long long LLU;
typedef long long LL;
typedef long double LD;

#ifdef COMBINATORICS_MOD1E9
const LL MODER = 1000000007;
LL getmod(LL a){if(a<0||a>=MODER)a%=MODER;if(a<0)a+=MODER;return a;}
LL summod(LL a,LL b){return getmod(getmod(a)+getmod(b));}
LL mulmod(LL a,LL b){return getmod(getmod(a)*getmod(b));}
LL powmod(LL a,LL p){LL ret=1;while(p){if(p&1)ret=mulmod(ret,a);a=mulmod(a,a);p>>=1;}return ret;}
LL invmod(LL a){return powmod(a,MODER-2);}
const int MAXBIN = 1005;
LL fac[MAXBIN],facinv[MAXBIN];
void prepbin(){fac[0]=facinv[0]=1;REP_1(i,MAXBIN-1){fac[i]=mulmod(fac[i-1],i);facinv[i]=mulmod(facinv[i-1],invmod(i));}}
LL bin(LL n,LL r){return mulmod(mulmod(fac[n],facinv[n-r]),facinv[r]);}
#endif

#ifdef LOCAL_DEBUG
const int MAXN = 105;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 100005;
#endif

int N;
const double eps = 1e-12;
struct Point{
    double x,y;
    Point(){};
    Point(double x,double y):x(x),y(y){}
    Point operator - (const Point &b) const{
        return Point(x-b.x,y-b.y);
    }
    Point operator + (const Point &b) const{
        return Point(x+b.x,y+b.y);
    }
    Point operator * (const double &d) const{
        return Point(x*d,y*d);
    }
    Point operator / (const double &d) const{
        return Point(x/d,y/d);
    }
    double len(){
        return sqrt(x*x+y*y);
    }
} hull[MAXN];
int dcmp(const double &x){
    return (x > eps) - (x < -eps);
}
double cross(const Point &a,const Point &b){
    return a.x*b.y - a.y*b.x;
}
double dot(const Point &a,const Point &b){
    return a.x*b.x + a.y*b.y;
}
double dis(const Point &a,const Point &b){
    return sqrt(dot(a-b,a-b));
}

double ptoseg(const Point &p,const Point &a,const Point &b){
    if(dcmp(dot(p-a,b-a)<=0)) return dis(p,a);
    if(dcmp(dot(p-b,a-b)<=0)) return dis(p,b);
    return fabs(cross(p-a,b-a))/dis(a,b);
}

Point P;
const double PI = acos(-1);

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (cin >> N) {
        double lg = -1e12,sm = 1e12;
        cin >> P.x >> P.y;
        REP(i, N){
            cin >> hull[i].x >> hull[i].y;
            lg = max(lg,dis(P, hull[i]));
            sm = min(sm,dis(P, hull[i]));
        }
        for(int l = 0,r = 1,i = 1;i <= N; i++,l++,r++,l%=N,r%=N){
            lg = max(lg,ptoseg(P, hull[l], hull[r]));
            sm = min(sm,ptoseg(P, hull[l], hull[r]));
        }
        cout << fixed << setprecision(10) << PI * (lg*lg - sm*sm) << endl;
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
