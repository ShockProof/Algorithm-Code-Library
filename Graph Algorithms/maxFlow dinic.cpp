#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40000+70;
const int INF = 1000000000;

struct e_maxx_dinic_template{

    struct edge {
        int a, b, cap, flow;
    };

    int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
    edge e[1000000];
    int edge_size;
    vector<int> g[MAXN];

    /**
    1. init()
    2. 'n' should be greater then the number of node
    3. 's' is source 't' is sink
    4. call dinic to get flow
    */

    void init( int src, int sink , int totalNode ) {
        for(int i=0; i<MAXN; i++) g[i].clear();
        memset(q,0,sizeof(q));
        memset(ptr,0,sizeof(ptr));
        s = src , t = sink , n = totalNode + 3;
        edge_size = 0;
    }

    void add_edge (int a, int b, int cap) {
        edge e1 = { a, b, cap, 0 };
        edge e2 = { b, a, 0, 0 };
        g[a].push_back (edge_size);
        e[edge_size++] = e1;
        g[b].push_back (edge_size);
        e[edge_size++] = e2;
    }

    bool bfs() {
        int qh=0, qt=0;
        q[qt++] = s;
        memset (d, -1, n * sizeof d[0]);
        d[s] = 0;
        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            int gvSZ = g[v].size();
            for (size_t i=0; i<gvSZ; ++i) {
                int id = g[v][i],
                    to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow) {
        if (!flow)  return 0;
        if (v == t)  return flow;
        int gvSZ = g[v].size();
        for (; ptr[v]<gvSZ; ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1)  continue;
            int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int dinic() {
        int flow = 0;
        for (;;) {
            if (!bfs())  break;
            memset (ptr, 0, n * sizeof ptr[0]);
            while (int pushed = dfs (s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
}obj;

int main()
{
    int n = 123;
    int src = n+1, des = n+2;

    obj.init( src, des , n+5 );
    /// call addEdge(u,v,weight)
    obj.add_edge( src , 5 , 1 );
    obj.add_edge( 5 , 6 , 1 );
    obj.add_edge( 6 , des , 1 );
    printf("%d\n", obj.dinic() );

    return 0;
}
