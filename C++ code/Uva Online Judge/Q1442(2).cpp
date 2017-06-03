#include<cstdio>
#define min(x,y) (x<y?x:y)
const int INF=2147483647;
int Z,N,F[1000002],C[1000002];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&Z);
	while(Z--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++)scanf("%d",&F[i]);
		for(int i=1;i<=N;i++)scanf("%d",&C[i]);
		F[0]=F[N+1]=C[0]=C[N+1]=INF;
		int l=0,r;
		int ans=0;
		for(;l<=N;)
		{
			for(r=l;r<=N&&F[r]>=F[r+1];r++);
			for(;r<=N&&F[r]<=F[r+1];r++);
			int low=min(F[l],F[r]);
			for(int i=l;i<=r;i++)low=min(low,C[i]);
			for(int i=l;i<=r;i++)if(F[i]<low)ans+=low-F[i];
			for(int i=l;i<=r;i++)printf(" %d",F[i]);puts("");
			printf("(%d,%d)low=%d,ans=%d\n",l,r,low,ans);
			l=r;
		}
		printf("%d\n",ans);
	}
	return 0;
}
