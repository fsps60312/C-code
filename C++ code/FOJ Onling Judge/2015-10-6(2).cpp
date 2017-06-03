#include<cstdio>
#include<cassert>
int N,K,A,M,SUM[2000000],VAL[1000001];
//void assert(bool valid){if(valid)return;for(;;)puts("E");}
void Build(int id,int l,int r)
{
//	assert(id<800000);
	if(l==r)
	{
		SUM[id]=VAL[l];
		return;
	}
	int mid=(l+r)/2;
	Build(id*2,l,mid);
	Build(id*2+1,mid+1,r);
	SUM[id]=SUM[id*2]+SUM[id*2+1];
}
void Set(int id,int l,int r,int L,int R)
{
	if(SUM[id]==0)return;
	if(L<=l&&r<=R)
	{
		SUM[id]=0;
		return;
	}
	if(l>R||r<L)return;
	int mid=(l+r)/2;
	Set(id*2,l,mid,L,R);
	Set(id*2+1,mid+1,r,L,R);
	SUM[id]=SUM[id*2]+SUM[id*2+1];
}
int max(int a,int b){return a>b?a:b;}
int main()
{
	while(scanf("%d%d%d%d",&N,&K,&A,&M)==4)
	{
		int gap=N-(K*A+K-1);
		assert(gap>=0&&N-A+1>=1);
		if(gap>A)gap=A;
		for(int i=1;i<=N-A+1;i++)VAL[i]=0;
		for(int i=1;i<=N-A+1;i+=A+1)for(int j=0;j<=gap;j++)if(i+j<=N-A+1)VAL[i+j]=1;
//		for(int i=1;i<=N;i++)printf("%d",VAL[i]);puts("");
		Build(1,1,N-A+1);
		bool printed=false;
		for(int i=0;i<M;i++)
		{
			static int x;
			scanf("%d",&x);
			if(printed)continue;
			Set(1,1,N-A+1,max(x-A+1,1),x);
//			printf("sum=%d\n",SUM[1]);
			if(SUM[1]==0)
			{
				printed=true;
				printf("%d\n",i+1);
			}
		}
		if(!printed)printf("%d\n",-1);
	}
	return 0;
}
