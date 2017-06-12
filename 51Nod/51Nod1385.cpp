#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 10005;
char str[MAXN];
int n;

int main(int argc, char *argv[]){

    scanf(" %s",str);
    n = strlen(str);
    int res = (n-1)*10;
    int apd = str[0]-'0';
    for(int i = 1;i < n; i++){
        if(str[i] < str[0]){
            apd--;
            break;
        }else if(str[i] > str[0]){
            break;
        }
    }//MDZZ:你要找的是aaaaaaa能不能成立，如果找到一个大于a的一定就能成立了
    cerr << apd << endl;
    printf("%d\n",res+apd);

    return 0;
}
