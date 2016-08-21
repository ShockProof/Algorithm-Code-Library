#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
const double EPS = 1e-9;
double sqr(double v) {return v*v;}
bool isEqual(double x, double y) { return abs(x-y)<EPS; }
struct Point3D {
    double x, y, z;
    Point3D(){}
    Point3D(double X, double Y, double Z){ x=X,y=Y,z=Z; }
    Point3D operator + (const Point3D &p)  const { return Point3D(x+p.x, y+p.y, z+p.z); }
    Point3D operator - (const Point3D &p)  const { return Point3D(x-p.x, y-p.y, z-p.z); }
    Point3D operator * (double c)        const { return Point3D(x*c,   y*c,   z*c  ); }
    Point3D operator / (double c)        const { return Point3D(x/c,   y/c,   z/c  ); }
    double dist(Point3D &b){ return sqrt( sqr( x - b.x ) + sqr( y - b.y ) + sqr( z - b.z ) ); }
    bool operator ==(const Point3D &p) const {
        return isEqual(x,p.x) && isEqual(y,p.y) && isEqual(z,p.z);
    }
};
/** Problem Link: http://acm.hust.edu.cn/vjudge/problem/26950 */
int Case = 0;

void Main()
{
    Point3D A,B,P;
    scanf("%lf %lf %lf",&A.x, &A.y, &A.z);
    scanf("%lf %lf %lf",&B.x, &B.y, &B.z);
    scanf("%lf %lf %lf",&P.x, &P.y, &P.z);
    Point3D high=A, low=B;
    Point3D mid1, mid2;
    for(int ite=0; ite<70; ite++)
    {
        mid1 = (high*2.00+low)/3;
        mid2 = (high+low*2.00)/3;
        if( mid1.dist(P) < mid2.dist(P) ) low = mid2;
        else high = mid1;
    }
    printf("Case %d: %0.9lf\n",Case, P.dist(mid1) );
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
