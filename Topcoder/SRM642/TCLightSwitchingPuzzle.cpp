//
//  TCLightSwitchingPuzzle.cpp
//  playground
//
//  Created by 張正昊 on 24/5/2016.
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

class LightSwitchingPuzzle{
public:
    string S;
    void flip(int pos){
        S[pos-1] = (S[pos-1]=='Y')?'N':'Y';
    }
    void commit(int a){
        for (int i = a; i <= S.size(); i += a) {
            flip(i);
        }
    }
    
    int minFlips(string stats){
        S = stats;
        int res = 0;
        for (int i = 1; i <= S.size(); i++) {
            if(S[i-1] == 'Y'){
                res++;
                commit(i);
            }
        }
        return res;
    }
    LightSwitchingPuzzle(){}
};

LightSwitchingPuzzle solver;
void commitTest(string s){
    cout << solver.minFlips(s) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest("YYYYYY");
    commitTest("YNYNYNYNY");
    commitTest("NNNNNNNNNN");
    commitTest("YYYNYYYNYYYNYYNYYYYN");
    commitTest("NYNNYNNNYNNNNYNNNNNYNNNNNNYNNNNNNNY");
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
