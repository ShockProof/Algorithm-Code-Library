#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }

const int M = 100000 + 7;

struct Compress {
        int st[M], sz;
        set<int>vis;
        void call(int A[], int n) {
                sz = 0;
                vis.clear();
                for(int i=0; i<n; i++) {
                        if( vis.find(A[i])==vis.end() ) {
                                vis.insert( A[i] );
                                st[sz++] = A[i];
                        }
                }
                sort(st,st+sz);
        }
        int Rank(int x) {
                int *ite = lower_bound(st,st+sz,x);
                if( (*ite) != x  ) return -1;
                return ite - st + 1;
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
