#include <bits/stdc++.h>
using namespace std;
/**
    tutorial link : (TopCoder)
    http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=stringSearching
*/

struct Knuth_Morris_Pratt {

    int  F[1000009]; /// failure function; starts from 1 to len (pattern length)
    char text[1000009];                /// starts from 0 to len-1
    char pattern[1000009];             /// starts from 0 to len-1
    int n,m; /// n=test_length and m=pattern_length

    void build_failure_function()
    {
        F[0] = F[1] = 0;
        for(int j, i = 2; i <= m; i++ ) {
            j = F[i - 1];
            while( j && pattern[j]!=pattern[i-1]) j=F[j];
            F[i] = j + (pattern[j]==pattern[i-1]);
        }
    }

    int indx[1000009], sz;
    /// this array contains the starting positions of matches

    int kmp_match()
    {
        n=strlen(text), m=strlen(pattern);
        build_failure_function();
        for(int i=sz=0, j=0; j<n; j++)
        {
            while( i && text[j]!=pattern[i] ) i = F[i];
            if( text[j]==pattern[i] ) {
                i++;
                if(i == m) {
                    indx[sz++] = j - m + 1;
                    i=F[i];
                }
            }
        }
        return sz;
    }
} kmp;

int main()
{
    scanf("%s %s", kmp.text, kmp.pattern );
    printf("%d\n", kmp.kmp_match() );
    return 0;
}
