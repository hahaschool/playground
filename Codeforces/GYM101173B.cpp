#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 21;
int N[2];
int mat[MAXN][MAXN];
long long W[2][MAXN];
long long T;


int connect[2][MAXN],tot[2];
long long collector[2][1<<MAXN];
bool subpass[2][1<<MAXN];

void proceed(int side){
    tot[side] = 0;
    for(int i = 1;i <= N[side]; i++){
        connect[side][i] = 0;
        for(int j = 1;j <= N[side^1]; j++){
            if(side == 1)
                if(mat[j][i]) connect[side][i] |= (1 << (j-1));
            if(side == 0)
                if(mat[i][j]) connect[side][i] |= (1 << (j-1));
        }
    }
    subpass[side][0] = true;
    for(int i = 0;i < (1 << N[side]); i++){
        subpass[side][i] = false;
        bool failed = false;
        int sumconnect = 0, popcnt = 0;
        long long sumweight = 0;
        for(int j = 0;j < N[side]; j++){
            if(i & (1 << j)){
                if(!subpass[side][i ^ (1 << j)]){
                    failed = true;
                    break;
                }
                popcnt++;
                sumconnect |= connect[side][j+1];
                sumweight += W[side][j+1];
            }
        }
        if(failed) continue;
        if(__builtin_popcount(sumconnect) >= popcnt){
            collector[side][tot[side]++] = sumweight;
            subpass[side][i] = true;
        }
    }
}

void solve(){
    proceed(0);
    proceed(1);
    sort(collector[0], collector[0]+tot[0]);
    sort(collector[1], collector[1]+tot[1]);
    /*
    for(int i = 0;i < tot[0] ; i++){
        cerr << collector[0][i] << ' ';
    }cerr << endl;
    for(int i = 0;i < tot[1] ; i++){
        cerr << collector[1][i] << ' ';
    }cerr << endl;
    */
    long long res = 0;
    int cur[2] = {0,tot[1]-1};
    for(cur[0] = 0; cur[0] < tot[0]; cur[0]++){
        while(cur[1] >= 0 && collector[0][cur[0]] + collector[1][cur[1]] >= T){
            cur[1]--;
        }
        res += (long long)(tot[1]-1) - (long long)cur[1];
    }
    //printf("%lld\n",res);
    cout << res << '\n';
}

int main(int argc, char *argv[]) {

    while(scanf(" %d %d",&N[0],&N[1]) != EOF){
        for(int i = 1;i <= N[0]; i++){
            for (int j = 1; j <= N[1]; j++) {
                char a;
                scanf(" %c",&a);
                mat[i][j] = a - '0';
            }
        }
        for(int i = 1;i <= N[0]; i++){
            cin >> W[0][i];
            //scanf(" %lld",&W[0][i]);
        }
        for(int i = 1;i <= N[1]; i++){
            cin >> W[1][i];
            //scanf(" %lld",&W[1][i]);
        }
        cin >> T;
        //scanf(" %lld",&T);
        solve();
    }

    return 0;
}
