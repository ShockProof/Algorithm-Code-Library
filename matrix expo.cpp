#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
inline int _Int() { int x; scanf("%d",&x); return x; }

int MOD = 10000000+7;
const int D_ME = 2; /** matrix dimension for */
struct Matrix_Exponentiation {

    int matrix[D_ME][D_ME] = { { 1, 1 } , { 1, 0 } };

    void copy(int A[D_ME][D_ME], int B[D_ME][D_ME]) {
        for(int i=0; i<D_ME; i++)
            for(int j=0; j<D_ME; j++)
                A[i][j] = B[i][j];
    }
    int tem[D_ME][D_ME]; /** temporary matrix */
    int expo[D_ME][D_ME];
    void mul(int A[D_ME][D_ME], int B[D_ME][D_ME])
    {
        /** making A = A x B */
        for(int i=0; i<D_ME; i++) {
            for(int j=0; j<D_ME; j++)
            {
                tem[i][j]=0;
                for(int k=0; k<D_ME; k++)
                    tem[i][j]+=(A[i][k]*B[k][j])%MOD;
                tem[i][j]%=MOD;
            }
        }
        copy(A,tem);
    }

    void bigmod(LL power) {
        if( power<=1 ) {
            if( power==1 ) copy(expo,matrix);
            return;
        }
        bigmod(power>>1);
        mul(expo,expo);
        if(power&1) mul(expo,matrix);
    }
}obj;

int main()
{
    /** nth fibonacci number */
    LL n;
    while(scanf("%lld",&n)==1) {
        if( n<2 ) {
            printf("%d\n",n);
            continue;
        }
        obj.bigmod(n-1);
        LL Ans = ( obj.expo[0][0] + obj.expo[0][1]*0 ) % MOD;
        printf("%lld\n", Ans );
    }
    return 0;
}
