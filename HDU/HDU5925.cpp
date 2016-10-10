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

const int MAXN = 998;
LL gridline_vertical[MAXN],vtot;
LL gridline_horizontal[MAXN],htot;
struct Block{
    int typ;
    LL r,c;
} grid[MAXN][MAXN];

LL R,C;
int n;
struct Point{
    LL r,c;
} pt[MAXN];


void build_grid(){
    vtot = htot = 0;
    gridline_vertical[vtot++] = 0;
    gridline_vertical[vtot++] = C;
    gridline_horizontal[htot++] = 0;
    gridline_horizontal[htot++] = R;
    REP_1(i, n){
        gridline_horizontal[htot++] = pt[i].r-1;
        gridline_horizontal[htot++] = pt[i].r;
        gridline_vertical[vtot++] = pt[i].c - 1;
        gridline_vertical[vtot++] = pt[i].c;
    }
    sort(gridline_horizontal, gridline_horizontal+htot);
    sort(gridline_vertical, gridline_vertical+vtot);
    vtot = unique(gridline_vertical, gridline_vertical+vtot) - gridline_vertical;
    htot = unique(gridline_horizontal, gridline_horizontal+htot) - gridline_horizontal;
    
    for(int u = 0,d = 1,rid = 1;d < htot; u++,d++,rid++){
        LL upos = gridline_horizontal[u],dpos = gridline_horizontal[d];
        for(int l = 0,r = 1,cid = 1;r < vtot; l++,r++,cid++){
            LL lpos = gridline_vertical[l], rpos = gridline_vertical[r];
            bool kuro = false;
            for(int i = 1;i <= n; i++){
                if(pt[i].r == dpos && pt[i].c == rpos){
                    kuro = true;
                    break;
                }
            }
            
            if (kuro) grid[rid][cid].typ = 1;
            else grid[rid][cid].typ = 0;
            grid[rid][cid].r = dpos - upos;
            grid[rid][cid].c = rpos - lpos;
        }
    }
}

inline bool isValid(int r,int c){
    if(r <= 0 || r >= htot) return false;
    if(c <= 0 || c >= vtot) return false;
    if(grid[r][c].typ == 1) return false;
    return true;
}

int belong[MAXN][MAXN],idtot = 0;
int dir[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};
void dfs(int r,int c,int id){
    belong[r][c] = id;
    for(int i = 0; i < 4; i++){
        int nr = r + dir[i][0];
        int nc = c + dir[i][1];
        if(isValid(nr, nc) && belong[nr][nc] == -1){
            dfs(nr, nc, id);
        }
    }
}

map<int,LL> area;

void solve(){
    build_grid();
    memset(belong, -1, sizeof(belong));
    for(int i = 1;i < htot; i++){
        for(int j = 1;j < vtot; j++){
            if(isValid(i, j) && belong[i][j] == -1){
                dfs(i,j,++idtot);
            }
        }
    }
    area.clear();
    for(int i = 1;i < htot; i++){
        for(int j = 1;j < vtot; j++){
            if(belong[i][j] != -1)
            area[belong[i][j]] += grid[i][j].r * grid[i][j].c;
        }
    }
    
    printf("%d\n",(int)area.size());
    vector<LL> vec;
    for(map<int,LL>::iterator it = area.begin(); it != area.end(); it++){
        vec.push_back(it->second);
    }
    sort(vec.begin(),vec.end());
    for(int i = 0;i < vec.size(); i++){
        printf("%lld",vec[i]);
        if(i == vec.size()-1) puts("");
        else putchar(' ');
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    CASE_LOOP{
        printf("Case #%d:\n",__);
        scanf(" %lld %lld %d",&R,&C,&n);
        REP_1(i,n) scanf(" %lld %lld",&pt[i].r,&pt[i].c);
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
