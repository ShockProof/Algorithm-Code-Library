#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned long long int uLL;
inline int _Int() { int x; scanf("%d",&x); return x; }
LL bigMod(LL A,LL P,int M){ LL R=1; for(A%=M; P; P>>=1) { if(P&1) R=(R*A)%M; A=(A*A)%M; } return R; } /** (A^P) % M **/
#define pb   push_back

const int MOD = 1000000007;
const int M = 2000007;

struct Combinatorics{
    uLL nCr[31][31];

    LL fac[M];
    void preCalculations() {

        for(int i=0; i<31; i++) {
            for(int j=0; j<31; j++) {
                if( j==0 ) nCr[i][j] = 1;
                else if( i==0 ) nCr[i][j] = (j==0);
                else nCr[i][j] = nCr[i-1][j] + nCr[i-1][j-1];
            }
        }

        fac[0] = 1;
        for(int i=1; i<M; i++) {
            fac[i] = (fac[i-1]*i)%MOD;
        }
    }

    int invFac(int n) {
        return bigMod( fac[n], MOD-2, MOD );
    }
    int nCr_mod(int n, int r) {
        return ( ((fac[n] * invFac(n-r))%MOD) * invFac(r) )%MOD;
    }
    int nth_Catalan_Number(int i) {
        return negMod(nCr_mod(i+i,i)-nCr_mod(i+i,i+1), MOD);
    }
}_math;

void Main()
{
    int n=_Int();
    int r=_Int();
    printf("%d\n", _math.nCr_mod(n+r-1,r-1) );
}

int main()
{
    _math.preCalculations();
    int test=_Int();
    while( test-- ) {
        Main();
    }
    return 0;
}
