#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }

const int RNG = 100000 + 7;

int compress_set [ RNG ], compress_set_sz;
set< int > compress_vis;

void compress_call( int A[], int n ) {
        compress_set_sz = 0;
        compress_vis.clear();
        for(int i = 0; i < n; i ++ ) {
                if( compress_vis.find( A[i] ) == compress_vis.end() ) {
                        compress_vis.insert( A[i] );
                        compress_set[compress_set_sz++] = A[i];
                }
        }
        sort( compress_set , compress_set + compress_set_sz );
}
int compress_rank(int x) {
        int *ite = lower_bound( compress_set , compress_set + compress_set_sz , x );
        if( (*ite) != x  ) return -1;
        return ite - compress_set + 1;
}
int compress_actual(int x) {
        return compress_set[x-1];
}

int Collect[RNG],Collect_sz;

int n;
int A[RNG];

void Main()
{
        n=_Int();
        Collect_sz = 0;
        for(int i=1; i<=n; i++) {
                Collect[Collect_sz++] = A[i] = _Int();
        }
        compress_call( Collect, Collect_sz );
        for(int i=1; i<=n; i++)
                cout<< ( A[i] = compress_rank(A[i]) ) <<" ";
        putchar(10);
}

int main()
{
        int t=_Int();
        while(t--) Main();
        return 0;
}
