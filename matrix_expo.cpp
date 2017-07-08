#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

const int MOD = 1000000007; const int MatSZ = 3;
void matrixCopy(LL A[MatSZ][MatSZ], LL B[MatSZ][MatSZ]) {
        for(int i=0; i<MatSZ; i++) for(int j=0; j<MatSZ; j++) A[i][j] = B[i][j];
}
LL temMat[MatSZ][MatSZ], expo[MatSZ][MatSZ];
void matrixMul(LL A[MatSZ][MatSZ], LL B[MatSZ][MatSZ]) {
        for(int i=0; i<MatSZ; i++) {
                for(int j=0; j<MatSZ; j++) {
                        temMat[i][j]=0;
                        for(int k=0; k<MatSZ; k++) temMat[i][j]+=(A[i][k]*B[k][j])%MOD;
                        temMat[i][j]%=MOD;
                }
        }
        matrixCopy( A , temMat );
}
LL myMat    [MatSZ][MatSZ] = {
        { 1 , 1 , 0 },
        { 0 , 1 , 1 },
        { 0 , 1 , 0 }
};
LL idenMat  [MatSZ][MatSZ] = {
        { 1 , 0 , 0 },
        { 0 , 1 , 0 },
        { 0 , 0 , 1 }
};
void matrixRaise(LL p) {
        matrixCopy( expo, idenMat );
        int r = 0, c = 0;
        while( p ) {
                r |= (p&1);
                p = p>>1;
                c ++;
                r = r<<1;
        }
        for(r = r >> 1; c; r = (r>>1), c--) {
                matrixMul( expo, expo );
                if( r&1 ) matrixMul( expo , myMat );
        }
}
LL sum_of_nth_fibo(LL n) {
        if( n<=0 ) return 0;
        LL f[MatSZ] = { 0 , 1 , 0 };
        matrixCopy( expo, myMat );
        matrixRaise( n );
        return (expo[0][0] * f[0] + expo[0][1] * f[1] + expo[0][2] * f[2])%MOD;
}




int main()
{
        return 0;
}
