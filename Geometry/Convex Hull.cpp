#include <bits/stdc++.h>

#include "geoTemplate.h"

Point BL_CH; /** Bottom-Left for convex Hull */
bool compFuncForCH(Point i, Point j) {
        Vector vi(BL_CH,i);
        Vector vj(BL_CH,j);
        if( isEqual( vi.cross(vj), 0.0000 )  ) {
                return BL_CH.dist(i) < BL_CH.dist(j);
        }
        return vi.cross(vj) < EPS;
}
void convexHull(Point L[], int &n, Point CH[], int &sz) {
        BL_CH = L[0];
        int ix = 0;
        for(int i=1; i<n; i++) {
                if( L[i] < BL_CH ) {
                        BL_CH = L[i];
                        ix = i;
                }
        }
        swap(L[ix],L[0]);
        sort( L+1, L+n, &compFuncForCH );
        sz = 0;
        for(int i=0; i<n; i++) {
                while( sz > 2 ) {
                        Vector v1(CH[ sz-2 ],CH[ sz-1 ]), v2(CH[ sz-1 ],L[i]);
                        if( v1.cross(v2) < EPS ) break;
                        sz--;
                }
                if( !i || (i && !(L[i]==L[i-1])) ) CH[sz++] = L[i];
        }
}

Point P[100000+7];
Point c[100000+7];

int main()
{
        int n = _Int();
        for(int i=0; i<n; i++) {
                P[i].x = _Int();
                P[i].y = _Int();
        }
        int x = 0;
        convexHull(P,n,c,x);
        cout<<"Convex hull Points"<<endl;
        for(int i=0; i<(x); i++) {
                cout<<c[i]<<endl;
        }
        return 0;
}
