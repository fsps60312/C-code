#include<bits/stdc++.h>
#define INF 2000000000
using namespace std;
const int maxn=2000000+10 ;
 
struct node
{
    node *l,*r ;
    int tag,mi ;
    node(){l=r=NULL ; tag=mi=0 ;}
}pool[2*maxn];
int pcnt ;
 
node *newnode()
{
    node *u=&pool[pcnt++] ;
    u->l=u->r=NULL ;
    u->tag=u->mi=0 ;
    return u ;
}
 
node *build(int l,int r)
{
    if(l==r) return newnode() ;
    node *u=newnode() ;
    int mid=(l+r)/2 ;
    u->l=build(l,mid) ;
    u->r=build(mid+1,r) ;
    return u ;
}
 
inline void pull(node *u){u->mi=min(u->l->mi,u->r->mi);}
inline void push(node *u)
{
    if(!u->tag) return ;
    u->l->tag+=u->tag ; u->l->mi+=u->tag ;
    u->r->tag+=u->tag ; u->r->mi+=u->tag ;
    u->tag=0 ;
}
 
void modify(int l,int r,int L,int R,node *u,int val)
{
    if(l==L && r==R)
    {
        u->tag+=val ; u->mi+=val ;
        return ;
    }
    push(u) ;
    int mid=(L+R)/2 ;
    if(r<=mid) modify(l,r,L,mid,u->l,val) ;
    else if(l>mid) modify(l,r,mid+1,R,u->r,val) ;
    else modify(l,mid,L,mid,u->l,val) ,
        modify(mid+1,r,mid+1,R,u->r,val) ;
    pull(u) ;
}
 
struct node2
{
    node2 *l,*r ;
    int ll,rl,len,tag ;
    node2(){l=r=0 ; ll=rl=len=1 ; tag=0 ;}
};
void pull(node2 *u,int l,int r)
{
    if(u->tag){u->ll=u->rl=u->len=0 ; return ;}
    if(!u->l){u->ll=u->rl=u->len=1 ; return ;}
    int mid=(l+r)/2 ;
    u->ll=(u->l->ll==mid-l+1 ? u->l->ll+u->r->ll : u->l->ll) ;
    u->rl=(u->r->rl==r-mid ? u->r->rl+u->l->rl : u->r->rl) ;
    u->len=max(max(u->l->len,u->r->len),u->l->rl+u->r->ll) ;
}
 
node2 *build2(int l,int r)
{
    if(l==r) return new node2 ;
    node2 *u=new node2 ;
    int mid=(l+r)/2 ;
    u->l=build2(l,mid) ;
    u->r=build2(mid+1,r) ;
    pull(u,l,r) ;
    return u ;
}
 
void modify2(int l,int r,int L,int R,node2 *u,int val)
{
    if(!(L<=l && l<=r && r<=R)){printf("7421\n") ; exit(0) ;}
    if(l==L && r==R){u->tag+=val ; pull(u,L,R) ; return ;}
    int mid=(L+R)/2 ;
    if(r<=mid) modify2(l,r,L,mid,u->l,val) ;
    else if(l>mid) modify2(l,r,mid+1,R,u->r,val) ;
    else modify2(l,mid,L,mid,u->l,val) ,
        modify2(mid+1,r,mid+1,R,u->r,val) ;
    pull(u,L,R) ;
}
 
int n,m,num ;
struct rec
{
    int x1,y1,x2,y2,val ;
    void scan(){scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&val) ;}
}r[maxn];
 
struct event
{
    int y,x1,x2,val ;
    bool operator < (const event &rhs) const
    {
        return y<rhs.y ;
    }
}ev[maxn];
 
int cal(int x)
{
    pcnt=0 ;
    node *root=build(1,n-x+1) ;
    int ecnt=0 ;
    for(int i=0;i<num;i++)
    {
        int x1=max(r[i].x1-x+1,1),x2=min(r[i].x2,n-x+1) ;
        int y1=max(r[i].y1,x),y2=min(r[i].y2+x-1,m) ;
        ev[ecnt++]=(event){y1,x1,x2,r[i].val} ;
        ev[ecnt++]=(event){y2+1,x1,x2,-r[i].val} ;
    }
    sort(ev,ev+ecnt) ;
    int ret=INF ;
    for(int i=x,j=0;i<=m;i++)
    {
        for(;j<ecnt && ev[j].y<=i;j++)
            modify(ev[j].x1,ev[j].x2,1,n-x+1,root,ev[j].val) ;
        ret=min(ret,root->mi) ;
    }
    return ret ;
}
 
event add[maxn],sub[maxn] ;
main()
{
//    freopen("pbs14a.in","r",stdin) ;
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
    int B ;
	while(scanf("%d%d%d%d",&n,&m,&B,&num) ==4)
	{
	    for(int i=0;i<num;i++) r[i].scan() ;
	    if(B)
	    {
	        int L=0,R=min(n,m)+1 ;
	        while(R-L>1)
	        {
	            int mid=(L+R)/2 ;
	            if(cal(mid)<=B) L=mid ;
	            else R=mid ;
	        }
	        printf("%d\n",L) ;
	        continue;
	    }
	 
	    for(int i=0;i<num;i++)
	        add[i]=(event){r[i].y1,r[i].x1,r[i].x2,1} ,
	        sub[i]=(event){r[i].y2,r[i].x1,r[i].x2,-1} ;
	    sort(add,add+num) ; sort(sub,sub+num) ;
	    node2 *root=build2(1,n) ;
	    int ans=0 ;
	    for(int le=1,ri=0,cnt1=0,cnt2=0;le<=m;le++)
	    {
	        for(;ri<m && root->len>=ri-le+1;)
	        {
	            ans=max(ans,ri-le+1) ;
	            ri++ ;
	            for(;cnt2<num && add[cnt2].y<=ri;cnt2++)
	                modify2(add[cnt2].x1,add[cnt2].x2,1,n,root,1) ;
	        }
	        if(root->len>=ri-le+1) ans=max(ans,ri-le+1) ;
	        for(;cnt1<num && sub[cnt1].y<=le;cnt1++)
	            modify2(sub[cnt1].x1,sub[cnt1].x2,1,n,root,-1) ;
	    }
	    printf("%d\n",ans) ;
	}
	return 0;
}
