#include <bits/stdc++.h>

#include "geoTemplate.h"

int Case = 0;

bool isPointOnLineSegment(Point A, Point x, Point y)
{
    double d1 = A.dist(x) + A.dist(y);
    return isEqual( x.dist(y), d1 );
}

const int M = 20000+9;
/// shooting a ray technique
bool PointIsInsidePolygonAreaCustom(Point V[], Point P, int sz) {
        Point Q(INT_MAX-1000,INT_MAX-100); /// ei point 2 tar GCD 1 hole valo hoy
        int ans=lineSegmentsIntersected( V[0],V[sz-1] , P,Q );
        if( isPointOnLineSegment(P,V[0],V[sz-1] ) ) return 1;
        for(int i=sz-1; i>0; i--) {
                if( isPointOnLineSegment(P,V[i],V[i-1] ) ) return 1;
                if( lineSegmentsIntersected( V[i],V[i-1] , P,Q ) ) {
                        Line one(V[i],V[i-1]), two(P,Q);
                        Point thatPoint = one.intersects(two);
                        ans += ( !(thatPoint==V[i]) && !(thatPoint==V[i-1]) );
                }
        }
        return (ans&1);
}

Point a[1000000];
void Main()
{
        int n = _Int();
        for(int i=0; i<n; i++) {
                a[i].x = scandbl();
                a[i].y = scandbl();
        }
        int qry=_Int();
        printf("Case %d:\n",Case);
        while(qry--)
        {
                Point p;
                p.x = scandbl(); p.y = scandbl();
                printf("%s\n", PointIsInsidePolygonAreaCustom(a, p, n) ? "Yes" : "No" );
        }
}

int main()
{
        int test=_Int();
        while(test--) {
                Case++;
                Main();
        }
        return 0;
}
