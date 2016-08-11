#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
const LL Mod=2147483647, B=257;

/** Finding Longest Suffix Palindrome of a string */

char s[1000009];

int main()
{
    scanf("%s",s);
    int len=strlen(s);
    LL h1=0,h2=0, X=1;
    int ans=len;
    for(int i=len-1, po=0; i>0; i--) {
        h1 = ( ( (h1*B)%Mod ) + (LL)s[i] ) % Mod;
        h2+= ((LL)s[i]*X) % Mod;
        X=(X*B)%Mod;
        h2%=Mod;
        if(h1==h2) ans=i;
    }
    return 0;
}
