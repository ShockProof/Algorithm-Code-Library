#include<bits/stdc++.h>
using namespace std;
int mod( int x, int n ) { return ( (x%n) + n) % n; }
int Grid[100][100];

int main()
{
        int n, Case = 0;
        while( scanf("%d",&n) == 1 ) {
                memset( Grid, 0, sizeof Grid );
                int x = 0, y = n>>1, p,q;
                int val = 0;
                Grid[x][y] = ++val;
                while( 1 ) {
                        p = mod( x - 1 , n ), q = ( y + 1 ) % n;
                        if( Grid[ p ][ q ] ) p = (x+1)%n, q = y;
                        if( Grid[ p ][ q ] ) break;
                        Grid[ x = p ][ y = q ] = ++val;
                }

                char format[10];
                x = 0, y = 1;
                while( val ) {
                        val/=10;
                        x++;
                }
                x++;
                while( x ) {
                        format[y++] = (x%10)+48;
                        x /= 10;
                }
                format[y] = 'd', format[y+1] = 0, format[0] = '%';
                reverse( format + 1 , format + y );

                int sum  = 0;
                for(int i=0; i<n; i++) sum+=Grid[i][i];
                if( Case++ ) putchar(10);
                printf("n=%d, sum=%d\n", n, sum);
                for(int i=0; i<n; i++) {
                        for(int j=0; j<n; j++) {
                                printf(format, Grid[i][j]);
                        }
                        putchar(10);
                }
        }
        return 0;
}
