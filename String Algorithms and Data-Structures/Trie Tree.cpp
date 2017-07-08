#include<bits/stdc++.h>
using namespace std;

int getId(char c) {
if( c>='0' && c<='9' ) return c-'0';
if( c>='a' && c<='z' ) return (c-'a')+10;
}
char getChar(int i) {
if( i<10 ) return i+'0';
if( i<36 ) return (i-10)+'a';
}

const int M = 200000+9;

struct trie {
        struct nodeDesign{
                int cnt;
                int next[36];
        } node[M];
        int non; /// number of nodes...
        void insert(string s) {
                int len=s.size();
                int now=0;
                for(int i=0; i<len; i++) {
                        int id = getId(s[i]);
                        if(node[now].next[id]==-1)
                                node[now].next[id]=++non;
                        now=node[now].next[id];
                }
                node[now].cnt++;
        }
        string str;
        int cnt;
        void traverse(int u, int pos, string q) {
                if( !cnt ) return;
                if( node[u].cnt && pos >= str.size() ) {
                        cnt--;
                        cout<<"  "<<q<<endl;
                }
                for(int i=0; i<36; i++) {
                        if( pos<str.size() ) {
                                if( getChar(i)==str[pos] && node[u].next[i]!=-1 ) {
                                        string temp = q;
                                        temp.push_back( getChar(i) );
                                        traverse(node[u].next[i], pos+1, temp);
                                }
                        }
                        else {
                                if( node[u].next[i]!=-1 ) {
                                        string temp = q;
                                        temp.push_back( getChar(i) );
                                        traverse( node[u].next[i], pos+1, temp );
                                }
                        }
                }
        }
        void printStrings(string ss) {
                str = ss;
                cout<<str<<endl;
                cnt = 20;
                traverse(0,0,"");
        }
        void clear() {
                non=0;
                for(int i=0; i<M; i++) {
                        for(int j=0; j<36; j++) {
                                node[i].cnt=0;
                                node[i].next[j]=-1;
                        }
                }
        }
} tree;
int main()
{
        string s;
        tree.clear();
        tree.insert("sun");
        while( cin>>s ) {
                if( s[0]=='?' ) {
                        s.erase(0,1);
                        tree.printStrings(s);
                }
                else {
                        s.erase(0,1);
                        tree.insert(s);
                }
        }
        return 0;
}
