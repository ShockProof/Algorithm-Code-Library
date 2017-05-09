#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
inline int _Int() { int x; scanf("%d",&x); return x; }
int Case;

const int M = 100000 + 7;

LL tree[ M<<2 ];

bool has_lazy[ M<<2 ];
LL lazy[ M<<2 ];

inline void lazy_pass_down( int node , int c1 , int c2 , int u , int mid , int v )
{
        lazy[c1] += lazy[node];
        lazy[c2] += lazy[node];
        has_lazy[c1] = has_lazy[c2] = 1;
        tree[c1] += lazy[node] * (mid-u+1);
        tree[c2] += lazy[node] * (v-mid);

        lazy[node] = has_lazy[node] = 0;
        tree[node] = tree[c1] + tree[c2];
}

void lazy_update( int node , int u , int v , int F , int T , int add )
{
        if( T < u || v < F ) return;
        if( F<=u && v<=T ) {
                has_lazy[node] = 1;
                lazy[node] += add;
                tree[node] += (LL)add * (v-u+1);
                return;
        }
        int mid = (u+v)>>1 , c1 = node<<1; int c2 = c1+1;

        if( has_lazy[node] )
                lazy_pass_down( node , c1,c2 , u,mid,v );

        lazy_update( c1 , u , mid , F,T , add );
        lazy_update( c2 , mid+1,v , F,T , add );

        tree[node] = tree[c1] + tree[c2];
}

LL lazy_query( int node , int u , int v , int F , int T )
{
        if( T < u || v < F ) return 0;
        if( F<=u && v<=T ) return tree[node];
        int mid = (u+v)>>1 , c1 = node<<1; int c2 = c1+1;

        if( has_lazy[node] )
                lazy_pass_down( node , c1,c2 , u,mid,v );
        return lazy_query( c1 , u,mid , F,T )+lazy_query( c2 , mid+1,v, F,T );
}

void lazy_init()
{
        memset( tree, 0 , sizeof tree );
        memset( has_lazy , 0 , sizeof has_lazy );
        memset( lazy , 0 , sizeof lazy );
}

int n;
LL rng_sum( int x , int y ) {
        return lazy_query( 1,0,n , x,y );
}
void rng_update( int x , int y , LL add ) {
        return lazy_update( 1,0,n, x,y,add );
}

void Main()
{
        lazy_init();
        n = _Int();
        int q = _Int() , qtt , u ,v , add ;
        printf("Case %d:\n",Case);
        while( q -- ) {
                qtt = _Int();
                u = _Int();
                v = _Int();
                if( !qtt ) {
                        rng_update( u,v, _Int() );
                }
                else {
                        printf("%lld\n", rng_sum( u,v ) );
                }
        }
}

int main()
{
        int test = _Int();
        for( Case = 1 ; Case <= test ; Case ++ )
                Main();
        return 0;
}
