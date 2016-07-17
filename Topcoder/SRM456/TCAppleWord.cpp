//
//  TCAppleWord.cpp
//  playground
//
//  Created by 張正昊 on 17/7/2016.
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

class AppleWord{
public:
    int minRep(string word){
        if (word.size() < 5) {
            return -1;
        }
        int res = 0;
        for (int i = 0; i < word.size(); i++) {
            word[i] = tolower(word[i]);
        }
        if(word[0] != 'a') res++;
        for (int i = 1; i < word.size()-2; i++) {
            if(word[i] != 'p') res++;
        }
        if(word[word.size()-2] != 'l') res++;
        if(word[word.size()-1] != 'e') res++;
        return res;
    }
    AppleWord(){
        
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
