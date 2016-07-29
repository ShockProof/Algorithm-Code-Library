#include <bits/stdc++.h>
using namespace std;

vector<int> graph[101];
int taken[101];
bool visited[101];
bool bipartite_match(int n)
{
    for(int i=graph[n].size()-1; i>=0; i--)
    {
        int now=graph[n][i];
        if(visited[now]==1) continue;
        visited[now]=1;
        if(taken[now]==-1 || bipartite_match(taken[now])==1)
        {
            taken[now]=n;
            return 1;
        }
    }
    return 0;
}

int main()
{
    /**
        factors and multiples problem solution
    **/
    int factors,multiples;
    long long int fac[100],mul[100];
    scanf("%d",&factors);
    for(int i=0; i<factors; i++) scanf("%lld",&fac[i]);
    scanf("%d",&multiples);
    for(int i=0; i<multiples; i++) scanf("%lld",&mul[i]);
    for(int i=0; i<factors; i++)
        for(int j=multiples-1; j>=0; j--)
        {
            if(fac[i]==0 && mul[j]==0) graph[i].push_back(j);
            if(fac[i]!=0 && mul[j]%fac[i]==0) graph[i].push_back(j);
        }

    int cnt=0;
    memset(taken,-1,sizeof(taken));
    for(int i=0; i<factors; i++)
    {
        memset(visited,0,sizeof(visited));
        if( bipartite_match(i)==1 ) cnt++;
    }
    printf("%d\n",cnt);

    return 0;
}
