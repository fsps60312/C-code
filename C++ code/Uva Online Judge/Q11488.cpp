#include<cstdio>
#include<cstdlib>
int T,N,ANS;
char S[201];
struct Trie
{
    struct Node
    {
        int v;
        int ch[2];
    }s[10000000];
    int sz;
    void init(int u){s[u].v=s[u].ch[0]=s[u].ch[1]=0;}
    void clear(){sz=1;init(0);}
    int getch(int u,int i)
    {
        if(!s[u].ch[i])
        {
            s[u].ch[i]=sz;
            init(sz++);
        }
        return s[u].ch[i];
    }
    void insert(char *str)
    {
        str--;
        int u=0;
        for(int i=1;str[i];i++)
        {
            u=getch(u,str[i]-'0');
            if(i*(++s[u].v)>ANS)ANS=i*s[u].v;
        }
    }
}trie;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        trie.clear();
        ANS=0;
        while(N--)
        {
            scanf("%s",S);
            trie.insert(S);
        }
        printf("%d\n",ANS);
    }
    return 0;
}
