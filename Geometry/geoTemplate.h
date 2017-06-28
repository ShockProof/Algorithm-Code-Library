#include <bits/stdc++.h>
#include "../precode.h"
using namespace std;

template<class T>T sqr(T a) { return a*a; }
double scandbl() { double temp; scanf("%lf",&temp); return temp; }

double EPS = 1e-7; /** x<=EPS means x==0 **/
bool isEqual(double a,double b){ return (max(a,b)-min(a,b))<EPS; }
bool inRange(double from, double key, double to) { return from <= key && key <= to; }

struct Point {
        double x, y;
        Point(){}
        Point(double X, double Y){ x=X,y=Y; }
        Point operator + (const Point &p)  const { return Point(x+p.x, y+p.y); }
        Point operator - (const Point &p)  const { return Point(x-p.x, y-p.y); }
        Point operator * (double c)        const { return Point(x*c,   y*c  ); }
        Point operator / (double c)        const { return Point(x/c,   y/c  ); }
        bool operator < (const Point &R ) const {
                return (x==R.x) ? (y<R.y) : (x<R.x);
        }
        double dist(Point &b){ return sqrt( sqr( x - b.x ) + sqr( y - b.y ) ); }
        bool operator ==(const Point &p) const {
                return isEqual(x,p.x) && isEqual(y,p.y);
        }
};
ostream &operator<<(ostream &os, const Point &p) { os << "( " << p.x << " , " << p.y << " )"; }

struct Line {
        double a,b,c;
        Line(){}
        Line(Point A, Point B) {
                a = B.y-A.y;
                b = A.x-B.x;
                c = a*A.x + b*A.y;
        }
        bool isParallel(Line &Ref) {
                double temp = a*Ref.b - Ref.a*b; /** a1*b2-a2*b1 **/
                return isEqual( temp, 0 );
        }
        Point intersects(Line &Ref) {
                double temp = a*Ref.b - Ref.a*b; /** a1*b2-a2*b1 **/
                if( isEqual( temp, 0) ) {
                        /** lines are parallel */
                        return Point(DBL_MIN,DBL_MIN);
                }
                double x = ( c * Ref.b - Ref.c * b ) / temp;
                double y = ( a * Ref.c - Ref.a * c ) / temp;
                return Point(x,y);
        }
};

struct Vector{
        double x, y;
        Vector(){}
        Vector(Point a, Point b) { x = b.x-a.x, y = a.y-b.y; }
        Vector(double X, double Y) { x=X, y=Y; }
        Vector operator + (const Vector &Ref) const {
                return Vector( x + Ref.x , y + Ref.y );
        }
        Vector operator - (const Vector &Ref) const {
                return Vector( x - Ref.x , y - Ref.y );
        }
        bool operator == (const Vector &Ref) const {
                return isEqual( x , Ref.x ) && isEqual( y , Ref.y );
        }
        Point endPoint(Point P) {
                /** when start Point is P returns endPoint **/
                return Point( x+P.x, P.y-y );
        }
        double magnitude() {
                /** length **/
                return sqrt( x*x + y*y );
        }
        double dot(Vector &B) {
                /** ax*by + ay*bx = |a| |b| cos(theta) */
                return  x * B.x + y * B.y;
        }
        double cross(Vector &B) {
                /** ax*by - ay*bx = |a| |b| sin(theta) */
                return x * B.y - y * B.x;
        }
        double angleClockwise( Vector &B ) {
                /** 1 radian = 57.2958 degree = (180.0/pi) degree **/
                double dot = this->x*B.x + this->y*B.y;      /// dot product
                double det = this->x*B.y - this->y*B.x;      /// determinant
                double angle = atan2( det, dot )*(180.0/pi); /// atan2(y, x) or atan2(sin, cos)
                if( angle < 0 ) return 360.00 + angle;
                return angle;
        }
        Vector rotate(double theta) {
                /** rotates clockwise theta degrees....
                for counter clockwise rotation just use theta = (360-theta);
                */
                Vector Ret;
                double ct = cos(theta*(pi/180));
                double st = sin(theta*(pi/180));
                Ret.x = x*ct-y*st;
                Ret.y = x*st+y*ct;
                return Ret;
        }
};
ostream &operator<<(ostream &os, const Vector &p) { os << "( " << p.x << " , " << p.y << " )"; }

bool lineSegmentsIntersected(Point as, Point ae, Point bs, Point be) {
        Line A(as,ae), B(bs,be);
        Point p = A.intersects(B);
        /** now just have to check if the point p is on both of the line segments */
        return inRange( min(as.x, ae.x), p.x, max(as.x, ae.x) )
        && inRange( min(as.y, ae.y), p.y, max(as.y, ae.y) )
        && inRange( min(bs.x, be.x), p.x, max(bs.x, be.x) )
        && inRange( min(bs.y, be.y), p.y ,max(bs.y, be.y) );
}

Line PerpendicularBisector( Line A, Point one, Point two ) {
        Point mid = (one+two)/2;
        Line Ret;
        Ret.a = -A.b;
        Ret.b = A.a;
        Ret.c = Ret.a*mid.x + Ret.b*mid.y;
        return Ret;
}

bool isPerpendicular(Vector a, Vector b) {
        /** angle between a and b is 90-degrees */
        return isEqual( a.dot(b) , 0.00 );
}
bool linesParallel(Point A,Point B, Point C, Point D) {
        Vector AB(A,B), CD(C,D);
        return isEqual( AB.cross(CD) , 0.00 );
}
bool linesCollinear(Point A,Point B, Point C, Point D) {
        Vector AB(A,B), AC(A,C), AD(A,D);
        return isEqual( AB.cross(AC) , 0.00 ) && isEqual( AB.cross(AD) , 0 );
}

double parallelogramArea(Point a, Point b, Point c) {
        Vector A(b,a), B(b,c);
        return A.cross(B);
}
double triangleArea(Point a, Point b, Point c) {
        return parallelogramArea(a,b,c)/2;
}
double triangleAreaFromThreeSides(double A,double B,double C) {
        double s = (A+B+C)/2;
        return sqrt(s*(s-A)*(s-B)*(s-C));
}

double linePointDist(Point a, Point b, Point p, bool isSegment) {
        Vector AB(a,b), BP(b,p), BA(b,a), AP(a,p);
        if( isSegment ) {
                if( BA.dot(AP) > 0.00 ) return a.dist(p);
                if( AB.dot(BP) > 0.00 ) return b.dist(p);
        }
        return fabs(AB.cross(BP)/AB.magnitude());
}

double polygonArea( vector<Point>&v ) {
        /** going to work for any irregular polygon **/
        double area  = 0.00;
        for(int i=v.size()-1; i>=2; i--) {
                area += triangleArea( v[0], v[i], v[i-1] );
        }
        return fabs(area);
}

double regularPolygonAngle( int numberOfSides ) {
        /** in regular polygon number of points = number of sides
        if three points of polygon are x,y,z expand zy to yc and
        this function returns the angle xyc
        */
        return (360.00/numberOfSides);
}

pair<int,int> slopeInteger(int x, int y) {
        if(x==0&&y==0) return pair<int,int>(x,y);
        int gcd = GCD( abs(x),abs(y) );
        x/=gcd;
        y/=gcd;
        if( x<0 && y<0 ) return pair<int,int>( -x,-y );
        if( (x<0 && y>=0) ) return pair<int,int>(x,y);
        if( (x>=0 && y<0) ) return pair<int,int>(-x,-y);
        return pair<int,int>(x,y);
}
