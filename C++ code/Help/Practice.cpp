#include<stdio.h>
int st[400005]={0};
int n,m,A[100005]={0};
void build(int id,int l,int r)
{
	if(l==r){st[id]=A[l]; return;}
	int mid=(l+r)/2;
	build(id*2,l,mid);build(id*2+1,mid+1,r);
	st[id]=st[id*2]+st[id*2+1];
}
int Query(int id,int l,int r,int lb,int rb)
{
	if(rb<l||lb>r) 
	{
		//printf("(%d,%d,%d):%d\n",id,l,r,0);
		return 0;
	}
	if(lb<=l&&rb>=r)
	{
//		printf("(%d,%d,%d):%d\n",id,l,r,st[id]);
		 return st[id];
	}
	int mid=(l+r)/2;
	int ans=Query(id*2,l,mid,lb,rb)+Query(id*2+1,mid+1,r,lb,rb);
//	printf("(%d,%d,%d):%d\n",id,l,r,ans);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&n,&m)==2)
	{
		for(int i=0;i<n;i++) scanf("%d",&A[i]);
		build(1,0,n-1);
		for(int i=0;i<m;i++)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			int sum=Query(1,0,n-1,l,r);
			printf("%d\n",sum);
		 } 
	}
	return 0;
 } 
