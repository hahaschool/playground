#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 5005, INF = 0x3f3f3f3f;
int ih[MAXN][MAXN],iv[MAXN][MAXN],D0G[MAXN],VG[MAXN],IG[MAXN];
char A[MAXN],B[MAXN];
int NA,NB;

void get_ALCS(){
    for(int i = 0;i <= NB; i++){
        ih[0][i] = i;
    }
    for(int i = 0;i <= NA; i++){
        iv[i][0] = 0;
    }
    for(int i = 1;i <= NA; i++){
        for(int j = 1;j <= NB; j++){
            if(A[i] != B[j]){
                ih[i][j] = max(iv[i][j-1],ih[i-1][j]);
                iv[i][j] = min(iv[i][j-1],ih[i-1][j]);
            }else{
                ih[i][j] = iv[i][j-1];
                iv[i][j] = ih[i-1][j];
            }
        }
    }
    for(int i = 1;i <= NB; i++){
        IG[i] = ih[NA][i];
        VG[i] = INF;
    }
    D0G[0] = 0;
    int i = 1;
    for(int j = 1;j <= NB; j++){a
        if(IG[j] == 0){
            D0G[i] = j;
            i++;
        }else{
            VG[IG[j]] = j;
        }
    }
    for(int j = i;j <= NA; j++){
        D0G[j] = INF;
    }
}

int DG[MAXN][MAXN];
void restore_DG(){
    for(int i = 0;i <= NA; i++){
        DG[0][i] = D0G[i];
    }
    for(int i = 1;i <= NB; i++){
        int cur = 1;
        for(int j = 0;j <= NA; j++){
            if(cur > NA){
                DG[i][j] = INF;
                continue;
            }
            if(VG[i] > DG[i-1][cur-1] && VG[i] < DG[i-1][cur]){
                DG[i][j++] = VG[i];
                DG[i][j] = DG[i-1][cur++];
            }else{
                DG[i][j] = DG[i-1][cur++];
            }
        }
    }
}

int CG[MAXN][MAXN];
void restore_CG(){
    for(int i = 0;i <= NB; i++){
        int cur = 0;
        DG[i][NA+1] = INF;
        for(int j = 0;j <= NA; j++){
            for(;cur < DG[i][j+1] && cur <= NB; cur++){
                CG[i][cur] = j;
            }
        }
    }
}



int main(int argc, char *argv[]){

    scanf(" %s %s",A+1,B+1);
    NA = strlen(A+1);
    NB = strlen(B+1);
    get_ALCS();
    restore_DG();
    restore_CG();

    long long res = 0;
    for(int i = 0;i < NB; i++){
        for(int j = i+1;j <= NB; j++){
            res = (233LL * res + CG[i][j]) % 998244353;
        }
    }
    cout << res << endl;

    /*
    for(int i = 0;i <= NB; i++){
        cerr << VG[i] << ' ' ;
    }cerr << endl;

    for(int i = 0;i <= NB; i++){
        for(int j = 0;j <= NA; j++){
            if(DG[i][j] == INF) cerr << '~' << ' ';
            else cerr << DG[i][j] << ' ';
        }cerr << endl;
    }
    cerr << endl;
    for(int i = 0;i <= NB; i++){
        for(int j = 0;j <= NB; j++){
            cerr << CG[i][j] << ' ';
        }cerr << endl;
    }
    */

    return 0;
}
