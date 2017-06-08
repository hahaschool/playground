#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <cstring>

using namespace std;

int Lside[10] = {3,0,2,0,1,1,3,0,3,1},
    Mside[10] = {5,0,7,7,2,7,7,1,7,7},
    Rside[10] = {3,3,1,3,3,2,2,3,3,3};

inline int make(int x){
    return Rside[x] + (Mside[x]<<4) + (Lside[x]<<9);
}

inline int combine(int a,int b,int c){
    return make(a)|(make(b)<<1)|(make(c)<<2);
}

int W;
int board[10][105];
bool dp[105][16][2];
struct Pointer{
    int ls,cy;
} prv[105][16][2];
struct Selection{
    int u,v,w;
} sel[105][16][2];


inline int extract(int x){
    int ret = 0;
    ret |= board[2][W+2-x];
    ret |= board[4][W+2-x]<<1;
    ret |= board[6][W+2-x]<<2;
    ret |= board[8][W+2-x]<<3;
    ret |= board[1][W+1-x]<<4;
    ret |= board[3][W+1-x]<<5;
    ret |= board[5][W+1-x]<<6;
    ret |= board[7][W+1-x]<<7;
    ret |= board[9][W+1-x]<<8;
    ret |= board[2][W+1-x]<<9;
    ret |= board[4][W+1-x]<<10;
    ret |= board[6][W+1-x]<<11;
    ret |= board[8][W+1-x]<<12;
    return ret;
}

const int msk_L = 0x1E00, msk_M = 0x01F0, msk_R = 0x000F;

char res[3][105];

void buildans(int loc,int cry){
    for(int i = 0;i < W; i++){
        res[0][i] = '0' + sel[W-i][loc][cry].u;
        res[1][i] = '0' + sel[W-i][loc][cry].v;
        res[2][i] = '0' + sel[W-i][loc][cry].w;
        int oloc = loc;
        loc = prv[W-i][loc][cry].ls;
        cry = prv[W-i][oloc][cry].cy;
    }
    res[0][W] = res[1][W] = res[2][W] = '\0';
    puts(res[0]);
    puts(res[1]);
    puts(res[2]);
}

void solve(){

    int cur = extract(1);
    for(int i = 0;i <= 9; i++){
        for(int j = 0;j <= 9; j++){
            int k = (i+j)%10, carry = (i+j)/10;
            int code = combine(i,j,k);
            if((cur&(msk_M|msk_R)) == (code&(msk_M|msk_R))){
                dp[1][(code&msk_L) >> 9][carry] = true;
                sel[1][(code&msk_L) >> 9][carry] = (Selection){i,j,k};
            }
        }
    }

    for(int i = 2;i <= W; i++){
        cur = extract(i);
        memset(dp[i],false,sizeof(dp[i]));
        for(int u = 0;u <= 9; u++){
            for(int v = 0;v <= 9; v++){
                //Considering carry from previous digit
                int w = (u+v+1)%10, carry = (u+v+1)/10;
                int code = combine(u,v,w);
                for(int prvL = 0; prvL < 16 ;prvL++){
                    if(dp[i-1][prvL][1]){
                        if((cur & (msk_M|msk_R)) == ((code&(msk_M|msk_R)) | prvL)){
                            //Transition Accepted
                            dp[i][(code&msk_L) >> 9][carry] = true;
                            sel[i][(code&msk_L) >> 9][carry] = (Selection){u,v,w};
                            prv[i][(code&msk_L) >> 9][carry] = (Pointer){prvL,1};
                        }
                    }
                }

                //Considering no carry
                w = (u+v)%10, carry = (u+v)/10;
                code = combine(u,v,w);
                for(int prvL = 0; prvL < 16 ;prvL++){
                    if(dp[i-1][prvL][0]){
                        if((cur & (msk_M|msk_R)) == ((code&(msk_M|msk_R)) | prvL)){
                            //Transition Accepted
                            dp[i][(code&msk_L) >> 9][carry] = true;
                            sel[i][(code&msk_L) >> 9][carry] = (Selection){u,v,w};
                            prv[i][(code&msk_L) >> 9][carry] = (Pointer){prvL,0};
                        }
                    }
                }
            }
        }
    }

    if(dp[W][(cur&msk_L) >> 9][0]){
        buildans((cur&msk_L) >> 9,0);
    }else{
        puts("NO");
    }

}


int main(int argc, char *argv[]) {

    freopen("digital.in","r",stdin);
    freopen("digital.out","w",stdout);
    while(scanf(" %d",&W) != EOF){
        for(int i = 1;i <= 9; i++){
            if(i&1){
                for(int j = 1;j <= W; j++){
                    scanf(" %d",&board[i][j]);
                }
            }else{
                for(int j = 1;j <= W+1; j++){
                    scanf(" %d",&board[i][j]);
                }
            }
        }
        solve();
    }

    return 0;
}
