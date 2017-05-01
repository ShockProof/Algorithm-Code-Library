#include<bits/stdc++.h>
using namespace std;

const int M = 2000000+7;

struct BinaryHeap_MIN {

        int tree[M];
        int nnn; /// Tree Size

        int parent( int x ) { return (x-1)>>1; }
        int chield_1( int x ){return (x<<1)+1; }
        int chield_2( int x ){return (x<<1)+2; }

        void insert( int x )  {
                int pos = nnn++ , prev;
                tree[pos] = x;
                prev = parent(pos);
                while( pos>0 && tree[pos]<tree[prev] ) {
                        swap( tree[pos] , tree[prev] );
                        pos = prev;
                        prev = parent(pos);
                }
        }

        void remove() {
                tree[0] = tree[--nnn];
                int i = 0 , c1,c2;
                while( 1 ) {
                        c1 = chield_1(i) , c2 = chield_2(i);
                        if     ( c1 < nnn && tree[c1] < tree[i] && ( c2 >= nnn || tree[c1]<=tree[c2] ) ) {
                                swap( tree[i] , tree[c1] );
                                i = c1;
                        }
                        else if( c2 < nnn && tree[c2] < tree[i] && ( c1 >= nnn || tree[c2]<=tree[c1] ) ) {
                                swap( tree[i] , tree[c2] );
                                i = c2;
                        }
                        else {
                                break;
                        }
                }
        }

        int top() {
                return tree[0];
        }

        void init() {
                nnn = 0;
        }
};

BinaryHeap_MIN ds;

int i;

void heap_sort( int A[] , int n )
{
        for( i = 0 ; i < n ; i ++ )  ds.insert( A[i] );
        i = 0;
        while( i < n ) {
                A[i++] = ds.top();
                ds.remove();
        }
}

int n;
int A[M];

int main()
{
//        freopen( "input.txt" , "r"  , stdin );
        ds.init();
        while( scanf("%d",&n)==1 && n )
        {
                for( i = 0 ; i < n ; i ++ ) scanf( "%d" , &A[i] );

                heap_sort( A , n );

                for( i = 0 ; i < n ; i ++  ) {
                        if( i ) putchar(' ');
                        printf( "%d" , A[i] );
                }
                putchar(10);
        }
        return 0;
}
