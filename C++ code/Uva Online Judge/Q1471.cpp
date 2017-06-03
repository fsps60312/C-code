#include<cstdio>
#include<cstdlib>
#define max(x,y) (x)>(y)?(x):(y)
#define min(x,y) (x)<(y)?(x):(y)
const int INF=2147483647;
int T,N,S[200000],R[200000],L[200000],MINMAX[200001],SZ;
int findM(int Min,int Max,int v)
{
	while(Min<Max)
	{
		int mid=(Min+Max)/2;
		if(MINMAX[mid]<v)Min=mid+1;
		else Max=mid;
	}
	return Max-1;
}
int main()
{
	MINMAX[0]=0;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%d",&S[i]);
		}
		for(int i=0;i<N;i++)
		{
			L[i]=R[N-1-i]=1;
			if(i)
			{
				if(S[i]>S[i-1])L[i]=L[i-1]+1;
				if(S[N-1-i]<S[N-i])R[N-1-i]=R[N-i]+1;
			}
		}
		int ans=1;
		SZ=1;
		for(int i=0;i<N;i++)
		{
			int l=findM(0,SZ,S[i]);
			ans=max(ans,R[i]+l);
			if(L[i]>=SZ)MINMAX[SZ++]=INF;
			MINMAX[L[i]]=min(MINMAX[L[i]],S[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
