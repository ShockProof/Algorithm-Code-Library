#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
int n, hist[100000];
LL _histogram()
{
    stack<int> s;
    LL max_area = 0, area;
    int i=0, _top;
    while ( s.size() || i<n )
    {
        if ( (i<n) && ( s.empty() || hist[s.top()] <= hist[i]) )
            s.push(i++);
        else {
            _top = s.top();
            s.pop();
            area = (LL)hist[_top] * (s.empty() ? i : i - s.top() - 1);
            if (max_area < area) max_area = area;
        }
    }
    return max_area;
}
int Case=0;
void Main()
{
    scanf("%d",&n);
    for(int i=0; i<n; i++) scanf("%d",&hist[i]);
    printf("Case %d: %lld\n",++Case, _histogram() );
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) Main();
}
/**
this code is the solution of a lightoj problem 1083 - Histogram

for tutorial and detail:
    http://www.geeksforgeeks.org/largest-rectangle-under-histogram/

for more advance problem with solution:
    http://codeforces.com/contest/547/submission/11324856
*/
