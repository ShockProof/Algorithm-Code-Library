#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
#define myMemset(a,b) memset(a,b,sizeof(a))

const int M = 1000 + 7 ;

bool notTree;
set<int>::iterator set_;

struct SCC_DAG {
        int n;
        vector< int > G[M], iG[M];
        set<int> dag[M];

        bool vis[M];
        int myCom[M], components;

        int stk[M+M] , stk_sz;
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
                myCom[u] = components;
                for(int i=iG[u].size()-1; i>=0; i--) dfs_2(iG[u][i]);
        }

        void call() {
                myMemset( vis , 0 );
                for(int i = 0; i < n; i++ ) if( !vis[i] ) dfs_1(i);
                myMemset( vis , 0 );
                components = 0;
                while( stk_sz ) {
                        int i = stk[--stk_sz];
                        if( !myCom[i] ) {
                                myCom[i] = ++components;
                                dfs_2(i);
                        }
                }
                printf("number of components = %d\n",components);
                for(int i = 0; i <= n; i ++ )
                        printf("%d -> %d\n" , i , myCom[i] );
                for( int u = 0 ; u < n ; u ++ ) {
                        for( int i = G[u].size() - 1 ; i >= 0 ; i -- ) {
                                int v = G[u][i];
                                int x = myCom[u] , y = myCom[v];
                                if( x == y ) continue;
                                if( dag[x].find(y) != dag[x].end() ) {
                                        notTree = 1;
                                }
                                dag[x].insert(y);
                        }
                }
        }

        int addEdge(int u, int v) {
                /// 0 <= u,v <= (n-1)
                G[u].push_back(v);
                iG[v].push_back(u);
        }
        void init(int numberOfNodes) {
                n = numberOfNodes;
                for(int i = 0 ; i < M ; i ++ ){
                        G[i].clear();
                        iG[i].clear();
                        dag[i].clear();
                }
                memset( myCom , 0 , sizeof(myCom) );
                stk_sz = components = 0;
        }
}obj;

int main()
{
        return 0;
}
