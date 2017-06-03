#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,SZ[100000];
vector<int>ET[100000];
int Build(const int u)
{
	SZ[u]=1;
	for(const int nxt:ET[u])SZ[u]+=Build(nxt);
//	printf("sz[%d]=%d\n",u,SZ[u]);
	return SZ[u];
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1,v;i<N;i++)
		{
			scanf("%d",&v),--v;
			assert(v<i);
			ET[v].push_back(i);
		}
		Build(0);
		for(int i=0;i<N;i++)
		{
			long long ans=0,sum=0;
			for(const int nxt:ET[i])
			{
				ans+=sum*SZ[nxt];
				sum+=SZ[nxt];
			}
			ans+=SZ[i]-1;
			ans*=2;
			++ans;
			if(i)putchar(' ');
			printf("%lld",ans);
		}
		puts("");
	}
	return 0;
}
