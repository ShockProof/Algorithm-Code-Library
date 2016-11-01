#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

LL joseph(LL n,LL k) {
    if (n==1LL) return 0LL;
    if (k==1LL) return n-1LL;
    if (k>n) return (joseph(n-1LL,k)+k)%n;
    LL cnt=n/k;
    LL R=joseph(n-cnt,k);
    R-=n%k;
    if (R<0LL) R+=n;
    else R+=R/(k-1LL);
    return R; /** maybe you need to return R+1 */
}



int main()
{
    int n,k;
    while( scanf("%d%d",&n,&k)==2 ) {
        if( !n &&!k ) return 0;
        cout<<n <<" "<<k <<" "<< joseph( n,k )+1 <<endl;
    }
    return 0;
}
