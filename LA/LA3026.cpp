//
//  LA3026.cpp
//  playground
//
//  Created by 張正昊 on 18/3/2016.
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

const int MAXN = 1000005;
int n;
char str[MAXN];

int lt[MAXN];
int lst[MAXN];

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while (scanf(" %d",&n) != EOF && n) {
        scanf(" %s",str);
        printf("Test case #%d\n",++caseCnt);
        lt[0] = -1,lt[1] = 0;
        for(int i = 2; i<= n; i++){
            lt[i] = 0;
        }
        for(int i = 1; i < n; i++){
            int j = i;
            while (j>0)
            {
                j=lt[j];
                if (str[j]==str[i])
                {
                    lt[i+1]=j+1;
                    break;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (lt[i]) {
                int len = i - lt[i];
                if (i % len == 0) {
                    printf("%d %d\n",i,i/len);
                }
            }
        }
        puts("");
    }
    
    return 0;
}
