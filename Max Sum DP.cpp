#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }




struct MaximumSum{
    int _1D[1000000], sz_1D, ss, ee, max_1D;
    int kadane()
    {
        ss = ee = 0, max_1D = _1D[0];
        for(int i=1, k = _1D[0], temp_ss=0; i<sz_1D; i++) {
            k = k + _1D[i];
            if( _1D[i] > k ) {
                k = _1D[i];
                temp_ss = i;
            }
            if( max_1D < k ) {
                max_1D = k;
                ss = temp_ss, ee = i;
            }
        }
        return max_1D;
    }

    int A[105][105], max_2D, Row,Col, left,top,bottom,right;
    int Maximum_2D_sum()
    {
        max_2D = INT_MIN, left=top=bottom=right=0;
        for(int L=0; L<Col; L++) {
            for(int i=0; i<Row; i++) _1D[i]=0;
            for(int R=L; R<Col; R++) {
                for(int i=0; i<Row; i++) _1D[i]+=A[i][R];
                sz_1D = Row;
                kadane();
                if( max_1D > max_2D ) {
                    max_2D = max_1D;
                    left=L, right=R, top=ss, bottom=ee;
                }
            }
        }
        return max_2D;
    }
}MaxSum;









/** --- 3D --- **/
#define For(i,F,T) for(i=F; i<=T; i++)
const int M = 25, inf = 2147483647;
LL dp[M][M][M];
LL Maximum_3D_sum(LL ar[M][M][M], int a, int b, int c) {
    int i,j,k, I,J,K;
    For(i,1,a) For(j,1,b) For(k,1,c)
    {
        LL &R = dp[i][j][k];

        R = ar[i][j][k] + dp[i-1][j-1][k-1] + dp[i-1][j][k]-dp[i][j-1][k-1];
        R +=dp[i][j-1][k] - dp[i-1][j][k-1] + dp[i][j][k-1]-dp[i-1][j-1][k];
    }
    LL ans = -(1LL << 50LL);
    For(i,1,a) For(j,1,b) For(k,1,c) For(I,i,a) For(J,j,b) For(K,k,c)
    {
        LL sum;
        sum  = dp[I][J][K] - dp[i-1][j-1][k-1] + dp[I][j-1][k-1] - dp[i-1][J][K];
        sum += dp[i-1][J][k-1] - dp[I][j-1][K] + dp[i-1][j-1][K] - dp[I][J][k-1];

        if(sum > ans) ans = sum;
    }
    return ans;
}








void Main()
{
    MaxSum.Row = MaxSum.Col = _Int();
    for(int i = 0; i<MaxSum.Row; i++) {
        for(int j=0; j<MaxSum.Col; j++)
            MaxSum.A[i][j] = _Int();
    }
    printf("%d\n", MaxSum.Maximum_2D_sum() );
}

int main()
{
    Main();
    return 0;
}
