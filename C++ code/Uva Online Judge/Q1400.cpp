#include<cstdio>
#include<cstdlib>
#define LL long long
struct treetype{LL x,y1,y2,z;};
struct pairtype{LL x,y;};
LL S[500001],Ssum[500001],n,m;
treetype st[4000000];
LL max(LL a,LL b,LL c)
{
	if(a<b)a=b;
	if(a<c)a=c;
	return a;
}
LL max(LL a,LL b){return a>b?a:b;}
LL sum(LL a,LL b){return Ssum[b]-Ssum[a-1];}
pairtype newpair(LL a,LL b){pairtype c;c.x=a,c.y=b;return c;}
void buildtree(LL id,LL l,LL r)
{
	if(l==r)
	{
		st[id].x=st[id].y1=st[id].y2=st[id].z=l;
		return;
	}
	LL mid=(l+r)/2;
	buildtree(id*2,l,mid);
	buildtree(id*2+1,mid+1,r);
	LL a=sum(l,st[id*2].x),b=sum(l,st[id*2+1].x),c;
	st[id].x=a>=b?st[id*2].x:st[id*2+1].x;
	a=sum(st[id*2].z,r),b=sum(st[id*2+1].z,r);
	st[id].z=a>=b?st[id*2].z:st[id*2+1].z;
	a=sum(st[id*2].y1,st[id*2].y2),b=sum(st[id*2].z,st[id*2+1].x),c=sum(st[id*2+1].y1,st[id*2+1].y2);
	if(a>=b)
	{
		if(a>=c)st[id].y1=st[id*2].y1,st[id].y2=st[id*2].y2;
		else st[id].y1=st[id*2+1].y1,st[id].y2=st[id*2+1].y2;
	}
	else if(b>=c)st[id].y1=st[id*2].z,st[id].y2=st[id*2+1].x;
	else st[id].y1=st[id*2+1].y1,st[id].y2=st[id*2+1].y2;
}
LL queryleft(LL id,LL l,LL r,LL L,LL R)//x~R
{
	if(l>=L&&r<=R)return st[id].z;
	if(l>R||r<L)return -1;
	LL mid=(l+r)/2;
	LL a=queryleft(id*2,l,mid,L,R),b=queryleft(id*2+1,mid+1,r,L,R);
	if(a==-1)return b;
	if(b==-1)return a;
	return sum(a,R)>=sum(b,R)?a:b;
}
LL queryright(LL id,LL l,LL r,LL L,LL R)
{
	if(l>=L&&r<=R)return st[id].x;
	if(l>R||r<L)return -1;
	LL mid=(l+r)/2;
	LL a=queryright(id*2,l,mid,L,R),b=queryright(id*2+1,mid+1,r,L,R);
	if(a==-1)return b;
	if(b==-1)return a;
	return sum(L,a)>=sum(L,b)?a:b;
}
pairtype query(LL id,LL l,LL r,LL L,LL R)
{
	if(l>=L&&r<=R)return newpair(st[id].y1,st[id].y2);
	if(l>R||r<L)return newpair(-1,-1);
	LL mid=(l+r)/2;
	pairtype a=query(id*2,l,mid,L,R)
		,b=newpair(queryleft(id*2,l,mid,L,mid),queryright(id*2+1,mid+1,r,mid+1,R))
		,c=query(id*2+1,mid+1,r,L,R);
	pairtype ans=newpair(L,L);
	if(a.x!=-1&&a.y!=-1&&sum(a.x,a.y)>sum(ans.x,ans.y))ans=a;
	if(b.x!=-1&&b.y!=-1&&sum(b.x,b.y)>sum(ans.x,ans.y))ans=b;
	if(c.x!=-1&&c.y!=-1&&sum(c.x,c.y)>sum(ans.x,ans.y))ans=c;
	return ans;
}
int main()
{
	LL kase=1;
	Ssum[0]=0;
	while(scanf("%lld%lld",&n,&m)==2)
	{
		for(LL i=1;i<=n;i++)
		{
			scanf("%lld",&S[i]);
			Ssum[i]=Ssum[i-1]+S[i];
		}
		buildtree(1,1,n);
		printf("Case %lld:\n",kase++);
		for(LL i=0,a,b;i<m;i++)
		{
			scanf("%lld%lld",&a,&b);
			pairtype c=query(1,1,n,a,b);
			printf("%lld %lld\n",c.x,c.y);
		}
	}
	return 0;
}
