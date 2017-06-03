#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
int T,K;
struct nodetype
{
    int v,f,sum;
    nodetype *ch[2];
    nodetype(int v):v(v)
    {
        f=rand();
        ch[0]=ch[1]=NULL;
        sum=1;
    }
    void maintain()
    {
        sum=1;
        if(ch[0]!=NULL)sum+=ch[0]->sum;
        if(ch[1]!=NULL)sum+=ch[1]->sum;
    }
};
void rotate(nodetype* &o,int d)
{
    nodetype *k=o->ch[d^1];
    o->ch[d^1]=k->ch[d];
    k->ch[d]=o;
    o->maintain(),k->maintain();
    o=k;
}
void insert(nodetype* &o,int v)
{
    if(o==NULL)
    {
        o=new nodetype(v);
        return;
    }
    int d=v<o->v?0:1;
    insert(o->ch[d],v);
    o->maintain();
    if(o->ch[d]->f>o->f)rotate(o,d^1);
}
void removetree(nodetype* &o)
{
    if(o==NULL)return;
    removetree(o->ch[0]);
    removetree(o->ch[1]);
    delete o;
    o=NULL;
}
void remove(nodetype* &o)
{
    int d;
    if(o->ch[0]!=NULL&&o->ch[1]!=NULL)
    {
        d=o->ch[0]->f>o->ch[1]->f?0:1;
        rotate(o,d^1);
        remove(o->ch[d^1]);
        o->maintain();
    }
    else
    {
        nodetype *k=o;
        if(o->ch[0]!=NULL)o=o->ch[0];
        else o=o->ch[1];
        delete k;
    }
}
int queryremove(nodetype* &o,int r)
{
    int tr=1;if(o->ch[0]!=NULL)tr+=o->ch[0]->sum;
    int ans;
    if(r==tr)
    {
        ans=o->v;
        remove(o);
    }
    else if(r<tr)ans=queryremove(o->ch[0],r);
    else ans=queryremove(o->ch[1],r-tr);
    if(o!=NULL)o->maintain();
    return ans;
}
nodetype *root=NULL;
int main()
{
    srand(time(NULL));
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&K);
        removetree(root);
        for(int i=1;i<=K;i++)insert(root,i);
        for(int i=0,j;i<K;i++)
        {
            if(i)printf(" ");
            scanf("%d",&j);
            printf("%d",queryremove(root,j+1));
        }
        printf("\n");
    }
    return 0;
}
