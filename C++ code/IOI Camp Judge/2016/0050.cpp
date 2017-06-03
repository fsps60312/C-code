#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
//const LL INF=9223372036854775807LL;
vector<LL>S;
LL L,R;
bool VIS[10];
void Dfs(const LL now)
{
	S.push_back(now);
	for(int i=0;i<10;i++)if(!VIS[i])
	{
		if(now==0LL&&i==0)continue;
		VIS[i]=true;
		Dfs(now*10LL+(LL)i);
		VIS[i]=false;
	}
}
int main()
{
	for(int i=0;i<10;i++)VIS[i]=false;
	Dfs(0LL);
	sort(S.begin(),S.end()),S.resize(unique(S.begin(),S.end())-S.begin());
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lld%lld",&L,&R);
		printf("%d\n",upper_bound(S.begin(),S.end(),R)-lower_bound(S.begin(),S.end(),L));
	}
	return 0;
}
