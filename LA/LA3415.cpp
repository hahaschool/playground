//
//  LA3415.cpp
//  playground
//
//  Created by 張正昊 on 4/3/2016.
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

const int MAXN = 505;
int n;
map<string,int> genrehash,sporthash;
int genretot,sporttot;
struct Student{
    int height,gender,genre,sport,id;
} student[MAXN];

int S[MAXN],T[MAXN],Mx[MAXN],My[MAXN],Nx,Ny,W[MAXN][MAXN];
bool aug(int u){
    S[u] = true;
    for (int v = 1; v <= Ny; v++) {
        if (!T[v] && W[u][v]) {
            T[v] =true;
            if (!My[v] || aug(My[v])) {
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
void init(){
    for(int i = 1; i <= Nx; i++){
        S[i] = Mx[i] = 0;
    }
    for(int i = 1; i <= Ny; i++){
        T[i] = My[i] = 0;
    }
}
void flh(){
    for(int i = 1; i<= Nx; i++){
        S[i] = false;
    }
    for(int i = 1; i <= Ny; i++){
        T[i] = false;
    }
}
int hungary(){
    init();
    int ret = 0;
    for(int i = 1; i <= Nx; i++){
        flh();
        if (aug(i)) {
            ret++;
        }
    }
    return ret;
}

void solve(){
    Nx = Ny = 0;
    for(int i = 1; i<= n; i++){
        if (student[i].gender == 1) {
            student[i].id = ++Nx;
        }else{
            student[i].id = ++Ny;
        }
    }
    for(int i = 1; i<= Nx;i++){
        for(int j = 1; j<= Ny; j++){
            W[i][j] = 0;
        }
    }
    for(int i = 1;i <= n; i++){
        for(int j = 1; j <= n; j++){
            if (i != j &&
                abs(student[i].height-student[j].height) <= 40 &&
                student[i].gender != student[j].gender &&
                student[i].genre == student[j].genre &&
                student[i].sport != student[j].sport &&
                student[i].gender == 1) {
                W[student[i].id][student[j].id] = 1;
            }
        }
    }
    printf("%d\n",n-hungary());
}

int main(){
    int caseCnt;
    cin >> caseCnt;
    for(int d = 1;d <= caseCnt;d++){
        cin >> n;
        genrehash.clear(),sporthash.clear();
        genretot = sporttot = 0;
        for(int i = 1; i <= n; i++){
            int h;
            string gender,genre,sport;
            cin >> h >> gender >> genre >> sport;
            if (!genrehash.count(genre)) {
                genrehash[genre] = ++genretot;
            }
            if (!sporthash.count(sport)) {
                sporthash[sport] = ++sporttot;
            }
            student[i] = {h,gender=="M"?1:2,genrehash[genre],sporthash[sport]};
        }
        solve();
    }
    return 0;
}