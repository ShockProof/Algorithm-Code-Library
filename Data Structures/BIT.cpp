#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
inline int _Int() { int x; scanf("%d",&x); return x; }

const int M = 1000000 + 7;

struct FenwickTree {
        LL Tree[M];
        int sz = M-5;

        LL qry(int i) {
                LL R = 0;
                while( i > 0 ) {
                        R += Tree[i];
                        i -= i & (-i);
                }
                return R;
        }

        LL query(int i, int j) { return qry( j ) - qry( i - 1 ); }

        void update(int i, LL v) {
                while( i<=sz ) {
                        Tree[i]+=v;
                        i += i & (-i);
                }
        }

        void clearIndex(int i) { update( i , -query(i,i) ); }
}ftr;

const int MM = 500;

struct FenwickTree2D {
        int bit[MM][MM];

        int sum( int x, int y ) {
                int R = 0;
                for( int i = x ; i >= 0 ; i = ( i&(i+1) ) -1 )
                        for( int j = y ; j >= 0 ; j = ( j&(j+1) ) -1 ) R += bit[i][j];
                return R;
        }

        void add ( int x, int y , int z ) {
                for( int i = x ; i < MM ; i = (i | (i+1)) )
                        for( int j = y ; j < MM ; j = ( j | (j+1))) bit[i][j] += z;
        }

        void init() { memset( bit , 0 , sizeof(bit) ); }
}f2d;

int main()
{
        return 0;
}
