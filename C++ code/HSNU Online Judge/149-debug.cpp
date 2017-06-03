#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn=3000000+10 ;
 
struct node
{
    node *l,*r ;
    int mi,tag ;
    node(){l=r=NULL ; mi=tag=0 ;}
};
 
void push(node *u)
{
    if(!u->tag) return ;
    u->l->mi+=u->tag ; u->l->tag+=u->tag ;
    u->r->mi+=u->tag ; u->r->tag+=u->tag ;
    u->tag=0 ;
}
void pull(node *u){u->mi=min(u->l->mi,u->r->mi) ;}
 
node *build(int l,int r)
{
    if(l==r) return new node ;
    node *u=new node ;
    int mid=(l+r)/2 ;
    u->l=build(l,mid) ;
    u->r=build(mid+1,r) ;
    return u ;
}
void modify(int l,int r,int L,int R,node *u,int add)
{
    if(l==L && r==R){u->tag+=add ; u->mi+=add ; return ;}
    push(u) ;
    int mid=(L+R)/2 ;
    if(r<=mid) modify(l,r,L,mid,u->l,add) ;
    else if(l>mid) modify(l,r,mid+1,R,u->r,add) ;
    else modify(l,mid,L,mid,u->l,add) ,
        modify(mid+1,r,mid+1,R,u->r,add) ;
    pull(u) ;
}
int query(int L,int R,node *u,int pos)
{
    if(L==R) return u->tag ;
    int mid=(L+R)/2 ;
    if(pos<=mid) return query(L,mid,u->l,pos)+u->tag ;
    else return query(mid+1,R,u->r,pos)+u->tag ;
}
void setzero(int L,int R,node *u)
{
    if(L==R)
    {
        if(u->tag>0) u->tag=u->mi=0 ;
        return ;
    }
    push(u) ;
    int mid=(L+R)/2 ;
    if(u->r->mi>0)
    {
        u->r->tag-- ;
        u->r->mi-- ;
        setzero(L,mid,u->l) ;
    }
    else setzero(mid+1,R,u->r) ;
}
 
int a[maxn] ;
vector<int> v(maxn) ;
int ID(int x)
{
    return lower_bound(v.begin(),v.end(),x)-v.begin() ;
}
 
main()
{
	freopen("in.txt","r",stdin);
    int n ; scanf("%d",&n) ;
    LL tot=0 ;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]) , v[i-1]=a[i] , tot+=a[i] ;
    v.resize(n) ;
    sort(v.begin(),v.end()) ;
    v.resize(unique(v.begin(),v.end())-v.begin()) ;
    int sz=v.size() ;
    node *root=build(0,sz) ;
    for(int i=1;i<=n;i++)
    {
        setzero(0,sz,root) ;
        int id=ID(a[i]) ;
        modify(0,id,0,sz,root,-1) ;
        modify(id+1,sz,0,sz,root,1) ;
    }
    LL ans=tot,now=tot ;
    for(int i=0,last=0;i<sz;last=v[i++])
    {
        now+=(LL)query(0,sz,root,i)*(v[i]-last) ;
        ans=min(ans,now) ;
    }
    printf("%lld\n",ans) ;
}

