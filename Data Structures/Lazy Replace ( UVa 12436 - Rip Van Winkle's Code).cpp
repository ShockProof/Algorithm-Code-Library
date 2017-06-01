#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
int _Int() { int x; scanf("%d",&x); return x; }
int Case;
const int M = 250000+7;
const int TREE = (M<<1) + M;

LL stt[TREE]; /// start
LL inc[TREE]; /// increase
LL tree[TREE];/// summation
bool has_lazy[TREE];
bool replaced[TREE];

LL lazy_easy( int u , int v , LL s , LL i ) {
        int c = v-u+1;
        /**  returns sum of array(A) of c elements
        where A[0]=s and A[i]=A[i-1]+inc (i>0) */
        LL cs = c;
        cs = ( cs * (cs-1) ) >> 1LL;
        return ( s * c ) + ( cs * i );
}

LL lazy_term( int n , LL s , LL i ) {
        /**  returns A[n] of array(A) elements
        where A[0]=s and A[i]=A[i-1]+inc (i>0) */
        return s + ( n * i );
}

void lazy_pass_down( int node , int c1 , int c2 , int u , int mid , int v )
{
        if( replaced[node] ) {
                replaced[c1] = replaced[c2] = 1;

                stt[c1] = stt[node];
                inc[c1] = inc[node];
                tree[c1] = lazy_easy( u , mid , stt[c1] , inc[c1] );
                LL stt_term = lazy_term( mid-u+1 , stt[node] , inc[node] );
                stt[c2] = stt_term;
                inc[c2] = inc[node];
                tree[c2] = lazy_easy( mid+1 , v , stt_term , inc[c2] );
        }
        else {
                stt[c1] += stt[node];
                inc[c1] += inc[node];
                tree[c1] += lazy_easy( u,mid , stt[node] , inc[node] );

                LL stt_term = lazy_term( mid-u+1 , stt[node] , inc[node] );
                stt[c2] += stt_term;
                inc[c2] += inc[node];
                tree[c2] += lazy_easy( mid+1,v , stt_term , inc[node] );
        }
        has_lazy[c1] = has_lazy[c2] = 1;
        stt[node] = inc[node] = replaced[node] = has_lazy[node] = 0;
        tree[node] = tree[c1] + tree[c2];
}

void lazy_update( int node , int u , int v , int L , int R , LL add , LL incre )
{
        if( R<u || v<L ) return;
        if( L <= u && v <= R ) {

                has_lazy[node] = 1;

                LL stt_term = lazy_term( u-L , add , incre );
                stt[node] += stt_term;
                inc[node] += incre;
                tree[node] += lazy_easy( u , v , stt_term , incre );

                return;
        }
        int mid = ( u + v ) >> 1 , c1 = (node<<1)+1; int c2 = c1 + 1;

        if( has_lazy[node] ) lazy_pass_down( node , c1 , c2 , u , mid , v );

        lazy_update( c1 , u , mid , L , R , add , incre );
        lazy_update( c2 , mid+1,v , L , R , add , incre );

        tree[node] = tree[c1] + tree[c2];
}

void lazy_replace( int node , int u , int v , int L , int R , LL val )
{
        if( R<u || v<L ) return;
        if( L <= u && v <= R ) {

                has_lazy[node] = 1;
                replaced[node] = 1;

                stt[node] = val;
                inc[node] = 0;
                tree[node] = lazy_easy( u,v , val , 0 );

                return;
        }
        int mid = ( u + v ) >> 1 , c1 = (node<<1)+1; int c2 = c1 + 1;

        if( has_lazy[node] ) lazy_pass_down( node , c1 , c2 , u , mid , v );

        lazy_replace( c1 , u , mid , L , R , val );
        lazy_replace( c2 , mid+1,v , L , R , val );

        tree[node] = tree[c1] + tree[c2];
}

void query( int node , int u , int v , int L , int R , LL &sum )
{
        if( R<u || v<L ) return;
        if( L <= u && v <= R ) {
                sum += tree[node];
                return;
        }
        int mid = ( u + v ) >> 1 , c1 = (node<<1)+1; int c2 = c1 + 1;

        if( has_lazy[node] ) lazy_pass_down( node , c1 , c2 , u , mid , v );

        query( c1 , u , mid , L , R , sum );
        query( c2 , mid+1,v , L , R , sum );
}

int query_count , u , v;
char query_type[3];

void Main()
{
        query_count = _Int();

        while( query_count-- ) {

                scanf("%s",query_type ); u = _Int(); v = _Int();

                if( query_type[0] == 'A' ) {
                        lazy_update( 0,0,M-1, u,v, 1,1 );
                }
                else if( query_type[0] == 'B' ) {
                        lazy_update( 0,0,M-1, u,v, v-u+1,-1 );
                }
                else if( query_type[0] == 'C' ) {
                        lazy_replace( 0,0,M-1, u,v, _Int() );
                }
                else if( query_type[0] == 'S' ) {
                        LL sum = 0;
                        query(0,0,M-1, u,v , sum );
                        printf( "%lld" , sum );
                        putchar_unlocked(10);
                }
        }
}

int main()
{
        Main();
        return 0;
}
