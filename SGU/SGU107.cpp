//
//  SGU107.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/18.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

//make a sheet
/*
 111111111
 119357639
 380642361
 388888889
 611111111
 619357639
 880642361
 888888889
 */


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

using namespace std;

int main(){
    int a = 0;
    scanf("%d",&a);
    if (a <= 8) {
        printf("0\n");
    }else if(a == 9){
        printf("8\n");
    }else{
        printf("72");
        for (int i = 10; i < a; i++) {
            printf("0");
        }
        printf("\n");
    }
    
    return 0;
}
