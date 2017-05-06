#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
inline int _Int() { int x; scanf("%d",&x); return x; }
/*************************************************************************************************************************
**                                            Syed Zafrul Lipu (ShockProof)                                              *
**                                            CSE, University of Asia Pacific                                            *
**************************************************************************************************************************/

int Case;
const int M = 250000 + 7;

struct lazy_properties {
        LL stt , inc; /// start and increase
        bool replaced;
        LL val;
        LL sum;
        void chieldren( LL csm ) {
                stt = inc = replaced = val = 0;
                sum = csm;
        }
        void set( LL a , LL b , bool c , LL d ) {
                stt = a;
                inc = b;
                replaced = c;
                val = d;
        }
} tree[ M*3 ] ;


LL lazy_easy( int c , LL s , LL i ) {
        /**  returns sum of array(A) of c elements where A[0]=s and A[i]=A[i-1]+inc (i>0) */
        LL cs = c;
        cs = ( cs * (cs-1) ) >> 1LL;
        return ( s * c ) + ( cs * i );
}

LL lazy_easy_term( int n , LL s , LL i ) {
        /**  returns A[n] of array(A) elements where A[0]=s and A[i]=A[i-1]+inc (i>0) */
        return s + ( n * i );
}

void lazy_update( int node, int u , int v , int L , int R , LL stt , LL inc , LL carry_stt , LL carry_inc , bool carry_replace , LL replace_val )
{
        if( R<u || v<L ) {
                LL c = v-u+1;
                if( carry_replace || tree[node].replaced ) {
                        if( !carry_replace ) {
                                replace_val = tree[node].val;
                                carry_stt += tree[node].stt , carry_inc += tree[node].inc;
                        }
                        tree[node].set(  carry_stt , carry_inc , 1 , replace_val );
                        tree[node].sum = lazy_easy( c , tree[node].stt+replace_val , tree[node].inc );
                }
                else {
                        tree[node].set( tree[node].stt + carry_stt , tree[node].inc + carry_inc , 0 , 0 );
                        tree[node].sum += lazy_easy( c , carry_stt , carry_inc );
                }
                return;
        }
        if( L<=u && v<=R ) {
                LL c = v-u+1;
                stt = lazy_easy_term( u-L , stt , inc );
                if( carry_replace || tree[node].replaced ) {
                        if( !carry_replace ) {
                                replace_val = tree[node].val;
                                carry_stt += tree[node].stt , carry_inc += tree[node].inc;
                        }
                        tree[node].sum = lazy_easy( c , carry_stt + stt + replace_val, carry_inc + inc );
                        tree[node].set( stt+carry_stt , inc+carry_inc , 1 , replace_val );
                        return;
                }
                tree[node].sum += lazy_easy( c , carry_stt + stt , carry_inc + inc );
                tree[node].set( tree[node].stt +carry_stt+stt , tree[node].inc +carry_inc+inc , 0,0 );
                return;
        }

        int mid = (u+v)>>1 , c1 = (node<<1)+1; int c2 = c1+1;

        if( !carry_replace ) {
                carry_stt += tree[node].stt;
                carry_inc += tree[node].inc;
        }
        if( tree[node].replaced && carry_replace==0 ) {
                carry_replace = 1;
                replace_val = tree[node].val;
        }
        lazy_update( c1 , u , mid , L,R,stt,inc, carry_stt , carry_inc , carry_replace , replace_val );
        carry_stt = lazy_easy_term( mid+1-u , carry_stt , carry_inc );
        lazy_update( c2 , mid+1,v , L,R,stt,inc, carry_stt , carry_inc , carry_replace , replace_val );

        tree[node].chieldren( tree[c1].sum + tree[c2].sum );
}

