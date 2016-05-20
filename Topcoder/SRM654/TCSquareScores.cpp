//
//  TCSquareScores.cpp
//  playground
//
//  Created by 張正昊 on 20/5/2016.
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
const double EPS = 1e-9;

class SquareScores{
public:
    static const int MAXN = 1005,MAXD = 27;
    int chn,len;
    double pch[MAXD];
    double prv[MAXD];
    double calcexpectation(vector<int> p,string a){
        chn = p.size();
        for (int i = 0; i < chn; i++) {
            pch[i] = (double)p[i]/100.0;
        }
        len = a.size();
        memset(prv, 0, sizeof(prv));
        double res = 0;
        for (int i = 0; i < len; i++) {
            if(a[i] == '?'){
                res += 1.0;
                for (int j = 0; j < chn; j++) {
                    res += prv[j]*pch[j];
                    prv[j] = pch[j] * (prv[j]+1.0);
                }
            }else{
                double prvprv = prv[a[i]-'a'];
                res += 1+prv[a[i]-'a'];
                memset(prv, 0, sizeof(prv));
                prv[a[i]-'a'] = prvprv + 1.0;
            }
        }
        return res;
    }
};

SquareScores solver;

void commitTest(vector<int> p,string a){
    cout << solver.calcexpection(p, a) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest({1, 99},"aaaba");
    commitTest({10, 20, 70},"aa?bbbb");
    commitTest({10, 20, 30, 40},"a??c?dc?b");
    commitTest({25, 25, 21, 2, 2, 25},"a??b???????ff??e");
    commitTest({4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4},"??????????????????????????????");
    commitTest({4, 3, 4, 3, 8, 2, 4, 3, 4, 4, 3, 2, 4, 4, 3, 4, 2, 4, 7, 6, 4, 4, 3, 4, 4, 3},"makigotapresentfromniko");
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
