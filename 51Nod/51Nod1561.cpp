//倍增TLE
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 1000005;
char str[MAXN];
int N,A,B;

int seq[MAXN];
int sum_pf[MAXN],sum_sf[MAXN];
int low_pf[MAXN],low_sf[MAXN];
bool elig[MAXN];//is i+1~N|1~i eligible?

#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_R(i,t) for(int i = t-1;i >= 0; i--)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define REP_1R(i,t) for(int i = t;i >= 1; i--)

int wa[MAXN*2],wb[MAXN*2],wv[MAXN*2],wss[MAXN*2];
inline int c0(int *r,int a,int b){
    return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];
}
inline int c12(int k,int *r,int a,int b){
    if(k==2) return r[a] < r[b] || (r[a] == r[b] && c12(1,r,a+1,b+1));
    else     return r[a] < r[b] || (r[a] == r[b] && wv[a+1] < wv[b+1]);
}
void sort(int *r,int *a,int *b,int n,int m){
    /*
      基数排序,b是a中的位置按对应的r中字符大小排序之后的结果
      r : 字符串
      a : 要排序的项目在字符串上的位置
      b : 排序的结果要存储到的数组
      n : 要排序的项目总数
      m : 字符集大小
    */
    REP(i, n) wv[i] = r[a[i]];//从字符串中抽出要排序的项目到wv
    REP(i, m) wss[i] = 0;//重置基数排序数组
    REP(i, n) wss[wv[i]]++;//统计各种字符的数量
    REP_1(i, m-1) wss[i] += wss[i-1];//计算基数排序数组的前缀和以确定排名
    REP_R(i, n-1) b[--wss[wv[i]]] = a[i];//把排序结果写入b数组
}
    
inline int F(const int x,const int tb){
    return x/3 + ((x%3==1)?0:tb);
}
inline int G(const int x,const int tb){
    return (x<tb)?(x*3+1):((x-tb)*3+2);
}
void dc3(int *r,int *sa,int n,int m){
    /*
      rn  : 要递归处理的新字符串
      san : 新字符串对应的后缀数组
      ta  : 起始位置模3为0的后缀总数
      tb  : 起始位置模3为1的后缀总数
      tbc : 起始位置模3为1或2的后缀总数
    */
    int *rn = r+n, *san = sa+n, ta = 0, tb = (n+1)/3, tbc = 0, p;
        
    //PART1: 计算好起始位置模3不等于0的后缀的对应的SA
    //用基数排序把3个字符合并成一个字符
    r[n] = r[n+1] = 0;
    REP(i, n) if(i%3) wa[tbc++] = i;//记录起始位置模3不为0的后缀到wa中
    sort(r+2, wa, wb, tbc, m);//以第三个字符为基准排序
    sort(r+1, wb, wa, tbc, m);//在三准基础上以第二个字符为基准排序
    sort(r, wa, wb, tbc, m);//在二三准基础上以第一个字符为基准排序
    //这样就完成了三个字符的合并
    //根据排序结果求新的字符串
    //F(x) : 计算原字符串起始位置是x的后缀在新字符串中的起始位置
    //c0() : 判定两个字符组是否完全一致
    int i,j;
    for(p = 1,rn[F(wb[0],tb)] = 0,i = 1;i < tbc; i++)
        rn[F(wb[i],tb)] = c0(r, wb[i-1], wb[i])? (p-1):(p++);
        
    if(p < tbc)
        //递归处理新字符串(有些字符组无法区分)
        dc3(rn, san, tbc, p);
    else
        //可以直接求出san的情形(所有的字符组可以区分)
        REP(i, tbc) san[rn[i]] = i;
        
    //PART2: 计算好起始位置模3等于0的后缀对应的SA
    //第二基准的排序结果可以藉由san直接得到
    REP(i, tbc) if(san[i] < tb) wb[++ta] = san[i]*3;
    if(n%3 == 1) wb[ta++] = n-1;//san中没有n-1，所以要特殊处理
    sort(r, wb, wa, ta, m);//第一基准为新加的字符，在算好的第二基准基础上排序
    //把san中的结果做一个反射，因为我们接下来要查询在新字符串中的以x结尾的后缀的排名是多少
    //G(x): 计算新字符串中起始位置为x的后缀在原字符串中的位置
    REP(i, tbc) wv[wb[i] = G(san[i],tb)] = i;
        
    //PART3: 合并前面两部分的结果
    //c12(): 合并时使用的比较
    for(i = j = p = 0;i < ta && j < tbc; p++)
        sa[p] = c12(wb[j]%3, r, wa[i], wb[j])?wa[i++] : wb[j++];
    for(;i < ta; p++) sa[p] = wa[i++];
    for(;j < tbc; p++) sa[p] = wb[j++];
}
int rnk[MAXN*2],height[MAXN*2];
void getHeight(int *r,int *sa,int n){
    int i,j,k = 0;
    REP(i, n) rnk[sa[i]] = i;
    for(i = 0;i < n; height[rnk[i++]] = k)
        if(rnk[i])
            for(k?k--:0,j = sa[rnk[i]-1];r[i+k]==r[j+k];k++);
    return;
}

