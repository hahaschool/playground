//
//  TCTheLotteryBothDivs.cpp
//  playground
//
//  Created by 張正昊 on 18/7/2016.
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

class TheLotteryBothDivs{
public:
    vector<string> sfx;
    int n;
    inline long long fac(int a){
        long long ret = 1;
        for (int i = 1; i <= a; i++) {
            ret *= 10LL;
        }
        return ret;
    }
    double solve(){
        bool del[55];
        memset(del, 0, sizeof(del));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(i != j && sfx[i].size() <= sfx[j].size() && sfx[i].size()){
                    bool done = true;
                    for (int k = sfx[i].size()-1,l = sfx[j].size()-1; k >= 0; k--,l--) {
                        if(sfx[i][k] != sfx[j][l]){
                            done = false;
                            break;
                        }
                    }
                    if(done){
                        sfx[j] = "";
                        del[j] = true;
                    }
            }
            }
        }
        long long cnt = 0;
        for (int i = 0; i < n; i++) {
            if(!del[i]){
                cnt += fac(9-sfx[i].size());
            }
        }
        return (double)cnt/1000000000.0;
    }
    
    double find(vector<string> _goodSuffixes){
        sfx = _goodSuffixes;
        n = sfx.size();
        return solve();
    }
    TheLotteryBothDivs(){}
} solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    cout << solver.find({"612829", "752829", "981832829", "413", "51829", "3829", "62385829", "747829", "8960", "914383829", "6749829", "730829", "696829", "91392829", "50458829", "459829", "351829", "4005", "829", "307", "64", "64829", "35829", "0883", "0859829", "501711829", "81829", "13829", "743829", "94829", "244829", "4370829", "46757829", "829", "62810", "700829", "462039829", "93082829", "2071829", "37588", "356829", "837612829", "5670829", "478829", "856443829", "4829", "2829", "829", "10829", "768475829"
}) << endl;
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
