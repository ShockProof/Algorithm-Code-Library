#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
#define myMemset(a,b) memset(a,b,sizeof(a))
int Case;
/** 1256 - Word Puzzle (Eulerian Path Problem) */

string temp;
stack<string> words[26][26];

int n; /// number of edges

int Graph[26][26];
int inDeg[26];
int outDeg[26];
bool vis[26];

bool weak[26][26];
bool weak_vis[26];
void weak_dfs( int u ) {
        if( weak_vis[u] ) return;
        weak_vis[u] = 1;
        for( int v = 0; v < 26 ; v++ ) {
                if( weak[u][v] ) weak_dfs(v);
        }
}

int edges_sz;
int edges[5000];
bool euler_path_found;
void euler_path( int u )
{
        if( euler_path_found ) return; /// maybe ei line tar dorkar nai
        for( int v = 0 ; v < 26 ; v ++ ) {
                if( !Graph[u][v] ) continue;
                Graph[u][v]--;
                edges[edges_sz++]  = u;
                edges[edges_sz++]  = v;
                euler_path( v );
                if( euler_path_found ) return;
                Graph[u][v]++;
                edges_sz--;
                edges_sz--;
        }
        if( edges_sz == n+n ) euler_path_found = 1;
}

void Main()
{
        edges_sz = 0;

        myMemset( weak_vis , 0 );
        myMemset(      vis , 0 );
        myMemset(    inDeg , 0 );
        myMemset(   outDeg , 0 );
        myMemset(    Graph , 0 );
        myMemset(     weak , 0 );

        for( int i = 0 ; i < 26 ; i ++ ) {
                for( int j = 0 ; j < 26 ; j ++ )
                        while( words[i][j].size() ) words[i][j].pop();
        }

        n = _Int();
        int weak_start;
        for( int i = 0 ; i < n ; i ++ ) {
                cin >> temp;
                int u = temp[0]-'a' , v = temp[temp.size()-1]-'a';
                words[u][v].push( temp );

                Graph[u][v]++;
                inDeg[v]++;
                outDeg[u]++;

                weak_start = u;
                weak[u][v] = weak[v][u] = 1;
        }
        /** has a euler path? */
        weak_dfs( weak_start );
        for( int i = 0 ; i < 26 ; i ++ ) {
                int sz = 0;
                for( int j = 0 ; j < 26 ;  j ++ ) sz += weak[i][j];
                if( sz && !weak_vis[i] ) {
                        printf("Case %d: No\n",Case);
                        return; /// not weakly connected
                }
        }
        int source = weak_start, destination = weak_start;
        for( int i = 0 , src = 0 , des = 0; i < 26 ; i ++ ) {
                if( inDeg[i] == outDeg[i]-1 ) {
                        src++ , source = i;
                }
                if( inDeg[i]-1 == outDeg[i] ) {
                        des++ ,  destination;
                }
                if( abs( inDeg[i]-outDeg[i] ) > 1 ||  src>1 || des>1 ) {
                        printf("Case %d: No\n",Case);
                        return; /// degree problem
                }
        }
        /** it has. now print the path */
        printf("Case %d: Yes\n",Case);
        euler_path_found = 0;
        euler_path( source );
        for( int i = 0 ;  i < edges_sz ; i += 2 ) {
                int u = edges[i] , v = edges[i+1];
                if( i ) putchar(' ');
                cout << words[u][v].top();
                words[u][v].pop();
        }
        putchar(10);
}

int main()
{
        int test = _Int();
        for( Case = 1 ; Case <= test ; Case ++ ) Main();
        return 0;
}
