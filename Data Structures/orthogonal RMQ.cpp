#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
int Case = 0;

const int M = 500+3;

int A[M][M];

int tree[(M*M)<<2];

int build(int node, int x1, int y1, int x2, int y2)
{
        if( x1>x2 || y1>y2 ) {
                return INT_MIN;
        }
        if( x1==x2 && y1==y2 ) {
                return tree[node] = A[x1][y1];
        }
        int c = (node<<2), m1 = (x1+x2)>>1, m2 = (y1+y2)>>1;
        int &ret = tree[node];
        ret = build( c+(-2), x1,y1,m1,m2 );
        ret = max( ret , build( c+(-1), m1+1,y1,x2,m2 ) );
        ret = max( ret , build( c+(0), m1+1,m2+1,x2,y2 ) );
        ret = max( ret , build( c+(1), x1,m2+1,m1,y2 ) );
        return ret;
}

int query(int node, int x1, int y1, int x2, int y2, int a1,int b1, int a2, int b2)
{
        if( x2<a1 || y2<b1 || a2<x1 || b2<y1 ) return INT_MIN;
        if( x1>x2 || y1>y2 ) return INT_MIN;
        if( a1<=x1 && b1<=y1 && x2<=a2 && y2<=b2 ) return tree[node];
        int c = (node<<2), m1 = (x1+x2)>>1, m2 = (y1+y2)>>1;
        int ret = query( c+(-2), x1,y1,m1,m2 ,a1,b1,a2,b2);
        ret = max( ret , query( c+(-1), m1+1,y1,x2,m2 ,a1,b1,a2,b2) );
        ret = max( ret , query( c+(0), m1+1,m2+1,x2,y2 ,a1,b1,a2,b2) );
        ret = max( ret , query( c+(1), x1,m2+1,m1,y2 ,a1,b1,a2,b2) );
        return ret;
}

void Main()
{
        int n=_Int();
        int q=_Int();
        for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                        A[i][j] = _Int();
                }
        }
        printf("Case %d:\n",Case);
        build(1,0,0,n-1,n-1);
        while(q--) {
                int x1=_Int()-1;
                int y1=_Int()-1;
                int z =_Int()-1;
                printf("%d\n",query(1,0,0,n-1,n-1, x1,y1,x1+z,y1+z));
        }
}

int main()
{
        int test=_Int();
        while(test--) {
                Case++;
                Main();
        }
        return 0;
}
