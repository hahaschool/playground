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

using namespace std;

typedef long long LL;

const int MAXN = 10005;
const double EPS = 1e-12;
double N,W,V,U;

struct Point{
    double x,y;
};
Point convex[MAXN];



int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cin >> N >> W >> V >> U;
    for(int i = 1;i <= N; i++){
        cin >> convex[i].x >> convex[i].y;
    }

    double u_u = -1e12,u_l = 1e12,
    l_l = 1e12,l_d = 1e12,
    d_d = 1e12,d_r = -1e12,
    r_r = -1e12,r_u = -1e12;
    int ul = 0,ld = 0,dr = 0,ru = 0;
    for(int i = 1;i <= N; i++){
        if(abs(convex[i].y - u_u) < EPS){
            if(convex[i].x < u_l){
                u_l = convex[i].x;
                ul = i;
            }
        }else{
            if(convex[i].y > u_u){
                u_u = convex[i].y;
                u_l = convex[i].x;
                ul = i;
            }
        }
        if(abs(convex[i].x - l_l) < EPS){
            if(convex[i].y < l_d){
                l_d = convex[i].y;
                ld = i;
            }
        }else{
            if(convex[i].x < l_l){
                l_l = convex[i].x;
                l_d = convex[i].y;
                ld = i;
            }
        }
        if(abs(convex[i].y-d_d) < EPS){
            if(convex[i].x > d_r){
                d_r = convex[i].x;
                dr = i;
            }
        }else{
            if(convex[i].y < d_d){
                d_d = convex[i].y;
                d_r = convex[i].x;
                dr = i;
            }
        }
        if(abs(convex[i].x-r_r) < EPS){
            if(convex[i].y > r_u){
                r_u = convex[i].y;
                ru = i;
            }
        }else{
            if(convex[i].x > r_r){
                r_r = convex[i].x;
                r_u = convex[i].y;
                ru = i;
            }
        }
    }
    
    
    if(convex[ru].x < 0){
        //direct pass
        printf("%.8lf\n",W/U);
    }else{
        //try L
        if(l_l > 0){
            if(l_l/V > l_d/U){
                //can arrive L
                bool done = true;
                double pos = (l_l/V)*U;
                int cur = ld;
                if(cur != ul)
                for(int i = 1;i < N; i++){
                    int prv = cur-1;if(prv<=0)prv+=N;
                    if(pos < convex[cur].y){
                        done = false;
                        break;
                    }else{
                        pos += ((convex[prv].x - convex[cur].x)/V)*U;
                    }
                    cur--;if(cur<=0)cur+=N;
                    if(cur == ul) break;
                }
                if(pos < u_u) done = false;
                if(done){
                    printf("%.8lf",W/U);
                    return 0;
                }
            }
        }
        
        //try R
        int cur = dr;
        for(int i = 1;i <= N; i++){
            if(convex[cur].x>0) break;
            cur++;if(cur > N) cur-=N;
        }
        double use = convex[cur].x/V;
        double pos = min(use*U,convex[cur].y);
        if(cur!=ru)
        for(int i = 1;i <= N; i++){
            int nxt = cur+1;if(nxt>N)nxt-=N;
            double pst = (convex[nxt].x - convex[cur].x)/V;
            pos = min(pos+pst*U,convex[nxt].y);
            use += pst;
            cur++;if(cur>N)cur-=N;
            if(cur == ru) break;
        }
        use += (W-pos)/U;
        printf("%.8lf\n",use);
        
    }
    
    
    
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
