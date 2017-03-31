#include <bits/stdc++.h>
typedef long long int LL;
typedef unsigned long long int uLL;
inline int _Int() {
        int x; scanf("%d",&x); return x;
}
LL bigMod(LL A,LL P,int M) { /** (A^P) % M **/
        LL R=1;
        for( A %= M ; P ; P >>= 1 ) {
                if( P&1 ) R = ( R * A ) % M;
                A = ( A * A ) % M;
        }
        return R;
}
LL bigMul(LL A,LL B,LL M) { /** (A*B) % M **/
        LL R = 0;
        for( A %= M ; B ; B >>= 1 ) {
                if( B&1 ) R = ( R + A ) % M;
                A = ( A + A ) % M;
        }
        return R;
}
LL negMod( LL A , LL B ) { /** (A % B) when A is negative or positive **/
        return ( ( ( A % B ) + B) % B );
}
LL invMod( LL A , LL M ) { /** (A^(-1)) % M */
        return bigMod( A, M-2, M );
}
uLL _pow(uLL A,int P) /** (A^P) **/
{
        uLL R=1;
        for( ; P ; P >>= 1 ) {
                if( P&1 ) R = ( R * A );
                A = ( A * A );
        }
        return R;
}
template<class T>T GCD(T x, T y) { /** Greatest Common Divisor( a , b ) **/
        while(x) x ^= y ^= x ^= y %= x;
        return y;
}
template<class T> bool inRng( T u, T v, T x ) { /** check ( u <= x <=v ) */
        return u <= x && x <= v;
}
#define myMemset(a,b) memset(a,b,sizeof(a))
#define pi            acos(-1)
#define pb            push_back
#define myDebug(x)    cout<<#x<<" : "<<x<<"\n"
