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
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : ty))
#define G(x) ((x) < ty ? (x) * 3 + 1 : ((x) - ty) * 3 + 2)

template<typename T = char>
struct SuffixArray {
    int str[MAXN * 6], sa[MAXN * 6], rank[MAXN*2], height[MAXN*2], sz;
    int wa[MAXN*2], wb[MAXN*2], wv[MAXN*2], ws[MAXN*2];
    
    int &operator [](int k) { return sa[k]; }
    
    int size() const { return sz; }
    
    bool eq(const int *r, int a, int b) const {
        return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
    }
    
    bool cmp(const int *r, int a, int b, int d) const {
        if (d == 1) return (r[a] < r[b]) || (r[a] == r[b] && wv[a + 1] < wv[b + 1]);
        return (r[a] < r[b]) || (r[a] == r[b] && cmp(r, a + 1, b + 1, 1));
    }
    
    void rsort(const int *r, const int *a, int *b, int n, int m) {
        int i;
        fill(ws, ws + m, 0);
        for (i = 0; i < n; ++i) ++ws[wv[i] = r[a[i]]];
        for (i = 1; i < m; ++i) ws[i] += ws[i - 1];
        for (i = n - 1; ~i; --i) b[--ws[wv[i]]] = a[i];
    }
    
    void dc3(int *r, int *sa, int n, int m) {
        int i, j, k, *rn = r + n, *san = sa + n, tx = 0, ty = (n + 1) / 3, tz = 0;
        
        r[n] = r[n + 1] = 0;
        for (i = 0; i < n; ++i) {
            if (i % 3) wa[tz++] = i;
        }
        rsort(r + 2, wa, wb, tz, m);
        rsort(r + 1, wb, wa, tz, m);
        rsort(r, wa, wb, tz, m);
        for (rn[F(wb[0])] = 0, k = i = 1; i < tz; ++i) {
            rn[F(wb[i])] = eq(r, wb[i - 1], wb[i]) ? k - 1 : k++;
        }
        if (k < tz) dc3(rn, san, tz, k);
        else {
            for (i = 0; i < tz; ++i) san[rn[i]] = i;
        }
        for (i = 0; i < tz; ++i) {
            if (san[i] < ty) wb[tx++] = san[i] * 3;
        }
        if (n % 3 == 1) wb[tx++] = n - 1;
        rsort(r, wb, wa, tx, m);
        for (i = 0; i < tz; ++i) wv[wb[i] = G(san[i])] = i;
        for (i = j = k = 0; i < tx && j < tz; ++k) {
            sa[k] = cmp(r, wa[i], wb[j], wb[j] % 3) ? wa[i++] : wb[j++];
        }
        for ( ; i < tx; ++i) sa[k++] = wa[i];
        for ( ; j < tz; ++j) sa[k++] = wb[j];
    }
    
    void build(const T *s, int n, int m = 128) {
        int i;
        for (i = 0; i < n; ++i) str[i] = (int)s[i];
        str[n] = 0; sz = n + 1;
        dc3(str, sa, sz, m);
    }
    
    void calHeight() {
        int i, j, k = 0;
        for (i = 0; i < sz; ++i) rank[sa[i]] = i;
        for (i = 0; i < sz; height[rank[i++]] = k) {
            for(k ? --k : 0, j = sa[rank[i] - 1]; str[i + k] == str[j + k]; ++k);
        }
    }
};

SuffixArray<> sa;
char s[MAXN*6];
int n;

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
        s[i-1] = s[i-1+N] = (str[i] == '(')?'a':'b';
    }
    s[n] = 0;
    /*
     for(int i = 0;i < n; i++){
     cerr << (int)s[i];
     }cerr << endl;
     */
    sa.build(s, n);
    sa.calHeight();
    
    /*
     for(int i = 1;i <= n; i++){
     cerr << sa[i] << ' ';
     }cerr << endl;
    for(int i = 1;i <= n; i++){
        cerr << sa.rank[i-1] << ' ';
    }cerr << endl;
    */
    
    
    int mir = 0x3f3f3f3f, miri = 0;
    for(int i = 1;i <= N; i++){
        //if(elig[i]) cerr << i << ' ' << sa.rank[i] << endl;;
        if(elig[i] && sa.rank[i] < mir){
            mir = sa.rank[i];
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
