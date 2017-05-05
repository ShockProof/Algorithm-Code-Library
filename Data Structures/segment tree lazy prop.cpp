#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
inline int _Int() { int x; scanf("%d",&x); return x; }
#define myMemset(a,b) memset(a,b,sizeof(a))

int Case;
const int M = 100000 + 7;

struct lazy_tree_node_data {
        LL sum;
        LL lazy;
}lazy_tree[M<<2];

void lazy_tree_update( int node, int u , int v , int L , int R , LL add , LL carry )
{
        if( v<L || R<u ) {
                lazy_tree[ node ].lazy += carry;
                lazy_tree[ node ].sum += carry*(v-u+1);
                return;
        }
        if( L <= u && v <= R ) {
                lazy_tree[ node ].lazy += add+carry;
                lazy_tree[ node ].sum += (carry+add)*(v-u+1);
                return;
        }
        int mid = (u+v)>>1; int c1 = (node<<1)+1; int c2 = c1+1;
        carry+=lazy_tree[node].lazy;
        lazy_tree_update( c1 , u , mid , L,R,add , carry );
        lazy_tree_update( c2 , mid+1, v, L,R,add , carry );
        lazy_tree[node].sum = lazy_tree[c1].sum + lazy_tree[c2].sum;
        lazy_tree[node].lazy = 0;
}

LL lazy_tree_query( int node, int u , int v , int L , int R , LL lazy_carry )
{
        if( v<L || R<u ) return 0;
        if( L<=u && v<=R ) return lazy_tree[node].sum + lazy_carry*(v-u+1);
        int mid = (u+v)>>1; int c1 = (node<<1)+1; int c2 = c1+1;
        lazy_carry += lazy_tree[node].lazy;
        return  lazy_tree_query( c1 , u , mid , L,R , lazy_carry ) +
                lazy_tree_query( c2 , mid+1,v , L,R , lazy_carry );
}

int n;
LL rng_sum( int x , int y ) {
        return lazy_tree_query( 0,0,n , x,y,0 );
}
void rng_update( int x , int y , LL add ) {
        return lazy_tree_update( 0,0,n, x,y,add,0 );
}

void Main()
{
        n = _Int();
        memset( lazy_tree , 0 , sizeof lazy_tree );

        int q = _Int() , qtype , x , y , v ;
        printf("Case %d:\n", Case );
        while ( q -- ) {
                qtype = _Int();
                x = _Int();
                y = _Int();
                if( qtype == 1 ) printf("%lld\n", rng_sum( x,y ) );
                else {
                        v = _Int();
                        rng_update( x,y,v );
                }
        }
}

int main()
{
        int test = _Int();
        for( Case = 1 ; Case <= test ; Case ++ ) Main();
        return 0;
}
