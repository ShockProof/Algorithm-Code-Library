#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned long long int uLL;
inline int _Int() { int x; scanf("%d",&x); return x; }
LL bigMod(LL A,LL P,int M){ LL R=1; for(A%=M; P; P>>=1) { if(P&1) R=(R*A)%M; A=(A*A)%M; } return R; } /** (A^P) % M **/
LL negMod(LL A,LL B) { return ( ( ( A % B ) + B) % B ); } /** (A % B) when A is negative or positive **/
#define pb   push_back

const int MOD = 1000000007;
const int M = 2000007;

struct Combinatorics{
        uLL nCr[31][31];

        LL fac[M];

        LL derangement[M];

        void precal()
        {
                for(int i = 0; i < 31; i ++ ) {
                        for(int j = 0; j < 31; j ++ ) {
                                if( j == 0 ) nCr[i][j] = 1;
                                else if( i == 0 ) nCr[i][j] = (j==0);
                                else nCr[i][j] = nCr[i-1][j] + nCr[i-1][j-1];
                        }
                }

                fac[0] = 1;
                for(int i = 1; i < M; i ++ ) {
                        fac[i] = (fac[i-1] * i) % MOD;
                }

                derangement[0] = derangement[2] = 1;
                derangement[1] = 0;
                for(int i = 3; i < M; i ++ ) {
                        derangement[i] = (i-1) * (derangement[i-1]+derangement[i-2]);
                        derangement[i] %= MOD;
                }
        }

        int invFac(int n) {
                return bigMod( fac[n], MOD-2, MOD );
        }
        int nCr_mod(int n, int r) {
                return ( ((fac[n] * invFac(n-r))%MOD) * invFac(r) )%MOD;
        }
        int nth_Catalan_Number(int i) {
                /** (i>=0) 0, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, ... */
                return negMod(nCr_mod(i+i,i)-nCr_mod(i+i,i+1), MOD);
        }
}obj;

void Main()
{
        int n=_Int();
        int r=_Int();
        printf("%d\n", obj.nCr_mod(n+r-1,r-1) );
}

int main()
{
        obj.precal();

        int test=_Int();
        while( test-- ) {
                Main();
        }
        return 0;
}
