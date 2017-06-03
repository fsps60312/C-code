#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
int N,M;
vector<int>ET[100000];
LL A[100000],B[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;
		scanf("%d%d%d",&N,&M,&querycount);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)A[i]=B[i]=0LL;
		LL sum=0LL;
		for(int u,x,y;querycount--;)
		{
			scanf("%d%d%d",&u,&x,&y),u--;
			sum+=y;
			A[u]+=x,B[u]-=y;
		}
		for(int i=0;i<N;i++)
		{
			for(const int nxt:ET[i])A[nxt]+=B[i];
			A[i]+=B[i];
		}
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%lld",sum+A[i]);
		}
		puts("");
	}
	return 0;
}
