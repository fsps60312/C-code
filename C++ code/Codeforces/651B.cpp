#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
int N;
map<int,int>S;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,v;i<N;i++)scanf("%d",&v),S[v]++;
		int ans=0;
		for(const auto &it:S)if(it.second>ans)ans=it.second;
		printf("%d\n",N-ans);
	}
	return 0;
}
