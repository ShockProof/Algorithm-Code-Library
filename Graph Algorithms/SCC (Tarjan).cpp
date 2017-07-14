#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int M = 1000 + 7;

vector<int> dag[M];

struct SCC_Tarjan {

        int n;

        vector<int>graph[M];

        int stk[M];
        int stk_sz;
        bool in_stack[M];

        int mycomp[M];
        int components;

        int disc[M]; /** discovery time */
        int low[M];

        int moment;

        void dfs( int u )
        {
                low[u] = disc[u] = moment++;
                stk[ stk_sz++ ] = u;
                in_stack[u] = 1;
                for( int i = graph[u].size() - 1 ; i >= 0 ; i -- ) {
                        int &v = graph[u][i];
                        if( !disc[v] ) {
                                dfs( v );
                                low[u] = min( low[u] , low[v] );
                        }
                        else if ( in_stack[v] ) {
                                low[u] = min( low[u] , disc[v] );
                        }
                }
                if( disc[u] == low[u] ) {
                        mycomp[u] = components++;
                        while( disc[ stk[ stk_sz-1 ] ] != low[ stk[ stk_sz-1 ] ] ) {
                                mycomp[ stk[ stk_sz-1 ] ] = mycomp[u];
                                in_stack[ stk[ stk_sz-1 ] ] = 0;
                                stk_sz--;
                        }
                        in_stack[ stk[ stk_sz-1 ] ] = 0;
                        stk_sz--;
                }
        }

        void call()
        {
                stk_sz = components = 0;
                moment = 1;
                memset( disc , 0 , sizeof disc );
                memset( in_stack , 0 , sizeof in_stack );
                for( int i = 0 ; i < n ; i ++ ) {
                        if( !disc[i] ) dfs(i);
                }

                /** now make the dag */
                for( int i = 0 ; i < n; i ++ ) {
                        int &x = mycomp[i];
                        for( int j = graph[i].size() - 1 ; j >= 0 ; j -- ) {
                                int &y = mycomp[ graph[i][j] ];
                                if( x == y ) continue;
                                dag[x].pb(y);
                        }
                }
        }

        void add_edge( int u , int v ) {
                graph[u].pb(v);
        }
        void init( int numberOfNodes ) {
                n = numberOfNodes;
                for( int i = 0 ; i < M ; i ++ ) graph[i].clear();
        }
}tarjan;

int main()
{
        return 0;
}
