#include <bits/stdc++.h>
using namespace std;
/**
 *    Syed Zafrul Lipu (ShockProof)
 *    CSE, University of Asia Pacific
 *    Problem: UVa 10304 - Optimal Binary Search Tree
 **/
const int M = 255;

int main()
{
        int n, v[M], sum[M];
        int dp[M][M], p[M][M];
        while(scanf("%d",&n)==1)
        {
                for(int i=1; i<=n; i++)
                {
                        scanf("%d", &v[i] );
                        sum[i]=sum[i-1]+v[i];
                }

                for(int i=0; i<=n; i++)  /** base cases **/
                {
                        dp[i][i]=0;
                        p[i][i]=i; /** the 2D array 'p[][]' has the root for a part from i to j **/
                }
                for(int l=2; l<=n; l++) /** 'l' stands for the partition length **/
                {
                        for(int f=1,t; (f+l-1)<=n; f++) /** 'f' stands for starting point and 't' stands for the ending point **/
                        {
                                t=f+l-1;
                                dp[f][t]=INT_MAX;
                                for(int i=p[f][t-1]; i<=p[f+1][t]; i++) /** using knuth's optimization **/
                                {
                                        int a=0;
                                        a+= dp[f][i-1] + sum[i-1]-sum[f-1];
                                        a+= dp[i+1][t] + sum[t]-sum[i];
                                        if(dp[f][t]>a)
                                        {
                                                dp[f][t]=a;
                                                p[f][t]=i; /** storing the root node for the partition 'f' to 't' **/
                                        }
                                }
                        }
                }
                printf("%d\n",dp[1][n]);
        }
        return 0;
}
