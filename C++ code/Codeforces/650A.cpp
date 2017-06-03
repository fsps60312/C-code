#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef long long LL;
int N;
map<int,LL>A,B;
map<pair<int,int>,LL>C;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		A.clear(),B.clear(),C.clear();
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			A[x]++,B[y]++,C[make_pair(x,y)]++;
		}
		LL ans=0LL;
		for(const auto &it:A)ans+=it.second*it.second;
		for(const auto &it:B)ans+=it.second*it.second;
		for(const auto &it:C)ans-=it.second*it.second;
		printf("%lld\n",(ans-N)/2LL);
	}
	return 0;
}
