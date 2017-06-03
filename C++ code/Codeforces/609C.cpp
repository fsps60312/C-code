#include<cstdio>
#include<cassert>
using namespace std;
int N,S[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		int avg=0;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),avg+=S[i];
		avg/=N;
		int ans1=0,ans2=0;
		for(int i=0;i<N;i++)
		{
			if(S[i]<avg)ans1+=avg-S[i];
			if(S[i]>avg+1)ans2+=S[i]-(avg+1);
		}
		printf("%d\n",ans1>ans2?ans1:ans2);
	}
	return 0;
}
