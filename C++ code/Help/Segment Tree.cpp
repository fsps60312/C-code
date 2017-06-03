#include<stdio.h>
int N,M,A[100000]={0};
int ST[400000]={0};
void Build(int id,int l,int r);
int Query(int id,int l,int r,int L,int R);
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(scanf("%d %d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		Build(1,0,N-1);
		for(int i=0,l,r;i<M;i++)
		{
			scanf("%d %d",&l,&r);
			int sum=Query(1,0,N-1,l,r);
			printf("%d\n",sum);
		}
	}
	return 0;
}
void Build(int id,int l,int r)
{
	if(l==r){ST[id]=A[l];return;}
	int mid=(l+r)/2;
	Build(id*2,l,mid);Build(id*2+1,mid+1,r);
	ST[id]=ST[id*2]+ST[id*2+1];
}
int Query(int id,int l,int r,int L,int R)
{
	if(l>R||r<L)return 0;
	if(L<=l&&r<=R)return ST[id];
	int mid=(l+r)/2;
	return Query(id*2,l,mid,L,R)+Query(id*2+1,mid+1,r,L,R);
}
