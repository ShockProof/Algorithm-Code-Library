#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned long long int uLL;
char __INPUT[25];
inline int _Int() { scanf("%s",__INPUT); return atoi(__INPUT); }
inline LL _LLi() { scanf("%s",__INPUT); return atoll(__INPUT); }
LL bigMod(LL A,LL P,int M){ LL R=1; for(A%=M; P; P>>=1) { if(P&1) R=(R*A)%M; A=(A*A)%M; } return R; } /** (A^P) % M **/
LL bigMul(LL A,LL B,LL M) { LL R=0; for(A%=M; B; B>>=1) { if(B&1) R=(R+A)%M; A=(A+A)%M; } return R; } /** (A*B) % M **/
uLL _pow(uLL A,int P) { uLL R=1; for(; P; P>>=1) { if(P&1) R=(R*A); A=(A*A); } return R; } /** (A^P) **/
template<class ShockProof>ShockProof GCD(ShockProof x, ShockProof y) { while(x) x^=y^=x^=y%=x; return y; } /** GCD(a,b) **/
template<class ShockProof> ShockProof sqr(ShockProof x) { return (x*x); } /** x*x **/
#define pb  push_back
#define pob pop_back
#define pi  acos(-1)
/*************************************************************************************************************************
**                                            Syed Zafrul Lipu (ShockProof)                                              *
**                                            CSE, University of Asia Pacific                                            *
**************************************************************************************************************************/

const int M = 10001;

int n;
vector<int>G[M];

struct Graph_Artuculation{
    /** learned from geekforgeeks **/
    bool vis[M];
    int parent[M];
    int low[M];
    int dt[M];
    bool ap[M]; /** articulation point **/
    vector<int>bridge[M];
    int time = 0;
    void dfs(int u)
    {
        vis[u]=1;
        dt[u] = low[u] = ++time;
        int children = 0;
        for(int i=G[u].size()-1; i>=0; i--) {
            int v = G[u][i];
            if( !vis[v] ) {
                children++;
                parent[v] = u;
                dfs( v );
                low[u] = min( low[u],low[v] );
                if (parent[u] == -1) ap[u] |= children > 1;
                else ap[u] |= low[v] >= dt[u];
                if( low[v]> dt[u] ) {
                    bridge[u].pb(v);
                    bridge[v].pb(u);
                }
            }
            else if( v!=parent[u] ){
                low[u] = min( low[u],dt[v] );
            }
        }
    }

    void init() {
        memset(vis,0,sizeof(vis));
        memset(ap,0,sizeof(ap));
        memset(parent,-1,sizeof(parent));
        time=0;
    }

    int call()
    {
        init();
        for(int i=0; i<n; i++) {
            if(!vis[i]) dfs(i);
        }
        int cnt=0;
        for(int i=0; i<n; i++) {
            cnt += ap[i];
        }
        return cnt;
    }
}Articulation;

int Case = 0;

void Main()
{
    for(int i=0; i<M; i++ ) G[i].clear();
    n=_Int();
    int m=_Int(),u,v;
    while(m--) {
        u=_Int()-1;
        v=_Int()-1;
        G[u].pb(v);
        G[v].pb(u);
    }
    printf("Case %d: %d\n",Case, Articulation.call() );
}

int main()
{
    int test=_Int();
    while(test--) {
        Case ++;
        Main();
    }
}
