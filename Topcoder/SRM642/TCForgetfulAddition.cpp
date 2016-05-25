//
//  TCForgetfulAddition.cpp
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
#include <sstream>

using namespace std;

class ForgetfulAddition{
public:
    
    int minNumber(string expression){
        int lf = 0,rf = 0,res = 2000000001;
        for(int lt = 1;lt < expression.size(); lt++){
            istringstream iss(expression.substr(0,lt));
            iss >> lf;
            istringstream isss(expression.substr(lt,expression.size()-lt));
            isss >> rf;
            res = min(res,lf+rf);
        }
        return res;
    }
    ForgetfulAddition(){}
};

ForgetfulAddition solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.minNumber("22") << endl;
    cout << solver.minNumber("123") << endl;
    cout << solver.minNumber("1289") << endl;
    cout << solver.minNumber("31415926") << endl;
    cout << solver.minNumber("98765") << endl;
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
