#include <bits/stdc++.h>
using namespace std;
inline int _Int() { int x; scanf("%d",&x); return x; }
/*************************************************************************************************************************
**                                            Syed Zafrul Lipu (ShockProof)                                              *
**                                            CSE, University of Asia Pacific                                            *
**************************************************************************************************************************/
const int M = 200000 + 7;
struct SuffixArray {
    struct State {
        int x[2],i;
        bool operator == (const State &Ref) const{
            return x[0]==Ref.x[0] && x[1]==Ref.x[1];
        }
        bool operator < (const State &Ref) const{
            if( x[0] == Ref.x[0] ) return x[1] <Ref.x[1];
            return x[0] < Ref.x[0];
        }
    } A[M];
    int n, R[ 25 ][ M ], k;
    void buildSuffixArray(char *s, int Length) {
        n = Length;
        for(int i=0; i<n; i++ ) R[0][i] = s[i]-'A';
        k = 0;
        for(int x = 1; x < n; x = x<<1 ) {
            for(int i = 0, j; i<n; i++) {
                j = i+x;
                A[i].i = i;
                A[i].x[0] = R[k][i];
                A[i].x[1] = (j<n) ? R[k][j] : -1;
            }
            k++;
            sort( A, A+n );
            for(int i=0; i<n; i++) {
                R[k][ A[i].i ] = (i&&A[i]==A[i-1]) ? R[k][ A[i-1].i ] : i;
            }
        }
    }
    int lcp[M];
    void buildLcp() {
        for(int i=0; i<n; i++) {
            lcp[i] = 0;
            if(!i) continue;
            int x = A[i-1].i, y = A[i].i;
            for(int j=k-1; j>=0; j--) {
                if( R[j][x]==R[j][y] ) {
                    lcp[i] += (1<<j);
                    x += (1<<j), y += (1<<j);
                }
            }
        }
    }
}obj;

int main() {
    return 0;
}
