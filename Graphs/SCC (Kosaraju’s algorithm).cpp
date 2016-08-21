#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int M = 123456;

int n;
vector<int>G[M], iG[M];
bool vis[M];
int scc[M], cnt;

stack<int> stk;
void dfs_1(int u) {
    if( vis[u] ) return;
    vis[u] = 1;
    for(int i=G[u].size()-1; i>=0; i--) dfs_1(G[u][i]);
    stk.push(u);
}
void dfs_2(int u)
{
    if( vis[u] ) return;
    vis[u] = 1;
    scc[u] = cnt;
    for(int i=iG[u].size()-1; i>=0; i--) dfs_2(iG[u][i]);
}

int main()
{
    int m;
    scanf("%d %d",&n,&m);
    int u,v;
    for(int i=0; i<m; i++) {
        scanf("%d %d",&u,&v);
        G[u].pb(v);
        iG[v].pb(u);
    }

    memset(vis,0,sizeof(vis));
    for(int i=1; i<=n; i++) if( !vis[i] ) dfs_1(i);
    memset(vis,0,sizeof(vis));
    cnt=0;
    while( stk.size() ) {
        int i = stk.top();
        stk.pop();
        if( !scc[i] ) {
            scc[i] = ++cnt;
            dfs_2(i);
        }
    }
    printf("number of components = %d\n",cnt);
    for(int i=1; i<=n; i++)
        printf("%d -> %d\n",i,scc[i]);
    return 0;
}
