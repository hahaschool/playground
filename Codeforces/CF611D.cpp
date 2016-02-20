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

const int MAXN = 5005;
string str;
int n;
int seq[MAXN];
short lcp[MAXN][MAXN];
void getLcp(){
    for(int i = 1; i <= n; i++){
        for(int a = n; a >= 1; a--){
            int b = a+i;
            if(b > n){
                continue;
            }
            if(seq[a] == seq[b]){
                lcp[a][b] = lcp[a+1][b+1]+1;
            }else{
                lcp[a][b] = 0;
            }
        }
    }
}

short lt[MAXN][MAXN];//i:len j:str1 startpos k = j+i:str2 startpos

void preProc(){
    getLcp();
    memset(lt[0], -1, sizeof(lt[0]));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int k = j+i;
            if(k + i - 1 > n){
                break;
            }
            if(lcp[j][k] >= i){
                lt[i][j] = -1;
            }else{
                int of = lcp[j][k];
                if(seq[j+of] < seq[k+of]){
                    lt[i][j] = 1;
                }
            }
        }
    }
}

const long long MODER = 1000000007;
long long dp[MAXN][MAXN];//i: lastpos j:lastGrpSize
long long dsum[MAXN][MAXN];

long long solve(){
    for(int i = 1; i<= n; i++){
        for(int j = 1; j <= i; j++){
            if(i == j && seq[1] != 0){
                dp[i][j] = 1;
                continue;
            }
            int a = i - j;
            if(a <= 0 || seq[a+1] == 0){
                continue;
            }
            long long ret = dsum[a][1] - dsum[a][j];
            ret %= MODER;
            int b = a - j + 1;
            if (b > 0 && lt[j][b] == 1) {
                ret += dp[a][j];
                ret %= MODER;
            }
            dp[i][j] = ret;
        }
        for (int j = n; j >= 1; j--) {
            dsum[i][j] = dsum[i][j+1] + dp[i][j];
            dsum[i][j] %= MODER;
        }
    }
    return dsum[n][1];
}

int main(){
    
    cin >> n >> str;
    for(int i = 1; i <= n; i++){
        seq[i] = str[i-1] - '0';
    }
    preProc();
    cout << (solve()+MODER)%MODER << endl;
    return 0;
}
