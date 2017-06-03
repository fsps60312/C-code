#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M,A[100],B[100],DP[10001];
int main()
{
//	freopen("in.txt","r",stdin);
	static int casenumber;scanf("%d",&casenumber);
	while(casenumber--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d%d",&A[i],&B[i]);
		for(int i=0;i<=10000;i++)DP[i]=INF;
		DP[0]=0;
		for(int i=0;i<N;i++)
		{
			for(int j=10000;j>=0;j--)if(DP[j]!=INF)
			{
				assert(j+B[i]<=10000);
				if(DP[j]+A[i]<DP[j+B[i]])DP[j+B[i]]=DP[j]+A[i];
			}
		}
		int ans=0;
		for(int i=10000;i>=0;i--)if(DP[i]<=M){ans=i;break;}
		printf("%d\n",ans);
	}
	return 0;
}
