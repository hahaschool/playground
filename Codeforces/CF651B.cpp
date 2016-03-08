//
//  CF651B.cpp
//  playground
//
//  Created by 張正昊 on 7/3/2016.
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

int cnt[1005];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i<= n; i++){
        int a;
        cin >> a;
        cnt[a]++;
    }
    int res = 0;
    while (true) {
        int hav = -1;
        for(int i = 0; i <= 1000;i++){
            if (cnt[i]) {
                cnt[i]--;
                hav++;
            }
        }
        if (hav != -1) {
            res+=hav;
        }
        else break;
    }
    cout << res << endl;
    return 0;
}