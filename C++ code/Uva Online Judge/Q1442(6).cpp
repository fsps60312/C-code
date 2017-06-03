#include<cstdio>
#define min(x,y) (x<y?x:y)
const int INF=2147483647;
int Z,N,F[1000000],C[1000000],R[1000000],L[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&Z);
	while(Z--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&F[i]);
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		int now=R[0]=C[0];
		for(int i=1;i<N;i++)
		{
			if(now>C[i])now=C[i];
			if(now<F[i])now=F[i];
			R[i]=now;
		}
		now=L[N-1]=C[N-1];
		for(int i=N-2;i>=0;i--)
		{
			if(now>C[i])now=C[i];
			if(now<F[i])now=F[i];
			L[i]=now;
		}
		int ans=0;
		for(int i=0;i<N;i++)ans+=min(R[i],L[i])-F[i];
		printf("%d\n",ans);
	}
	return 0;
}
