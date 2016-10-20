#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned long long int uLL;
inline unsigned int _Int() { int x; scanf("%d",&x); return x; }

int Case = 0;

/****************** segmented sieve ******************/
/** works for positive integer range */
int isP[50000],p[6000],pSize;
void sieve()
{
    int i,j;
    pSize = 0;
    for(i=2;i<224;i++) {
        if(!isP[i])
            for(j=i+i;j<50000;j+=i) isP[j]=1;
    }
    for(i=2;i<50000;i++)if(!isP[i])p[pSize++]=i;
}

bool vis[100000+7];

int segSieve(LL a, LL b)
{
    if( b<=2 ) return ( b == 2 );
    int ret = ( a <= 2 && b >= 2 );
    if( a<3 ) a = 3;
    if( !(a&1) ) a++;
    memset(vis,0,sizeof(vis));
    for(int i=0; i<pSize; i++) {
        LL x = (a/p[i])+( (a%p[i])!=0 );
        x = (x*p[i]);
        if(x==p[i]) x+=p[i];
        for(LL j=x; j<=b; j+=p[i]) {
            vis[j-a] = 1;
        }
    }
    for(int i=0; i<(b-a+1); i+=2) ret+=(!vis[i]);
    return ret;
}
/******************************************************/

void Main()
{
    LL a,b;
    scanf("%lld %lld",&a,&b);
    printf("Case %d: %d\n",Case, segSieve(a,b) );
}

int main()
{
    sieve();
    int t=_Int();
    while(t--) {
        Case++;
        Main();
    }
    return 0;
}
