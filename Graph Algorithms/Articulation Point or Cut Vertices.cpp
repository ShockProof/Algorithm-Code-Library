#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
#define myMemset(a,b) memset(a,b,sizeof(a))
#define pb   push_back
/*************************************************************************************************************************
**                                            Syed Zafrul Lipu (ShockProof)                                              *
**                                            CSE, University of Asia Pacific                                            *
**************************************************************************************************************************/
const int M = 10001;

int n;
vector<int>G[M];

struct Graph_Artuculation{
    bool vis[M];
    int parent[M];
    int low[M];
    int dt[M];
    bool ap[M]; /** articulation point **/
    vector<int>bridge[M];
    set<int> bridgeAdj[M];
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
                    bridgeAdj[u].insert(v);
                    bridgeAdj[v].insert(u);
                }
            }
            else if( v!=parent[u] ){
                low[u] = min( low[u],dt[v] );
            }
        }
    }

    void init() {
        myMemset(vis,0);
        myMemset(ap,0);
        myMemset(parent,-1);
        for(int i=0; i<M; i++) {
            bridge[i].clear();
            bridgeAdj[i].clear();
        }
        time=0;
    }

    int call()
    {
        init();
        for(int i=0; i<n; i++) if(!vis[i]) dfs(i);
        int x=0;
        for(int i=0; i<n; i++) x += ap[i];
        return x;
    }

    /** block cut tree */
    int BCT_n;
    int BCT_parent[M];
    void BCT_build(int u) {
        if( vis[u] ) return;
        vis[u] = 1;
        BCT_parent[u] = BCT_n;
        for(int i=G[u].size()-1; i>=0; i--) {
            int v = G[u][i];
            if( bridgeAdj[u].find(v)!=bridgeAdj[u].end() ) continue;
            BCT_build( v );
        }
    }
    vector<int>BCT[M];
    void block_cut_tree() {
        for(int i=0; i<M; i++) BCT[i].clear();
        BCT_n = 0;
        myMemset(vis,0);
        for(int i=0; i<n; i++) {
            if( !vis[i] ) {
                BCT_build(i);
                BCT_n ++;
            }
        }
        for(int u=0; u<n; u++){
            for(set<int>:: iterator v = bridgeAdj[u].begin(); v!=bridgeAdj[u].end(); v++)
                BCT[ BCT_parent[u] ].pb( BCT_parent[*v] );
        }
    }
}Articulation;


int main()
{
    return 0;
}
