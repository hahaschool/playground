#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int dig[100];
int n;

void printans(){
    for(int i = 1;i <= n; i++){
        if(dig[i] != 0){
            for(int j = i;j <= n; j++){
                cout << dig[j];
            }
            cout << '\n';
            return;
        }
    }
}

void solve(){
    if(n == 1){
        printans();
        return;
    }
    for(int i = n-1; i >= 1; i--){
        if(dig[i] > dig[i+1]) {
            dig[i]--;
            for(int j = i+1; j <= n; j++){
                dig[j] = 9;
            }
        }
    }
    printans();
}

int main(int argc, char *argv[]){

    int caseCnt = 0;
    scanf(" %d", &caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        string str;
        cin >> str;
        memset(dig,-1,sizeof(dig));
        n = str.size();
        for(int i = 0; i < str.size(); i++){
            dig[i+1] = str[i] - '0';
        }
        printf("Case #%d: ",d);
        solve();
    }

    return 0;
}
