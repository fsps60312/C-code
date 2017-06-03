#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef long long LL;
map<int,LL>A,B;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		A.clear(),B.clear();
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			A[x+y]++,B[x-y]++;
		}
		LL ans=0LL;
		for(const auto &it:A)ans+=it.second*(it.second-1LL)/2LL;
		for(const auto &it:B)ans+=it.second*(it.second-1LL)/2LL;
		printf("%lld\n",ans);
	}
}
