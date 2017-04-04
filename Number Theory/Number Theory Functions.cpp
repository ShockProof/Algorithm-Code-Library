#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned long long int uLL;
inline unsigned int _Int() { int x; scanf("%d",&x); return x; }
uLL _pow(uLL A,int P) { uLL R=1; for(; P; P>>=1) { if(P&1) R=(R*A); A=(A*A); } return R; } /** (A^P) **/

const int RNG = 1000001;
int Prime[RNG], Prime_sz;
int bitsieve[ (RNG>>5)+3 ]; /** bitwise sieve */
bool is_composite(int i) { int x = i>>5; int bit = i-(x<<5); return ( bitsieve[x] & (1<<bit) ); }
void bitsieve_mark(int i){ int x = i>>5; int bit = i-(x<<5); bitsieve[x]=bitsieve[x] | (1<<bit); }
void bitsieve_precal() {
        int sqrtrng = sqrt(RNG)+1 , i,j,k;
        for( i = 4 ; i < RNG ; i += 2 ) bitsieve_mark( i );
        for( i = 3; i < sqrtrng; i ++ ) {
                if( is_composite(i) ) continue;
                for( j = i*i, k=i+i; j < RNG; j += k) bitsieve_mark(j);
        }
        Prime_sz = 0;
        Prime[ Prime_sz++ ] = 2;
        for( i = 3; i < RNG; i += 2 ) {
                if( !is_composite(i) ) Prime[ Prime_sz++ ] = i;
        }
        ///cout<< Prime_sz <<endl;
}

void PrimeFactorization( LL n, LL facList[], int facPow[], int &sz ) {
        int sqrtN = sqrt(n)+1;
        for(int i = sz = 0; i < Prime_sz && Prime[i] < sqrtN; i++ ) {
                if( (n % Prime[i]) != 0 ) continue;
                facList[sz] = Prime[i];
                facPow[sz] = 1;
                n /= Prime[i];
                while( (n % Prime[i])==0 ) {
                        n /= Prime[i];
                        facPow[sz]++;
                }
                sz++, sqrtN = sqrt(n)+1;
        }
        if(n>1) {
                facPow[sz] = 1;
                facList[sz++] = n;
        }
}

bool segsieve_vis[100000+7]; /** segmented sieve */
int segSieve(LL a, LL b) {
        if( b <= 2 ) return ( b == 2 );
        int ret = ( a <= 2 && b >= 2 );
        if( a < 3 ) a = 3;
        if( !( a & 1 ) ) a++;
        memset( segsieve_vis , 0 , sizeof( segsieve_vis ) );
        for(int i = 0; i < Prime_sz; i ++ ) {
                LL x = ( a / Prime[i] ) + ( (a%Prime[i]) != 0 );
                x = ( x * Prime[i] );
                if(x == Prime[i]) x += Prime[i];
                for(LL j = x; j <= b; j += Prime[i] ) {
                        segsieve_vis[j-a] = 1;
                }
        }
        for(int i = 0; i < ( b - a + 1 ); i += 2 ) ret+=(!segsieve_vis[i]);
        return ret;
}

LL P[1000];
int Q[1000], facCount;

LL divisors( LL n )
{
        PrimeFactorization( n , P , Q , facCount );
        LL Ans = 1;
        for( int i = 0 ; i < facCount ; i ++ )
                Ans = Ans * ( Q[i] + 1 );
        return Ans;
}
LL sigmaFunction( LL n )
{
        PrimeFactorization( n , P , Q , facCount );
        LL Ans = 1;
        for( int i = 0 ; i < facCount ; i ++ )
                Ans = Ans * ( ( _pow( P[i] , Q[i] + 1 ) - 1 ) / ( P[i] - 1 ) );
        return Ans;
}
LL eulerPhi( LL n )
{
        PrimeFactorization( n , P , Q , facCount );
        LL Ans = n;
        for( int i = 0 ; i < facCount ; i ++ )
                Ans = ( Ans * ( P[i] + 1 ) ) / P[i];
        return Ans;
}

int fac[RNG], fpw[RNG];
int PrimeFactorization_N_Factorial( int n )
{
        int sz = 0;
        for( int i = 0 ; i < Prime_sz && Prime[i] <= n ; i ++ , sz ++ ) {
                int x = n;
                fac[sz] = Prime[i];
                fpw[sz] = 0;
                while( x > 1 ) {
                        x /= Prime[i];
                        fpw[sz] += x;
                }
        }
        return sz;
}

int main()
{
        bitsieve_precal();
        return 0;
}
