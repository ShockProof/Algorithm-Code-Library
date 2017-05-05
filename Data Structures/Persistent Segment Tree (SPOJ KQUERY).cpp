#include <bits/stdc++.h>
using namespace std;
template<class T> inline bool inRng( T u, T v, T x ) { return u<=x && x<=v; }
 
inline unsigned int _Int() {
        char c=getchar_unlocked();
        while(c<'0'||c>'9')c=getchar_unlocked();
        unsigned x=(c-'0');
        while((c=getchar_unlocked())>='0'&&c<='9')x=((x<<3)+(x<<1))+c-'0';
        return x;
}
 
const int M = 30000 + 7;
 
 
        struct Persistent_Segment_Tree_node{
                int sum;
                int cleft , cright;
                void leaf( int ini_sum ) {
                        cleft = -1 , cright = -1;
                        sum = ini_sum;
                }
        };
 
        Persistent_Segment_Tree_node dag[M*30];
 
        int _size;
        int nodeCount;
        int updateCount;
        int updateRoot[M];
 
 
        void build( int n , int u , int v ) {
                if( u == v ) {
                        dag[ n ].leaf( 0 );
                        return;
                }
                int mid = (u+v)>>1 ;
                dag[n].cleft = nodeCount++;
                dag[n].cright = nodeCount++;
                build( dag[n].cleft  , u , mid );
                build( dag[n].cright , mid+1,v );
                dag[n].sum = dag[dag[n].cleft].sum + dag[dag[n].cright].sum;
        }
 
        void Persistent_Segment_Tree_init( int __size ) {
                updateCount = 1; /// index of update starts from 1
                memset( dag , -1 , sizeof(dag) );
                nodeCount = 0;
                updateRoot[0] = nodeCount++;
                _size = __size;
                build( 0 , 0 , _size-1 );
        }
 
        void update( int n , int m , int u , int v , int x , int y ) {
                if( u==v ) {
                        dag[n].sum = y;
                        return;
                }
                int mid = (u+v)>>1;
                if( inRng( u , mid , x ) ) {
                        dag[n].cright = dag[m].cright;
                        dag[n].cleft = nodeCount ++;
                        update( dag[n].cleft , dag[m].cleft , u , mid , x , y );
                }
                else {
                        dag[n].cleft = dag[m].cleft;
                        dag[n].cright = nodeCount ++;
                        update( dag[n].cright , dag[m].cright , mid+1,v , x , y );
                }
                dag[n].sum = dag[ dag[n].cleft ].sum + dag[ dag[n].cright ].sum;
        }
 
        int qry( int n , int u , int v , int l , int r ) {
                if( v<l || r<u ) return 0;
                if( l<=u&&v<=r ) return dag[n].sum;
                int mid = (u+v)>>1;
                return qry( dag[n].cleft , u,mid , l,r ) + qry( dag[n].cright , mid+1,v , l,r );
        }
 
        void insert( int index , int x ) {
                updateRoot[updateCount++] = nodeCount++;
                int root = nodeCount-1 , prevRoot = updateRoot[updateCount-2];
                update( root , prevRoot , 0 , _size-1 , index , x );
        }
 
 
struct data{
        int i , x;
        bool operator < ( const data &R ) const {
                return x < R.x;
        }
}A[M];
int Arr[M];
 
int n,q;
 
void Main()
{
        n = _Int();
        for( int i = 0 ; i < n ; i ++ ) {
                A[i].x = _Int();
                A[i].i = i;
        }
 
        Persistent_Segment_Tree_init(n);
        sort( A , A+n );
        for( int i = 0 ; i < n ; i ++ ) {
                insert( A[i].i , 1 );
                Arr[i] = A[i].x;
        }
 
        q = _Int();
        for( int i = 0 ; i < q ; i ++  ){
                int u = _Int() - 1;
                int v = _Int() - 1;
                int x = _Int();
                int p = upper_bound( Arr , Arr + n , x ) - Arr;
                printf("%d" , v-u+1 - qry( updateRoot[p] , 0 , _size-1 , u , v ) );
                putchar_unlocked(10);
        }
}
 
int main()
{
//        freopen( "input.txt" , "r" , stdin );
        Main();
        return 0;
} 