int s[MAXN*6],sa[MAXN*6],n;

int main(int argc, char *argv[]){

    scanf(" %s",str+1);
    N = strlen(str+1);
    for(int i = 1;i <= N; i++){
        seq[i] = (str[i] == '(')?1:-1;
        if(seq[i] > 0) A++;
        else B++;
    }
    int cur = 0;
    for(int i = 1;i <= N; i++){
        sum_pf[i] = seq[i] + sum_pf[i-1];
        cur += seq[i];
        low_pf[i] = min(low_pf[i-1],cur);
    }
    cur = 0;
    for(int i = N; i >= 1; i--){
        sum_sf[i] = -seq[i] + sum_sf[i+1];
        cur -= seq[i];
        low_sf[i] = min(low_sf[i+1],cur);
    }
    for(int i = 1;i <= N; i++){
        low_sf[i] -= sum_sf[i];
    }
   
    /*
    for(int i = 1;i <= N; i++){
        cerr << sum_pf[i] << ' ' << sum_sf[i] << ' ';
        cerr << low_pf[i] << ' ' << low_sf[i] << endl;
    }
    */

    for(int i = 1;i < N; i++){
        //i+1~N|1~i
        if(A >= B){
            //(((((( )) case
            if(low_sf[i+1] >= 0 && (-sum_sf[i+1]) + low_pf[i] >= 0){
                elig[i] = true;
            }else{
                elig[i] = false;
            }
        }else{
            //(( )))))))) case
            if(B-A + low_sf[i+1] >= 0 && B-A + (-sum_sf[i+1]) + low_pf[i] >= 0){
                elig[i] = true;
            }else{
                elig[i] = false;
            }
        }
    }
    if(low_pf[N] >= 0) elig[N] = true;

    n = 2*N;
    for(int i = 1;i <= N; i++){
        s[i-1] = s[i-1+N] = (str[i] == '(')?1:2;
    }
    s[n] = 0;
    /*
    for(int i = 0;i < n; i++){
        cerr << (int)s[i];
    }cerr << endl;
    */
    dc3(s,sa,n,2);
    
    /*
    for(int i = 0;i < n; i++){
        cerr << sa[i] << ' ';
    }cerr << endl;
    */
    getHeight(s,sa,n);
    
    int mir = 0x3f3f3f3f, miri = 0;
    for(int i = 1;i <= N; i++){
        //if(elig[i]) cerr << i << ' ' << rnk[i] << endl;;
        if(elig[i] && rnk[i] < mir){
            mir = rnk[i];
            miri = i;
        }
    }
    
    for(int i = 1;i <= B-A; i++){
        putchar('(');
    }
    for(int i = miri+1;i <= N; i++){
        putchar(str[i]);
    }
    for(int i = 1;i <= miri; i++){
        putchar(str[i]);
    }
    for(int i = 1;i <= A-B; i++){
        putchar(')');
    }
    puts("");

    return 0;
}
