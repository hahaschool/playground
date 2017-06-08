#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 1000005;
char str[MAXN];
int nxt[MAXN];
long long N,K;
void kmp(char *s,int *a,int n){
    a[0] = -1;
    int t = -1;
    for(int i = 1;i <= n; i++){
        while(t >= 0 && s[t+1] != s[i])
            t = a[t];
        a[i] = ++t;
    }
}

int lop[MAXN];

int main(int argc, char *argv[]){
    cin >> N >> K;
    scanf("%s",str+1);
    kmp(str,nxt,N);
    /*
    for(int i = 1;i <= N; i++){
        cerr << nxt[i] << ' ';
    }cerr << endl;
    */
    for(int i = 1;i <= N; i++){
        if(i%(i-nxt[i]) == 0){
            lop[i] = i/(i-nxt[i]);
        }else{
            lop[i] = 1;
        }
        if(lop[i] - K*(lop[i]%K) >= 0){
            putchar('1');
            continue;
        }
        long long la = nxt[i]%(i-nxt[i]);
        long long lb = i-nxt[i]-la;
        long long rem = i-(K+1)*la-K*lb;
        if(la && lb && rem >= 0 && rem%(i-nxt[i]) == 0){
            long long m = rem/(i-nxt[i]);
            if(m-K*(m%K) >= 0) putchar('1');
            else putchar('0');
        }else putchar('0');
    }puts("");
    /*
    for(int i = 1;i <= N; i++){
        cerr << lop[i];
    }cerr << endl;
    */

    return 0;
}
