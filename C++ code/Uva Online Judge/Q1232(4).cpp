#include<cstdio>
#include<cstdlib>
struct treetype{int MAX,MIN;};
int T,BN;
treetype ST[400000];
bool TAG[400000];
void buildtree(int id,int l,int r)
{
	ST[id].MAX=ST[id].MIN=TAG[id]=0;
	if(l==r)return;
	int mid=(l+r)/2;
	buildtree(id*2,l,mid);
	buildtree(id*2+1,mid+1,r);
}
void putdown(int id)
{
	if(!TAG[id])return;
	TAG[id]=false;
	TAG[id*2]=TAG[id*2+1]=true;
	ST[id*2]=ST[id*2+1]=ST[id];
}
void update(treetype &a,treetype t1,treetype t2)
{
	a.MIN=t1.MIN<t2.MIN?t1.MIN:t2.MIN;
	a.MAX=t1.MAX>t2.MAX?t1.MAX:t2.MAX;
}
int change(int id,int l,int r,int L,int R,int H)
{
	//printf("LRH=(%d,%d,%d) l=%d r=%d st[id]=(%d,%d)\n",L,R,H,l,r,ST[id].MAX,ST[id].MIN);
	if(l>=L&&r<=R)
	{
		if(ST[id].MAX<=H)
		{
			ST[id].MAX=ST[id].MIN=H;
			TAG[id]=true;
			return r-l+1;
		}
		else if(ST[id].MIN>H)return 0;
		else if(l==r)
		{
			ST[id].MAX=ST[id].MIN=H;
			return 0;
		}
	}
	else if(r<L||l>R)return 0;
	putdown(id);
	int mid=(l+r)/2,ans=0;
	ans+=change(id*2,l,mid,L,R,H);
	ans+=change(id*2+1,mid+1,r,L,R,H);
	update(ST[id],ST[id*2],ST[id*2+1]);
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&BN);
		buildtree(1,1,100000);
		int L,R,H,ans=0;
		while(BN--)
		{
			scanf("%d%d%d",&L,&R,&H);
			int c=change(1,1,100000,L,R-1,H);
			//printf("c=%d\n",c);
			ans+=c;
		}
		printf("%d\n",ans);
	}
	scanf("%d",&T);
	if(T!=0)printf("error\n");
	return 0;
}
