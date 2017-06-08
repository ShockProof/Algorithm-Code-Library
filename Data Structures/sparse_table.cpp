#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }

const int M = 5000 + 7;

int precal_log[M];

struct sparse_table {
        int minimum;
        int maximum;
        void single( int x ) {
                minimum = x;
                maximum = x;
        }
}s_table[M][25];

int build_s_table( int A[] , int &n )
{
        for( int i = 0 ; i < n ; i ++ )
                s_table[i][0].single( A[i] );

        for( int j = 1 ; (1<<j) <= n ; j ++ ) {
                for( int i = 0 ; i < n ; i ++ ) {
                        int b = i+(1<<(j-1));
                        if( b > n ) continue;
                        s_table[i][j].minimum = min( s_table[ i ][ j-1 ].minimum , s_table[ b ][ j-1 ].minimum );
                        s_table[i][j].maximum = max( s_table[ i ][ j-1 ].maximum , s_table[ b ][ j-1 ].maximum );
                }
        }
}

int query_min( int a , int b )
{
        int p = precal_log[b-a+1];
        return min( s_table[a][p].minimum , s_table[ b-(1<<p)+1 ][ p ].minimum );
}
int query_max( int a , int b )
{
        int p = precal_log[b-a+1];
        return max( s_table[a][p].maximum , s_table[ b-(1<<p)+1 ][ p ].maximum );
}

void Main()
{
}

int main()
{
        /// precal log --------------------->
        int one = 1 , two = 2 , id = 0;
        for( int i = 1 ; i < M ; i ++  ) {
                if( i==two ) {
                        one = one<<1;
                        two = two<<1;
                        id++;
                }
                precal_log[i] = id;
        }
        /// <--------------------- precal log

        Main();
        return 0;
}
