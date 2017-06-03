#include<cstdio>
#include<cassert>
using namespace std;
int N,M,CNT[11];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<=M;i++)CNT[i]=0;
		for(int i=0,v;i<N;i++)scanf("%d",&v),++CNT[v];
		int ans=0;
		for(int i=1;i<=M;i++)for(int j=i+1;j<=M;j++)ans+=CNT[i]*CNT[j];
		printf("%d\n",ans);
	}
	return 0;
}
