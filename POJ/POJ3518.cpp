//
//  POJ3518.cpp
//  playground
//
//  Created by 張正昊 on 6/3/2016.
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

const int MAXN = 2000000;
bool ispr[MAXN];
void makpr(){
    memset(ispr, true, sizeof(ispr));
    for(int i = 2; i < MAXN; i++){
        if (ispr[i]) {
            for(int j = i+i; j < MAXN; j += i){
                ispr[j] = false;
            }
        }
    }
}
int gl[MAXN];
void mkgl(){
    makpr();
    for(int i = 2; i < MAXN;i++){
        if (ispr[i]) {
            gl[i] = 0;
        }else{
            int l = 1;
            int j = i;
            while (!ispr[j] && j < MAXN) {
                l++;
                j++;
            }j--;
            for(int k = i; k <= j; k++){
                gl[k] = l;
            }
            i = j;
        }
    }
    gl[1] = 2;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    mkgl();
    int q;
    while (scanf(" %d",&q) != EOF && q) {
        printf("%d\n",gl[q]);
    }
    return 0;
}
