#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int T,K;
string str;

void flp(int l,int r){
    for(int i = l;i <= r; i++){
        str[i] = str[i]=='+'?'-':'+';
    }
}

int solve(){
    int res = 0;
    for(int i = 0;i + K - 1 < str.size(); i++){
        if(str[i] == '-') {
            flp(i,i+K-1);
            res++;
        }
    }
    for(int i = 0;i < str.size(); i++){
        if(str[i] == '-') return -1;
    }
    return res;
}

int main(){

    scanf(" %d",&T);
    for(int i = 1;i <= T; i++){
        printf("Case #%d: ",i);
        cin >> str >> K;
        int res = solve();
        if(res == -1) puts("IMPOSSIBLE");
        else printf("%d\n",res);
    }

    return 0;
}
