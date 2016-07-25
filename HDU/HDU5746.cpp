#include <stdio.h>
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

const int MAXN = 2005;
int n,m,k;
int p[4];
struct Point{
    int r,c;
    bool operator < (const Point &b) const{
        if(r != b.r) return r < b.r;
        return c < b.c;
    }
} pt[MAXN];
bool cmp_row(const int &a,const int &b){
    if(pt[a].r != pt[b].r) return pt[a].r < pt[b].r;
    return pt[a].c < pt[b].c;
}
bool cmp_col(const int &a,const int &b){
    if(pt[a].c != pt[b].c) return pt[a].c < pt[b].c;
    return pt[a].r < pt[b].r;
}

struct Node{
    int val,prv,nxt;
} list[MAXN*2];
int pos[MAXN];
int list_tot;
void clear(){
    list_tot = -1;
}
int append(int val){
    if(list_tot == -1){
        list[++list_tot] = {val,-1,-1};
        return list_tot;
    }
    list[list_tot].nxt = list_tot+1;
    list[list_tot+1] = {val,list_tot,-1};
    return ++list_tot;
}

void remove(int tar){
    int l = list[tar].prv, r = list[tar].nxt;
    if(l != -1) list[l].nxt = r;
    if(r != -1) list[r].prv = l;
}


int mat_sum[MAXN][MAXN];
int sum(int x1, int x2, int y1, int y2) {
    return mat_sum[x2][y2] - mat_sum[x2][y1 - 1] - mat_sum[x1 - 1][y2] + mat_sum[x1 - 1][y1 - 1];
    
}


int idx_col[MAXN];
int solve(){
    sort(pt+1, pt+1+k);
    for (int i = 1; i <= k; i++) idx_col[i] = i;
    sort(idx_col+1, idx_col+1+k,cmp_col);
    int right = 0 , left = 0;
    for (int i = 0; i < 4; i++) {
        right += p[i] > max(p[0],p[3]);
        left += p[i] < min(p[0],p[3]);
    }
    
    int ret = 0;
    //enumerating lower boundary
    for (int i = 1; i <= k; i++) {
        //build a list with all poosible upper boundary
        //sorted by col
        clear();
        for (int j = 1; j <= k; j++) {
            if(pt[idx_col[j]].r >= pt[i].r){
                pos[idx_col[j]] = append(idx_col[j]);
            }
        }
        
        //enumerating upper boundary
        for (int j = k; pt[j].r > pt[i].r; j--) {
            if((p[0] - p[3]) * (pt[i].c - pt[j].c) <= 0){
                remove(pos[j]);
                continue;
            }
            
            int sel[4],cnt,cur;
            sel[0] = i,sel[1] = j,cnt = 2;
            int d = pt[i].r ,u = pt[j].r ,l = min(pt[i].c,pt[j].c) ,r = max(pt[i].c,pt[j].c);//determine current boundary
            
            
            cur = (p[0] > p[3])?pos[i]:pos[j];//cur is the right point
            for (int h = 0; h < right && list[cur].nxt != -1; h++) {
                cur = list[cur].nxt;
                sel[cnt++] = list[cur].val;
                r = pt[list[cur].val].c;
            }//extend right side
            
            
            cur = (p[0] < p[3])?pos[i]:pos[j];//cur is the left point
            for (int h = 0; h < left && list[cur].prv != -1; h++) {
                cur = list[cur].prv;
                sel[cnt++] = list[cur].val;
                l = pt[list[cur].val].c;
            }//extend left side
            
            
            //Eligibality Check
            if(sum(d,u,l,r) != 4 || cnt != right + left + 2){
                remove(pos[j]);
                continue;
            }
            
            
            int med = 2 - left - right;
            cur = (p[0] > p[3])?pos[i]:pos[j];//cur is the right point
            for (int h = 0;h < med && list[cur].prv != -1; h++) {
                cur = list[cur].prv;
                sel[cnt++] = list[cur].val;
            }
            if(cnt == 4){
                sort(sel, sel+4, cmp_row);
                bool flg = true;
                for(int x = 0;x < 3; x++){
                    flg &= pt[sel[x]].r < pt[sel[x+1]].r;
                }
                for(int x = 0;x < 4 && flg; x++){
                    for (int y = x+1; y < 4; y++) {
                        flg &= (p[x] - p[y]) * (pt[sel[x]].c - pt[sel[y]].c) > 0;
                    }
                }
                ret += flg;
            }
            remove(pos[j]);
        }
    }
    return ret;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d %d %d",&n,&m,&k);
        for (int i = 0; i < 4; i++) {
            scanf(" %d",&p[i]);
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                mat_sum[i][j] = 0;
            }
        }
        for (int i = 1;i <= k; i++) {
            scanf(" %d %d",&pt[i].r,&pt[i].c);
            mat_sum[pt[i].r][pt[i].c] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                mat_sum[i][j] = mat_sum[i][j] + mat_sum[i-1][j] + mat_sum[i][j-1] - mat_sum[i-1][j-1];
            }
        }
        printf("%d\n",solve());
    }
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
