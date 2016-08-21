#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
#define pb push_back

const int inf = 1234567891;
int Case;
const int M = 1000 + 3; /// MAX NODE

int n;
vector<int> G[M];
int dist[M];
int updated[M];
void bellman_ford(int u)
{
    queue<int> q;
    dist[u] = 0;
    q.push(u);
    while( q.size() ) {
        int u = q.front();
        q.pop();
        for(int i=G[u].size()-2; i>=0; i-=2) {
            int v = G[u][i], w = G[u][i+1];
            if( dist[v] > (dist[u]+w) && updated[u] <= n  ) {
                dist[v] = dist[u]+w;
                q.push(v);
                updated[v]++;
                if( updated[v] == n ) {
                    /** negative cycle found; dist[v] is -inf; */
                }
            }
        }
    }
}

void Main()
{
    for(int i=0; i<M; i++) {
        updated[i] = 0, dist[i] = inf, G[i].clear();
    }
}
int main()
{
    return 0;
}
