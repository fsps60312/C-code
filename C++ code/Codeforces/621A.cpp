#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		LL ans=0LL;
		vector<int>odd;
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			if(v%2==0)ans+=v;
			else odd.push_back(v);
		}
		sort(odd.begin(),odd.end(),greater<int>());
		for(int i=1;i<(int)odd.size();i+=2)ans+=odd[i-1],ans+=odd[i];
		printf("%lld\n",ans);
	}
	return 0;
}
