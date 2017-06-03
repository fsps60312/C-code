#include<cstdio>
int N,K,A,M,SUM[400000],TAG[400000];
void Push(int id,int l,int r,int mid)
{
	if(!TAG[id])return;
	TAG[id*2]=TAG[id*2+1]=true,TAG[id]=false;
	SUM[id*2]=mid-l+1,SUM[id*2+1]=r-l;
}
void Build(int id,int l,int r)
{
	SUM[id]=0,TAG[id]=false;
	if(l==r)return;
	int mid=(l+r)/2;
	Build(id*2,l,mid);
	Build(id*2+1,mid+1,r);
}
void Set(int id,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	{
		SUM[id]=r-l+1;
		TAG[id]=true;
		return;
	}
	if(l>R||r<L)return;
	int mid=(l+r)/2;
	Push(id,l,r,mid);
	Set(id*2,l,mid,L,R);
	Set(id*2+1,mid+1,r,L,R);
	SUM[id]=SUM[id*2]+SUM[id*2+1];
}
int main()
{
	while(scanf("%d%d%d%d",&N,&K,&A,&M)==4)
	{
		Build(1,1,N-A+1);
		bool printed=false;
		for(int i=0;i<M;i++)
		{
			static int x;
			scanf("%d",&x);
			if(printed)continue;
			Set(1,1,N-A+1,x-A+1,x);
//			printf("sum=%d\n",SUM[1]);
			if(SUM[1]==N-A+1)
			{
				printed=true;
				printf("%d\n",i+1);
			}
		}
		if(!printed)printf("%d\n",-1);
	}
	return 0;
}
