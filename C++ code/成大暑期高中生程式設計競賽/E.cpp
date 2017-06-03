#include<cstdio>
#include<cassert>
#include<vector>
//#include<algorithm>
using namespace std;
int N,M,K;
int S[1000];
vector<int>ET[1000];
int main()
{
//	freopen("ine.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&M,&K);
		for(int i=0;i<M;i++)S[i]=0;
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<K;i++)scanf("%d%d",&a,&b),ET[--a].push_back(--b);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			static int sum[1001];
			sum[M]=0;
			for(int j=M-1;j>=0;j--)sum[j]=sum[j+1]+S[j];
			for(const int nxt:ET[i])ans+=sum[nxt+1],++S[nxt];
		}
		static int kase=0;
		printf("Test case %d: %d\n",++kase,ans);
	}
	return 0;
}
