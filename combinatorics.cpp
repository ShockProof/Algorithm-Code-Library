#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
inline int _Int() { int x; scanf("%d",&x); return x; }
LL bigMod(LL A,LL P,int M){ LL R=1; for(A%=M; P; P>>=1) { if(P&1) R=(R*A)%M; A=(A*A)%M; } return R; } /** (A^P) % M **/
#define pb   push_back

const int MOD = 1000000007;
const int M = 2000007;

struct Combinatorics{
    LL fac[M];
    void preCalculations() {
        fac[0] = 1;
        for(int i=1; i<M; i++)
            fac[i] = (fac[i-1]*i)%MOD;
    }
    int invFac(int n) {
        return bigMod( fac[n], MOD-2, MOD );
    }
    int nCr(int n, int r) {
        return ( ((fac[n] * invFac(n-r))%MOD) * invFac(r) )%MOD;
    }
}_math;

void Main()
{
    int n=_Int();
    int r=_Int();
    printf("%d\n", _math.nCr(n+r-1,r-1) );
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
