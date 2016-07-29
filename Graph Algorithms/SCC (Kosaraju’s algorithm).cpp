#include <bits/stdc++.h>
using namespace std;
#define pb  push_back
const int M = 123456;

/** Kosaraju’s algorithm to find Strongly Connected Component **/

int n,m, cnt; /** n = number of nodes ; m = number of edges ; cnt = SCC **/
vector<int> G[M], iG[M]; /** G is the main graph and iG is the inverse graph **/
int vis[M], iVis[M]; /** visited checking for different graphs **/
int scc[M]; /** scc[i] is the number of scc for node i **/

void dfs_1(int u)
{
    if( vis[u]==cnt ) return;
    vis[u]=cnt;
    if(scc[u] && scc[u]!=cnt) return;
    for(int i=G[u].size()-1; i>=0; i--)
            dfs_1(G[u][i]);
}
void dfs_2(int u)
{
    if( iVis[u]==cnt ) return;
    if( vis[u]==cnt ) scc[u]=cnt;
    iVis[u]=cnt;
    if( scc[u] && scc[u]!=cnt ) return;
    for(int i=iG[u].size()-1; i>=0; i--)
            dfs_2(iG[u][i]);
}

int main()
{
    scanf("%d %d",&n,&m);
    int u,v;
    for(int i=0; i<m; i++) {
        scanf("%d %d",&u,&v);
        G[u].pb(v);
        iG[v].pb(u);
    }
    cnt=0;
    for(int i=1; i<=n; i++) {
        if(!scc[i]) {
            scc[i]=++cnt;
            dfs_1(i);
            dfs_2(i);
        }
    }
    printf("number of components = %d\n",cnt);
    for(int i=1; i<=n; i++)
        printf("%d -> %d\n",i,scc[i]);
    return 0;
}
