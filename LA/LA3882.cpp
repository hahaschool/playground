//
//  LA3882.cpp
//  playground
//
//  Created by 張正昊 on 19/2/2016.
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

int f[10005];
int n,k,m;

int main(){

    int n,m,k;
    while(scanf(" %d %d %d",&n,&k,&m) != EOF)
    {
        if(!m && !k && !n){
            break;
        }
        int s=0;
        for(int i=2;i<=n-1;i++)
            s=(s+k)%i;  //不用开数组哟。
        printf("%d\n",(s+m)%n+1);
    }
    return 0;
}