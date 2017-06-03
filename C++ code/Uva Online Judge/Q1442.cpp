#include<cstdio>
#define min(x,y) (x<y?x:y)
int Z,N,F[1000000],C[1000000];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&Z);
	while(Z--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&F[i]);
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		int l=0,r;
		for(;l+1<N&&F[l+1]>=F[l];l++);
		int ans=0;
		for(;l<N;)
		{
			for(r=l;r+1<N&&F[r+1]<=F[r];r++);
			for(;r+1<N&&F[r+1]>=F[r];r++);
			int low=min(F[l],F[r]);
			for(int i=l;i<=r;i++)low=min(low,C[i]);
			for(int i=l;i<=r;i++)if(F[i]<low)ans+=low-F[i];
			printf("(%d,%d)\n",l,r);
			l=++r;
		}
		printf("%d\n",ans);
	}
	return 0;
}
