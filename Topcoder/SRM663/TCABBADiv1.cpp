//
//  TCABBADiv1.cpp
//  playground
//
//  Created by 張正昊 on 13/5/2016.
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

class ABBADiv1{
public:
    string init,targ;
    bool dfs(string cur){
        if(cur.size() == init.size()){
            return cur == init;
        }
        if(cur[0] == 'B'){
            string rev = cur.substr(1,cur.size()-1);
            reverse(rev.begin(), rev.end());
            if(dfs(rev)) return true;
        }
        if(cur[cur.size()-1] == 'A'){
            if(dfs(cur.substr(0,cur.size()-1))) return true;
        }
        return false;
    }
    
    string canObtain(string initial,string target){
        init = initial,targ = target;
        if(dfs(target)){
            return "Possible";
        }else{
            return "Impossible";
        }
    }
    
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    string a,b;
    ABBADiv1 solver;
    while (cin >> a >> b) {
        cout << solver.canObtain(a, b) << endl;
    }
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