void lazy_replace( int node, int u , int v , int L , int R , LL carry_stt , LL carry_inc , bool carry_replace , LL replace_val , LL replace_now )
{
        if( R<u || v<L ) {
                LL c = v-u+1;
                if( carry_replace || tree[node].replaced ) {
                        if( !carry_replace ) {
                                replace_val = tree[node].val;
                                carry_stt += tree[node].stt;
                                carry_inc += tree[node].inc;
                        }
                        tree[node].set(  carry_stt , carry_inc , 1 , replace_val );
                        tree[node].sum = lazy_easy( c , tree[node].stt + replace_val , tree[node].inc );
                }
                else {
                        tree[node].set( tree[node].stt + carry_stt , tree[node].inc + carry_inc , 0 , 0 );
                        tree[node].sum += lazy_easy( c , carry_stt , carry_inc );
                }
                return;
        }
        if( L<=u && v<=R ) {
                LL c = v-u+1;
                tree[node].sum = replace_now * c;
                tree[node].set( 0,0, 1,replace_now);
                return;
        }

        int mid = (u+v)>>1 , c1 = (node<<1)+1; int c2 = c1+1;

        if( !carry_replace ) {
                carry_stt += tree[node].stt;
                carry_inc += tree[node].inc;
        }
        if( tree[node].replaced && carry_replace==0 ) {
                carry_replace = 1;
                replace_val = tree[node].val;
        }
        lazy_replace( c1 , u , mid , L,R, carry_stt , carry_inc , carry_replace , replace_val , replace_now );
        carry_stt = lazy_easy_term( mid+1-u , carry_stt , carry_inc );
        lazy_replace( c2 , mid+1,v , L,R, carry_stt , carry_inc , carry_replace , replace_val , replace_now );

        tree[node].chieldren( tree[c1].sum + tree[c2].sum );
}

LL lazy_query( int node, int u , int v , int L , int R , LL carry_stt , LL carry_inc , bool carry_replace , LL replace_val )
{
        if( R<u || v<L ) return 0;
        if( L<=u && v<=R ) {
                LL c = v-u+1;
                if( carry_replace || tree[node].replaced ) {
                        if( !carry_replace ) {
                                replace_val = tree[node].val;
                                carry_stt += tree[node].stt;
                                carry_inc += tree[node].inc;
                        }
                        return lazy_easy( c , replace_val + carry_stt , carry_inc );
                }
                return tree[node].sum + lazy_easy( c , carry_stt , carry_inc );
        }

        int mid = (u+v)>>1 , c1 = (node<<1)+1; int c2 = c1+1;

        if( !carry_replace ) {
                carry_stt += tree[node].stt;
                carry_inc += tree[node].inc;
        }
        if( tree[node].replaced && carry_replace==0 ) {
                carry_replace = 1;
                replace_val = tree[node].val;
        }
        LL Ret = lazy_query( c1 , u , mid , L,R, carry_stt , carry_inc , carry_replace, replace_val );
        carry_stt = lazy_easy_term( mid+1-u , carry_stt , carry_inc );
        Ret+= lazy_query( c2 , mid+1,v , L,R, carry_stt , carry_inc , carry_replace, replace_val );
        return Ret;
}

int query_count , u , v;
char query_type[3];

void Main()
{
        query_count = _Int();
//        memset( tree , 0 , sizeof tree );
        while( query_count-- ) {
                scanf("%s %d %d",query_type , &u,&v );
                /***/if( query_type[0] == 'A' ) {
                        lazy_update( 0,0,M-1, u,v, 1,1, 0,0,0,0 );
                }
                else if( query_type[0] == 'B' ) {
                        lazy_update( 0,0,M-1, u,v, v-u+1,-1, 0,0,0,0 );
                }
                else if( query_type[0] == 'C' ) {
                        lazy_replace( 0,0,M-1, u,v, 0,0,0,0, _Int() );
                }
                else if( query_type[0] == 'S' ) {
                        printf( "%lld\n" , lazy_query(0,0,M-1, u,v , 0,0,0,0 ) );
                }
        }
}

int main()
{
        Main();
        return 0;
}
