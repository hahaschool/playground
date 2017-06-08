#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 1000005;
int nxt[MAXN];//exKMP_next[i]表示模式串mode[i~(len-1)]与整个模式串的最长公共前缀长度

void getnext(char *str){
    int len = strlen(str);
    nxt[0] = len;
    int pos = 0;
    while(pos + 1 < len && str[pos] == str[pos+1]){
        pos++;
    }
    nxt[1] = pos;
    pos = 1;
    for(int i = 2;i < len; i++){
        if(nxt[i-pos] + i < nxt[pos] + pos){
            nxt[i] = nxt[i-pos];
        }else{
            int j = nxt[pos] + pos - i;
            if(j < 0){
                j = 0;
            }
            while(i+j < len && str[i+j] == str[j]){
                j++;
            }
            nxt[i] = j;
            pos = i;
        }
    }
}

char str[MAXN];
int N;

int main(){

    scanf(" %s",str);
    N = strlen(str);
    getnext(str);
    long long res = 0;
    for(int i = 0;i < N; i++){
        res += nxt[i];
    }
    cout << res << endl;

    return 0;
}
