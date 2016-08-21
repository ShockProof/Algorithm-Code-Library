#include<bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
#define pb push_back
/** 2-SAT tutorial http://codeforces.com/blog/entry/16205 */
const int M = 16000 + 7;

int n;
vector<int>G[M], iG[M];
vector<int>t_DAG[M];
bool vis[M];
int myCom[M], scc;
vector<int>underSCC[M];
int stk[M], stk_sz;
void dfs_1(int u) {
    if( vis[u] ) return;
    vis[u] = 1;
    for(int i=G[u].size()-1; i>=0; i--) dfs_1(G[u][i]);
    stk[stk_sz++] = u;
}
void dfs_2(int u)
{
    if( vis[u] ) return;
    vis[u] = 1;
    myCom[u] = scc;
    underSCC[scc].pb(u);
    for(int i=iG[u].size()-1; i>=0; i--) dfs_2(iG[u][i]);
}
void kosaraju()
{
    memset(myCom,0,sizeof(myCom));
    memset(vis,0,sizeof(vis));
    stk_sz = 0;
    for(int i=1; i<=n; i++) if( !vis[i] ) dfs_1(i);
    memset(vis,0,sizeof(vis));
    scc=0;
    while( stk_sz ) {
        int i = stk[--stk_sz];
        if( !myCom[i] ) {
            myCom[i] = ++scc;
            dfs_2(i);
        }
    }
    for(int u=0; u<n; u++) {
        for(int i=G[u].size()-1; i>=0; i--) {
            int v = G[u][i];
            if( myCom[u]==myCom[v] ) continue;
            t_DAG[myCom[v]].pb(myCom[u]);
        }
    }
}
void addEdge(int u, int v) {
    G[u].pb(v);
    iG[v].pb(u);
}


int order[M], order_sz;
void topSort(int u)
{
    if(vis[u]) return;
    vis[u] = 1;
    for(int i= t_DAG[u].size()-1; i>=0; i--)
        topSort(t_DAG[u][i]);
    for(int i=underSCC[u].size()-1; i>=0; i--) {
        order[order_sz++] = underSCC[u][i];
    }
}

int Case = 0;

void Main()
{
    for(int i=0; i<M; i++) {
        G[i].clear();
        iG[i].clear();
        t_DAG[i].clear();
        underSCC[i].clear();
    }
    int voters = _Int();
    int node = _Int();
    n = node<<1;
    while(voters--) {
        int u=_Int(), v=_Int();
        int not_u, not_v;
        if( u>0 ) not_u = node + u;
        else {
            not_u = -u;
            u = node + (not_u);
        }
        if( v>0 ) not_v = node + v;
        else {
            not_v = -v;
            v = node + (not_v);
        }
        u--,v--,not_u--,not_v--;
        addEdge(not_u,v);
        addEdge(not_v,u);
    }

    kosaraju();
    for(int i=0; i<node; i++) {
        if( myCom[i] == myCom[node+i] ) {
            printf("Case %d: No\n",Case);
            return;
        }
    }

    printf("Case %d: Yes\n",Case);
    order_sz = 0;
    memset(vis,0,sizeof(vis));
    for(int i=1; i<=scc; i++) if(!vis[i]) topSort(i);
    memset(vis,0,sizeof(vis));
    set<int> Ans;
    for(int i=order_sz-1; i>=0; i--) {
        int x = order[i];
        if( x<node && !vis[x+node] ) Ans.insert(x+1);
        vis[x] = 1;
    }
    printf("%d",Ans.size());
    for(set<int>::iterator i=Ans.begin(); i!=Ans.end(); i++) printf(" %d",*i);
    putchar(10);
}

int main()
{
    int test = _Int();
    while(test--) {
        Case++;
        Main();
    }
    return 0;
}
