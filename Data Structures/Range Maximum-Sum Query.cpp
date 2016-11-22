#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int M = 50000 + 3; int n; LL A[M];
struct Range_MaxSum_Query {
    struct NodeDesign{
        LL ans, sum;   LL left, right;   bool isBlank;
        void single( int i ) { sum = ans = A[i]; left  = A[i]; right = A[i]; }
        void twoChield( NodeDesign &c1, NodeDesign &c2 ) {
            sum = c1.sum + c2.sum;
            ans = max( max(c1.ans, c2.ans), c1.right+c2.left );
            left = max( c1.left, c1.sum + c2.left );
            right = max( c2.right, c2.sum + c1.right );
        }
        void twoChieldCopy( NodeDesign c1, NodeDesign c2 ) { this->twoChield( c1,c2 ); }
    } tree[M*3];
    void build( int node, int u, int v ) {
        tree[node].isBlank = 0;
        if( u==v ) {
            tree[node].single( u );
            return;
        }
        int mid = (u+v)>>1, c = (node<<1); int c2 = c+1;
        build( c,    u, mid );
        build( c2, mid+1, v );
        tree[node].twoChield( tree[c],tree[c2] );
    }
    void update(int node, int u, int v, int x, LL y) {
        if( v<x || x<u ) return;
        if( u==v ) {
            A[u] = y;
            tree[node].single( u );
            return;
        }
        int mid = (u+v)>>1, c = (node<<1); int c2 = c+1;
        update( c,    u, mid , x,y );
        update( c2, mid+1, v , x,y );
        tree[node].twoChield( tree[c],tree[c2] );
    }
    NodeDesign Ret;
    void query(int node, int u, int v, int x, int y) {
        if( v<x || y<u ) return ;
        if( x <= u && v <= y ) {
            if(Ret.isBlank) Ret = tree[node];
            else Ret.twoChieldCopy( Ret , tree[node] );
            return ;
        }
        int mid = (u+v)>>1, c = (node<<1); int c2 = c+1;
        query( c, u, mid, x,y );
        query( c2, mid+1, v, x,y );
    }
}segTree;
inline void init() { segTree.build( 1, 0 , n-1 ); }
inline LL rngQuery( int u, int v ) {
    segTree.Ret.isBlank = 1;
    segTree.query( 1,0,n-1, u,v );
    return segTree.Ret.ans;
}
inline void singleUpdate( int i, LL x ) { segTree.update( 1, 0,n-1, i, x ); }

int main()
{
    return 0;
}
