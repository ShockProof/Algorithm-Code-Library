#include<stdio.h>
#define M 5000001
unsigned long long int phi[M];
void precal()
{
        int i,j;
        phi[1] = 1;
        for( i = 2; i < M; i ++ ) {
                if( phi[i] != 0 ) continue;
                phi[i] = i-1;
                for( j = i + i ; j < M; j += i ) {
                        if( phi[j] == 0 ) phi[j] = j;
                        phi[j] = ( phi[j] * (i-1) ) / i;
                }
        }
}
int main()
{
        precal();
        return 0;
}
