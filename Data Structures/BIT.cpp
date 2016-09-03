#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
inline int _Int() { int x; scanf("%d",&x); return x; }

const int M = 1000000 + 7;

LL Tree[M];
int sz = M-5;
LL qry(int i) {
    LL R = 0;
    while( i > 0 ) {
        R += Tree[i];
        i -= i & (-i);
    }
    return R;
}
LL query(int i, int j) { return qry(j)-qry(i-1); }
void update(int i, LL v) {
    while( i<=sz ) {
        Tree[i]+=v;
        i += i & (-i);
    }
}
int clearIndex(int i) {
    int v = query(i,i);
    update( i , (-v) );
    return v;
}






int main()
{
    return 0;
}
