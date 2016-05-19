//
//  TCABBA.cpp
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

class ABBA{
public:
    string canObtain(string initial,string target){
        while (target.size() > initial.size()) {
            if(target[target.size()-1] == 'B'){
                target = target.substr(0,target.size()-1);
                reverse(target.begin(), target.end());
            }else target = target.substr(0,target.size()-1);
        }
        if(target == initial){
            return "Possible";
        }else{
            return "Impossible";
        }
    }
};
