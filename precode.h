#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned long long int uLL;
inline int _Int() {
        int x; scanf("%d",&x); return x;
}

/** (A^P) % M **/
LL bigMod(LL A,LL P,int M) {
        LL R=1;
        for( A %= M ; P ; P >>= 1 ) {
                if( P&1 ) R = ( R * A ) % M;
                A = ( A * A ) % M;
        }
        return R;
}

/** (A*B) % M **/
LL bigMul(LL A,LL B,LL M) {
        LL R = 0;
        for( A %= M ; B ; B >>= 1 ) {
                if( B&1 ) R = ( R + A ) % M;
                A = ( A + A ) % M;
        }
        return R;
}

/** (A % B) when A is negative or positive **/
LL negMod( LL A , LL B ) {
        return ( ( ( A % B ) + B) % B );
}

/** (A^(-1)) % M */
LL invMod( LL A , LL M ) {
        return bigMod( A, M-2, M );
}

/** (A^P) **/
uLL _pow(uLL A,int P)
{
        uLL R=1;
        for( ; P ; P >>= 1 ) {
                if( P&1 ) R = ( R * A );
                A = ( A * A );
        }
        return R;
}

/** A*B <= k */
bool mul_in_limit(LL A,LL B,LL k)
{
        LL R = 0;
        LL one = 1LL;
        bool bigA = 0;
        for( ; B ; B >>= one ) {
                if( (B & one) && bigA ) return 0;
                if( (B & one) ) R = ( R + A );
                if( !bigA ) A = ( A + A );
                if( A > k ) bigA = 1;
                if( R > k ) return 0;
        }
        return 1;
}

/** Greatest Common Divisor( a , b ) **/
template<class T>T GCD(T x, T y) {
        while(x) x ^= y ^= x ^= y %= x;
        return y;
}
/** check ( u <= x <=v ) */
template<class T> bool inRng( T u, T v, T x ) {
        return u <= x && x <= v;
}
#define x first
#define y second
#define pi acos(-1)
#define pb push_back
#define myDebug(x) cout<<#x<<" : "<<x<<"\n"

int dir_knight_x[] = { -2, -1, -2, -1, +2, +1, +2, +1 };
int dir_knight_y[] = { -1, -2, +1, +2, -1, -2, +1, +2 };
int dir_x[] = { -1, -1, -1,  0,  0, +1, +1, +1 };
int dir_y[] = { -1,  0, +1, -1, +1, -1,  0, +1 };
