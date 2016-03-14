//
//  UVA11911.cpp
//  playground
//
//  Created by 張正昊 on 14/3/2016.
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
#include <ext/hash_map>

using namespace std;

int n,m;
map<int,vector<int> > mp;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d %d",&n,&m) != EOF) {
        mp.clear();
        for (int i = 1; i <= n; i++) {
            int a;
            scanf(" %d",&a);
            mp[a].push_back(i);
        }
        for (map<int,vector<int> >::iterator it = mp.begin(); it != mp.end(); it++) {
            vector<int> &vec = it->second;
            sort(vec.begin(), vec.end());
        }
        for (int i = 1; i <= m; i++) {
            int a,b;
            scanf(" %d %d",&b,&a);
            if (b > mp[a].size()) {
                puts("0");
            }else{
                printf("%d\n",mp[a][b-1]);
            }
        }
    }
    
    return 0;
}
