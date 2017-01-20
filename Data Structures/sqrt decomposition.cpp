#include<bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
template<class T>bool inRng(T u, T v, T x) { return u <= x && x <= v; } /** check ( u <= x <= v )  */

const int M = 100000+3;
int n;
int A[100000+3];

const int Bound = 320; /** sqrt( M ) */

int sqrtN, data_sz;
struct Interval{
        int u,v, len, ans;
        void init() {
                len = 0, ans = INT_MAX;
        }
        void insert(int i) {
                if( !len )
                        u = v = i;
                else v++;
                len++;
                ans = min( ans, A[i] );
        }
}data[Bound];

void build()
{
        sqrtN = sqrt(n); data_sz = 0;
        for(int i=0; i<n; i++)  {
        if( !data_sz || ( data[data_sz-1].len == sqrtN ) ) data[ data_sz++ ].init();
                data[data_sz-1].insert(i);
        }
}
int query(int u,int v)
{
        int R = INT_MAX;
        for(int i=0; i<data_sz; i++) {
                if( u <= data[i].u && data[i].v <= v ) R = min(R,data[i].ans);
                else if( data[i].u <= u && v <= data[i].v ) {
                        for(int x=u; x<=v; x++) R = min (R,A[x]);
                }
                else if( inRng( data[i].u,data[i].v, u ) ) {
                        for(int x=u; x<=data[i].v; x++) R = min (R,A[x]);
                }
                else if( inRng( data[i].u,data[i].v, v) ) {
                        for(int x=data[i].u; x<=v; x++) R = min (R,A[x]);
                }
        }
        return R;
}


int main()
{
        return 0;
}
