#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 1000005;

int n;

int linear(int r,int c){
    return c+(r-1)*n;
}

int par[MAXN],dj_tot;
void dj_init(int tot){
    dj_tot = tot;
    for(int i = 1;i <= dj_tot; i++){
        par[i] = i;
    }
}
int dj_find(int x){
    if(par[x] == x) return x;
    return par[x] = dj_find(par[x]);
}
void dj_link(int a,int b){
    int pa = dj_find(a);
    int pb = dj_find(b);
    par[pa] = pb;
}

struct Query{
    int ra,ca,rb,cb;
    int res;
} qry[300005];
char board[1005][1005];
int q;

int ob_hor[1005][1005],ob_vec[1005][1005];
int dp[1005][1005];

vector<pair<int,int> > vec[505];

bool hor_valid(int r,int s,int t){
    return (ob_hor[r][t] - ob_hor[r][s-1]) == 0;
}

bool vec_valid(int c,int s,int t){
    return (ob_vec[c][t] - ob_vec[c][s-1]) == 0;
}

void solve(){
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= n; j++){
            if(board[i][j] == '.'){
                ob_hor[i][j] = ob_vec[j][i] = 0;
            }else {
                ob_hor[i][j] = ob_vec[j][i] = 1;
            }
            ob_hor[i][j] += ob_hor[i][j-1];
            ob_vec[j][i] += ob_vec[j][i-1];
        }
    }
    for(int i = 0;i <= 501; i++){
        vec[i].clear();
    }
    int mx = -1;
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= n; j++){
            dp[i][j] = max(0,dp[i-1][j-1] - 1);
            if(board[i][j] == '#') {
                dp[i][j] = 0;
                continue;
            }
            //ISSUE:没有考虑到左上角是障碍的情况，对于这种情况的有效点要直接加入0幅度数组
            if(board[i-1][j-1] == '#'){
                dp[i][j] = 0;
                vec[0].push_back(make_pair(i, j));
                continue;
            }
            if(i + dp[i-1][j-1] <= n &&
               j - dp[i-1][j-1] >= 1 &&
               j + dp[i-1][j-1] <= n &&
               i - dp[i-1][j-1] >= 1){
                if(hor_valid(i+dp[i-1][j-1],j-dp[i-1][j-1],j+dp[i-1][j-1]) &&
                   vec_valid(j+dp[i-1][j-1],i-dp[i-1][j-1],i+dp[i-1][j-1])){
                    dp[i][j] = dp[i-1][j-1];
                }
            }
            if(i + dp[i-1][j-1] + 1 <= n &&
               j - dp[i-1][j-1] - 1 >= 1 &&
               j + dp[i-1][j-1] + 1 <= n &&
               i - dp[i-1][j-1] - 1 >= 1){
                if(hor_valid(i+dp[i-1][j-1],j-dp[i-1][j-1]-1,j+dp[i-1][j-1]+1) &&
                   vec_valid(j+dp[i-1][j-1],i-dp[i-1][j-1]-1,i+dp[i-1][j-1]+1) &&
                   hor_valid(1+i+dp[i-1][j-1],j-dp[i-1][j-1]-1,j+dp[i-1][j-1]+1) &&
                   vec_valid(1+j+dp[i-1][j-1],i-dp[i-1][j-1]-1,i+dp[i-1][j-1]+1)){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
            }
            mx = max(mx,dp[i][j]);
            vec[dp[i][j]].push_back(make_pair(i,j));
        }
    }
    
    static int dir[4][2] = {{0,-1},{0,1},{1,0},{-1,0}};
    dj_init(n*n);
    for(int i = mx; i >= 0; i--){
        for(int j = 0;j < vec[i].size(); j++){
            int r = vec[i][j].first, c = vec[i][j].second;
            for(int k = 0;k < 4; k++){
                int nr = r+dir[k][0], nc = c+dir[k][1];
                if(board[nr][nc] == '#') continue;
                if(nr >= 1 && nr <= n && nc >= 1 && nc <= n){
                    if(dp[nr][nc] >= dp[r][c]){
                        dj_link(linear(nr,nc),linear(r,c));
                    }
                }
            }
        }
        for(int j = 1;j <= q; j++){
            if(qry[j].res == -1 && dj_find(linear(qry[j].ra,qry[j].ca)) == dj_find(linear(qry[j].rb,qry[j].cb))){
                qry[j].res = i;
            }
        }
    }
    
    for(int i = 1;i <= q; i++){
        printf("%d\n",max(0,qry[i].res*2+1));
    }
}

int main(int argc, char *argv[]){
    /*
     freopen("testdata.in", "r", stdin);
     freopen("output.out", "w", stdout);
*/
    while(scanf(" %d",&n) != EOF){
        for(int i = 1;i <= n; i++){
            for(int j = 1;j <= n; j++){
                scanf(" %c",&board[i][j]);
            }
        }
        scanf(" %d",&q);
        for(int i = 1;i <= q; i++){
            scanf(" %d %d %d %d",&qry[i].ra, &qry[i].ca, &qry[i].rb, &qry[i].cb);
            qry[i].res = -1;
        }
        solve();
    }
    
    return 0;
}
