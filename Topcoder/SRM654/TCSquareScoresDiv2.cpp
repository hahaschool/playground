//
//  TCSquareScoresDiv2.cpp
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

class SquareScoresDiv2{
public:
    static const int MAXD = 26;
    int prv[MAXD];
    int getscore(string s){
        int res = 0;
        memset(prv,0,sizeof prv);
        for (int i = 0; i < s.size(); i++) {
            int prvprv = prv[s[i]-'a']+1;
            memset(prv, 0, sizeof(prv));
            res += prvprv;
            prv[s[i]-'a'] = prvprv;
        }
        return res;
    }
};

SquareScoresDiv2 solver;

void commitTest(string a){
    cout << solver.getscore(a) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest("aaaba");
    commitTest("zzzxxzz");
    commitTest("abcdefghijklmnopqrstuvwxyz");
    commitTest("p");
    commitTest("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
