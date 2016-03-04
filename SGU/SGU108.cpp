//
//  SGU108.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/18.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

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

bool isself[100];
vector<pair<int, int> > goal;
int container[5005];

bool cmp(pair<int, int> a,pair<int, int> b){
    return a.first < b.first;
}

int main(){
    int n = 0,k = 0;
    scanf(" %d %d",&n,&k);
    goal.clear();
    for (int i = 1; i <= k; i++) {
        int tmp = 0;
        scanf(" %d",&tmp);
        goal.push_back(make_pair(tmp, i));
    }
    sort(goal.begin(), goal.end(),cmp);
    memset(isself, true, sizeof(isself));
    memset(container, 0, sizeof(container));
    int cnt = 0;
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        if (isself[i%64]) {
            cnt++;
            while (cnt == goal[cur].first) {
                container[goal[cur].second] = i;
                cur++;
            }
        }
        int tmp = i,sum = i;
        while (tmp != 0) {
            sum += tmp%10;
            tmp /= 10;
        }
        isself[sum%64] = false;
        isself[i%64] = true;
    }
    printf("%d\n",cnt);
    for (int i = 1;i < k; i++) {
        printf("%d ",container[i]);
    }
    printf("%d\n",container[k]);
    return 0;
}
