#include <bits/stdc++.h>
using namespace std;
const int M = 1500 + 7;

int getId(char c)   { return (c-'a'); }
char getChar(int i) { return i+'a';   }

struct Trie{
        int cnt;
        Trie *next[26];
        Trie() {
                cnt = 0;
                for( int i = 0 ; i < 26 ; i ++ ) next[i] = NULL;
        }
}*root;

void _insert( char *s ) {
        if( root == NULL ) root = new Trie();
        Trie *now = root;
        for(int i = 0; s[i]; i ++ ) {
                int id = getId( s[i] );
                if( now->next[id] == NULL )
                        now->next[id] = new Trie();
                now = now->next[id];
        }
        now->cnt++;
}

int main()
{
        return 0;
}
