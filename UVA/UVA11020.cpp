//
//  UVA11020.cpp
//  playground
//
//  Created by 張正昊 on 25/3/2016.
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

const int MAXN = 15006;
struct Point{
    int x,y;
    bool operator < (const Point &b)const{
        if(x != b.x) return x < b.x;
        return y < b.y;
    }
};
multiset<Point> st;
typedef multiset<Point>::iterator MSIT;
int n;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        st.clear();
        if(d > 1){
            puts("");
        }
        printf("Case #%d:\n",d);
        scanf(" %d",&n);
        for(int i = 1;i <= n; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            Point cur = {a,b};
            if(st.empty()){
                st.insert(cur);
            }else{
                MSIT lbit = st.lower_bound(cur);
                if(lbit == st.begin() || (--lbit)->y > cur.y){
                    st.insert(cur);
                    MSIT it = st.upper_bound(cur);
                    while (it != st.end() && it->y >= cur.y) {
                        st.erase(it++);
                    }
                }
            }
            printf("%d\n",st.size());
        }
    }
    
    
    return 0;
}
