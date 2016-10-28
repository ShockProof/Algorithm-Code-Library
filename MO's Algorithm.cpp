#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned long long int uLL;

inline unsigned int _Int() {
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    unsigned x=(c-'0');
    while((c=getchar())>='0'&&c<='9')x=((x<<3)+(x<<1))+c-'0';
    return x;
}
/**
    MO's Algorithm
    Given an array of N integers and Q intervals
    In each interval how many distinct values are there
**/
const int M = 200000+7; /// maximum array size

int n,qryC;
int A [ M ];
int blockSize;

struct interval{
    int index;
    int u,v;
    void set(int a, int b, int c) {
        index = a, u = b, v = c;
    }
    bool operator < (const interval &R) const{
        int b1 = u/blockSize, b2 = R.u/blockSize;
        if( b1 != b2 ) return (b1<b2);
        return v < R.v;
    }
} q[ M ];

int fr[ 1000000+7 ];

int distinctValues;
void element(int x, int f) /// f{1,-1} = add or remove flag
{
    fr[ x ] = fr[ x ] + f;
    if( f==+1 && fr[x]==1 ) distinctValues++;
    if( f==-1 && fr[x]==0 ) distinctValues--;
}
int Ans[ M ];

void Main()
{
    n = _Int();
    blockSize = sqrt(n+1);
    qryC = _Int();
    for(int i=1; i<=n; i++) A[i] = _Int();
    for(int i=0,u,v; i<qryC; i++) {
        u = _Int();
        v = _Int();
        q[i].set(i,u,v);
    }
    sort( q, q+qryC );
    int left = 0, right = 0;
    distinctValues = 0;
    for(int x=0; x<qryC; x++) {
        while( right < q[x].v ) element( A[ ++right ],  1 );
        while( right > q[x].v ) element( A[ right-- ], -1 );
        while( left  < q[x].u ) element( A[ left++ ],  -1 );
        while( left  > q[x].u ) element( A[ --left ],   1 );
        Ans[ q[x].index ] = distinctValues;
    }
    for(int i=0; i<qryC; i++) {
        printf("%d", Ans[i] );
        putchar(10);
    }
}
int main()
{
    Main();
    return 0;
}
