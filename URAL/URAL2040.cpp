#include <iostream>
#include <string>
#include <cstring>
#include <functional>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <set>
#include <ctime>
#include <vector>

using namespace std;

const int MAXN = 5000005,MAXC = 2;

int ch[MAXN][MAXC],_len[MAXN],fail[MAXN],n;
char str[MAXN];
int q,last;

inline bool addchar(char c){
    c -= 'a';
    str[++n] = c;
    int cur = last;
    while(str[n - _len[cur] - 1] != str[n]){
        cur = fail[cur];
    }
    bool flg = false;
    if(!ch[cur][c]){
        flg = true;
        _len[q] = _len[cur]+2;
        int now = q++;
        int failcur = fail[cur];
        while(str[n - _len[failcur] - 1] != str[n]){
            failcur = fail[failcur];
        }
        fail[now] = ch[failcur][c];
        ch[cur][c] = now;
    }
    last = ch[cur][c];
    return flg;
}

char buf[MAXN];
int len;

int main(int argc, char *argv[]) {
    while(true){
        buf[len] = getchar();
        if(buf[len] == '\n'){
            buf[len] = 0;
            break;
        }
        len++;
    }
    _len[q++] = 0;
    _len[q++] = -1;
    str[n] = -1;
    fail[0] = 1;
    addchar(buf[0]);
    buf[0] = '1';
    for(int i = 1;i < len; i++){
        if(addchar(buf[i]))buf[i] = '1';
        else buf[i] = '0';
    }
    puts(buf);
    return 0;
}
