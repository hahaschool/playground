//
//  TCGoodString.cpp
//  playground
//
//  Created by 張正昊 on 19/5/2016.
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

class GoodString{
public:
    string isGood(string s){
        int stk = 0;
        for (int i = 0; i < s.size(); i++) {
            if(s[i] == 'a'){
                stk++;
            }else{
                if (stk <= 0) {
                    return "Bad";
                }
                stk--;
            }
        }
        if(stk == 0) return "Good";
        return "Bad";
    }
};

GoodString solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.isGood("ab") << endl;
    cout << solver.isGood("aab") << endl;
    cout << solver.isGood("aabb") << endl;
    cout << solver.isGood("ababab") << endl;
    cout << solver.isGood("abaababababbaabbaaaabaababaabbabaaabbbbbbbb") << endl;
    cout << solver.isGood("aaaaaaaabbbaaabaaabbabababababaabbbbaabbabbbbbbabb") << endl;
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
