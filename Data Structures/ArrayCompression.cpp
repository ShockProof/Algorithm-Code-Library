#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }

const int M = 100000 + 7;

struct Compress {
        int compress_st[RNG], compress_sz;
        set< int > compress_vis;
        void compress_call( int compress_A[], int compress_n ) {
                compress_sz = 0;
                compress_vis.clear();
                for(int i=0; i<compress_n; i++) {
                        if( compress_vis.find(compress_A[i])==compress_vis.end() ) {
                                compress_vis.insert( compress_A[i] );
                                compress_st[compress_sz++] = compress_A[i];
                        }
                }
                sort(compress_st,compress_st+compress_sz);
        }
        int compress_rank(int x) {
                int *ite = lower_bound(compress_st,compress_st+compress_sz,x);
                if( (*ite) != x  ) return -1;
                return ite - compress_st + 1;
        }
        int actual(int x) {
                return st[x-1];
        }
}compress;

int Collect[M],Collect_sz;

int n;
int A[M];

void Main()
{
        n=_Int();
        Collect_sz = 0;
        for(int i=1; i<=n; i++) {
                Collect[Collect_sz++] = A[i] = _Int();
        }
        compress.call( Collect, Collect_sz );
        for(int i=1; i<=n; i++)
                cout<< ( A[i] = compress.Rank(A[i]) ) <<" ";
        putchar(10);
}

int main()
{
        int t=_Int();
        while(t--) Main();
        return 0;
}
