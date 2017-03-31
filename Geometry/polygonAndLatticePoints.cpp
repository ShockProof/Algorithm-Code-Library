#include <bits/stdc++.h>
#include "precode.h"
using namespace std;

/**
        Problem:
        Given the points of a polygon
        how points lying strictly inside the polygon

        Solution:
        B = number of lattice points on the boundary of the polygon
        I = number of lattice points in the interior of the polygon

        From pick's theorem we know that:

        Area = B/2 + I - 1

        so, I = Area - (B/2) + 1
*/

struct Point {
        int x, y;
        Point(){}
};
struct Vector{
        LL x, y;
        Vector(){}
        Vector(Point a, Point b) { x = b.x-a.x, y = a.y-b.y; }
        LL cross(Vector &B) {
                return x * B.y - y * B.x;
        }
};
LL parallelogramArea(Point a, Point b, Point c) {
        Vector A(b,a), B(b,c);
        return A.cross(B);
}

int Case;

Point P[100000+7];

int latticePoints(Point a, Point b)
{
        b.x -= a.x;
        b.y -= a.y;
        if( b.x < 0 ) b.x = -b.x;
        if( b.y < 0 ) b.y = -b.y;
        return __gcd(b.x,b.y);
}

void Main()
{
        int n=_Int();
        LL twoA = 0; /** twice of polygon area */
        LL B = n;
        scanf("%d %d",&P[0].x,&P[0].y);
        for(int i=1; i<n; i++) {
                scanf("%d %d",&P[i].x,&P[i].y);
                twoA += parallelogramArea( P[0],P[i-1],P[i] );
                B += latticePoints( P[i-1], P[i] ) - 1;
        }
        B += latticePoints( P[n-1], P[0] ) - 1;
        if( twoA < 0 ) twoA = -twoA;
        printf("Case %d: %lld\n", Case, ( twoA - B + 2 ) >> 1 );
}

int main()
{
        int test=_Int();
        for( Case = 1 ; Case <= test ; Case ++ ) Main();
        return 0;
}
