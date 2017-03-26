#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int uLL;
const int M = 3000000 + 7;

uLL phi[M];
uLL sum[M];

void precal_phi()
{
        for( int i = 1 ; i < M ; i ++ ) phi[i] = i;
        for( int i = 2 ; i < M ; i ++ ) {
                if( phi[i] != i ) continue;
                for( int j = i ; j < M ; j += i ) {
                        phi[j] = ( phi[j] * ( i - 1 ) ) / i;
                }
        }
}

void precal_LCM_SUM()
{
        for( int i = 1 ; i < M ; i ++ ) {
                for(int j = i ; j < M ; j += i ) {
                        sum[ j ] += phi[ i ] * i;
                }
        }
        for( int i = 1 ; i < M ; i ++ ) {
                sum[i] = sum[i] + 1;
                sum[i] = sum[i] >> 1ULL;
                sum[i] = sum[i] * i;
        }
}

int main()
{
        precal_phi();
        precal_LCM_SUM();
        /// sum[ n ] = LCM( 1 , n ) + LCM( 2 , n ) + LCM( 3 , n ) + ... ... ... + LCM( n , n );
        return 0;
}
