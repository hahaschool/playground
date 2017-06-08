#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define REP_R(i,t) for(int i = t-1;i >= 0; i--)
using namespace std;
namespace Manacher{
    /*
     Manacher Algorithm.
 
     MAXN   : Maximum string length.
     rad    : Maximum panlidrome radius. <0,MAXN>
     tmp    : Alternated string for manacher working process. <0,2*MAXN>
 
     Example:
        hahaschool --> *#h#a#h#a#s#c#h#o#o#l#$ ($ being '\0')
 
 
     #define REP(i,t) for(int i = 0;i < t; i++)
     #define REP_1(i,t) for(int i = 1;i <= t; i++)
 
     Time   : O(n)
     Space  : 3n
     */
    const int MAXN = 1000005;
    char tmp[MAXN*2];
    int rad[MAXN*2];
    void manacher(char *str){
        memset(tmp, 0, sizeof(tmp));
        //将原始字符串插入辅助字符(必须确保下述两个辅助字符没有在字符串中出现过)
        tmp[0] = '*', tmp[1] = '#';
        int len = strlen(str);
        REP(i, len){
            tmp[i*2+2] = str[i];
            tmp[i*2+3] = '#';
        }
        len = (len+1)<<1;
        tmp[len] = 0;
 
        //Manacher主过程
        //id:当前回文串中心 ma:当前回文串右边界
        int id = 0,ma = 0;
        REP_1(i, len-1){//正在处理的右部点
            if(ma > i) rad[i] = min(ma-i,rad[id*2-i]);//拉取当前回文串的"基本长度"
            else rad[i] = 1;//当前处理中心已经超出右边界，只能暴力扩张
            while(tmp[i-rad[i]] == tmp[i+rad[i]]) rad[i]++;//尝试扩张以i为中心的回文串
            if(i + rad[i] > ma){//当以i为中心的回文串超出右边界，要更改中心点和算出新的右边界
                id = i;
                ma = i + rad[i];
            }
        }
    }
}

char str[1000005];
int len;

int main(int argc, char *argv[]){

    scanf(" %s",str);
    Manacher::manacher(str);
    int res = 0;
    len = strlen(str);
    for(int i = 1;i <= (len+1)*2; i++){
        if(i&1){
            res = max(res,(Manacher::rad[i]/2)*2);
        }else{
            res = max(res,((Manacher::rad[i]-1)/2)*2 + 1);
        }
    }
    printf("%d\n",res);

    return 0;
}
