#include<cstdio>
#include<cassert>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
const double PI=acos(-1.0);
typedef long long LL;
int N;
LL R[100000],H[100000];
LL Area(const int i){return R[i]*R[i]*H[i];}
map<LL,LL>DP;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%I64d%I64d",&R[i],&H[i]);
		DP.clear();
		DP[0LL]=0LL;
		for(int i=0;i<N;i++)
		{
			auto it=DP.lower_bound(Area(i));
			it--;
			auto p=make_pair(Area(i),it->second+Area(i));
			it++;
			if(it!=DP.end()&&it->first==p.first&&it->second>=p.second)continue;
			for(;it!=DP.end()&&p.second>=it->second;)DP.erase(it++);
			DP.insert(p);
		}
		printf("%.9f\n",DP.rbegin()->second*PI);
	}
	return 0;
}
