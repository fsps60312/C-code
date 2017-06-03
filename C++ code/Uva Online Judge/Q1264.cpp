#include<cstdio>
#include<cstdlib>
#define LL long long
const LL MOD=9999991;
struct Node
{
    int v,sum;
    Node *ch[2];
    Node(int v):v(v)
    {
        sum=1;
        ch[0]=ch[1]=NULL;
    }
    void maintain()
    {
        sum=1;
        if(ch[0]!=NULL)sum+=ch[0]->sum;
        if(ch[1]!=NULL)sum+=ch[1]->sum;
    }
};
Node *root;
void removetree(Node* &o)
{
    if(o==NULL)return;
    removetree(o->ch[0]);
    removetree(o->ch[1]);
    delete o;
    o=NULL;
}
void insert(Node* &o,int v)
{
    if(o==NULL)
    {
        o=new Node(v);
        return;
    }
    int d=v<o->v?0:1;
    insert(o->ch[d],v);
    o->maintain();
}
LL C[40][20];
LL solve(Node* &o)
{
    if(o==NULL)return 1;
    if(o->ch[0]!=NULL&&o->ch[1]!=NULL)
    {
        LL ans=solve(o->ch[0])*solve(o->ch[1])%MOD;
        ans*=C[o->ch[0]->sum+o->ch[1]->sum][o->ch[0]->sum];
        return ans%MOD;
    }
    else if(o->ch[0]!=NULL)return solve(o->ch[0]);
    else return solve(o->ch[1]);
}
void buildC()
{
    for(int i=1;i<40;i++)
    {
        C[i][0]=1;
        for(int j=1;j<20&&j<i;j++)
        {
            C[i][j]=C[i-1][j]+C[i-1][j-1];
        }
        if(i<20)C[i][i]=1;
    }
}
int T,N;
int main()
{
    buildC();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        removetree(root);
        for(int i=0,j;i<N;i++)
        {
            scanf("%d",&j);
            insert(root,j);
        }
        printf("%lld\n",solve(root));
    }
    return 0;
}
