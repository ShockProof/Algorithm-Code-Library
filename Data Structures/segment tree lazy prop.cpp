#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long int LL;
const int M = 200000+7;
/**
Segment tree lazy propagation
index 1...n
*/
int n;
struct data {
        LL sum, prop;
} tree[M<<2] ;
void init() {
        for(int i=0; i<(M<<2); i++) {
                tree[i].sum=0;
                tree[i].prop=0;
        }
}
void update(int node, int l, int r, int f, int t, LL add)
{
        if( l>=f && r<=t ) {
                tree[node].prop += add;
                tree[node].sum += (r-l+1)*add;
                return;
        }
        int mid = (l+r)>>1, c1 = node<<1, c2 = (node<<1) + 1;
        if( mid>=f ) update( c1,  l,  mid, f, t, add );
        if(mid+1<=t) update( c2, mid+1, r, f, t, add );
        tree[node].sum = tree[c1].sum + tree[c2].sum;
        tree[node].sum+= (r-l+1)*tree[node].prop;
}
LL query(int node, int l, int r, int f, int t, LL carry)
{
        if( l>=f && r<=t ) return tree[node].sum + ( carry*(r-l+1) );
        int mid = (l+r)>>1, c1 = node<<1, c2 = (node<<1)+1;
        LL ret=0;
        if(mid>=f)   ret = query( c1,  l,  mid, f, t, (carry+tree[node].prop) );
        if(mid+1<=t) ret+= query( c2, mid+1, r, f, t, (carry+tree[node].prop) );
        return ret;
}
LL rngSum(int u, int v) { return query(1,1,n, u,v, 0 ); }
void rngUpdate(int u, int v, LL add) { update( 1,1,n, u,v, add); }




int main()
{
    return 0;
}
