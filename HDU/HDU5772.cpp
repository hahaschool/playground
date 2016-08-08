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

int biao[32];
void prep(){
    for(int i = 0;i < 32; i++){
        biao[i] = (1<<i)-1;
    }
}

typedef int LL;

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prep();
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        int p,q;
        scanf(" %d %d",&p,&q);
        if(q >= p){
            printf("%d\n",q-p);
        }else{
            if(q == 0){
                printf("%ld\n",lower_bound(biao, biao+32,p)-biao);
                continue;
            }
            LL res = 2*(p-q) - 1;
            LL dlt = p-q;
            LL cst = 0;
            LL stp = 0;
            while (dlt) {
                LL lb = lower_bound(biao, biao+32, dlt)-biao;
                if(biao[lb] == dlt){
                    res = min(res,lb+cst+stp);
                    dlt -= biao[lb];
                }else{
                    if(biao[lb] >= q+dlt){
                        //force down
                        //ISSUE OCCURED HERE
                        res = min(res,max(q,stp)+lb+cst);
                    }
                    
                    //try up
                    LL upp = biao[lb] - dlt;
                    res = min(res,max(upp,stp)+lb+cst);
            
                    //try down
                    lb--;
                    cst += lb;
                    stp++;
                    dlt -= biao[lb];
                }
            }
            printf("%lld\n",res);
        }
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
