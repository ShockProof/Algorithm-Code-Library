#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned long long int uLL;
inline unsigned int _Int() { int x; scanf("%d",&x); return x; }

int Case = 0;

const int RNG = 1000001;
int Prime[100000], Prime_sz;
struct BitwiseSieve
{
    int is[ (RNG/32)+3 ];
    bool notPrime(int i) {
        int x = i>>5;
        int bit = i-(x<<5);
        return ( is[x] & (1<<bit) );
    }
    void mark(int i) {
        int x = i>>5;
        int bit = i-(x<<5);
        is[x] = is[x]|(1<<bit);
    }
    void unmark(int i) {
        int x = i>>5;
        int bit = i-(x<<5);
        is[x] = is[x]^(1<<bit);
    }
    void precalculations() {
        int MX = sqrt(RNG)+1;
        for(int i=2; i<=MX; i++) {
            if( !notPrime(i) ) {
                for(int j=i+i; j<=RNG; j+=i)
                    mark(j);
            }
        }

        Prime_sz = 0;
        for(int i=2; i<RNG; i++) {
            if( !notPrime(i) ) {
                Prime[Prime_sz++] = i;
            }
        }
        ///cout<< Prime_sz <<endl;
    }
} bitsieve;

void PrimeFactorization( int n, int facList[], int facPow[], int &sz) {
    int sqrtN = sqrt(n)+1;
    for(int i = sz = 0; i<Prime_sz && Prime[i]<sqrtN; i++ ) {
        if( (n%Prime[i]) != 0 ) continue;
        facList[sz] = Prime[i];
        facPow[sz] = 1;
        n/=Prime[i];
        while( (n%Prime[i])==0 ) {
            n/=Prime[i];
            facPow[sz]++;
        }
        sz++;
    }
    if(n>1) {
        facPow[sz] = 1;
        facList[sz++] = n;
    }
}

int divisor(LL x) {
    /** works for x < 10^12 */
    int Ans = 1;
    int sqrtX = sqrt(x);
    for(int i=0; Prime[i]<=sqrtX && x>1 && i<Prime_sz; i++) {
        int cnt = 0;
        while( (x%Prime[i])==0 ) {
            x/=Prime[i];
            cnt++;
        }
        if(cnt) Ans=Ans*(cnt+1);
    }
    if( x>1 ) Ans<<=1;
    return Ans;
}

void Main()
{
    LL n;
    scanf("%lld",&n);
    printf("Case %d: %d\n", Case, divisor(n)-1 );
}

int main()
{
    bitsieve.precalculations();
    int t=_Int();
    while(t--) {
        Case++;
        Main();
    }
    return 0;
}
