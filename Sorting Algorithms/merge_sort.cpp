#include<bits/stdc++.h>
using namespace std;

const int M = 2000000+7;

int merge_sort_temp_array[M];

void merge_sub( int A[] , int n , int u , int mid , int v )
{
        int x = u , y = mid + 1 , i = u;
        while( x <= mid || y <= v ) {
                if( x <= mid && ( y>v || A[x]<=A[y]) )
                        merge_sort_temp_array[i++] = A[x++];
                else    merge_sort_temp_array[i++] = A[y++];
        }
        for( i = u ; i <= v ; i ++ ) {
                A[i] = merge_sort_temp_array[i];
        }
}

void merge_sort( int A[] , int n , int u, int v )
{
        if( u == v ) return;
        int mid = (u+v)/2;
        merge_sort( A,n , u , mid );
        merge_sort( A,n , mid+1,v );
        merge_sub ( A,n , u,mid,v );
}

int n ,i;
int A[M];

int main()
{
//        freopen( "input.txt" , "r"  , stdin );
        while( scanf("%d",&n)==1 && n )
        {
                for( i = 0 ; i < n ; i ++ ) scanf( "%d" , &A[i] );

                merge_sort( A , n , 0 , n-1 );

                for( i = 0 ; i < n ; i ++  ) {
                        if( i ) putchar(' ');
                        printf( "%d" , A[i] );
                }
                putchar(10);
        }
        return 0;
}
