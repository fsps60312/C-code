#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
int N,L[300],C[300];
map<int,int>COST;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&L[i]);
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		COST.clear();
		COST[0]=0;
		for(int i=0;i<N;i++)
		{
			vector<pair<int,int> >add;
			for(const auto &it:COST)
			{
				add.push_back(make_pair(__gcd(it.first,L[i]),it.second+C[i]));
			}
			for(const auto &p:add)
			{
				auto it=COST.find(p.first);
				if(it!=COST.end())
				{
					if(p.second<it->second)it->second=p.second;
				}
				else COST.insert(p);
			}
		}
//		for(const auto &it:COST)printf("%d=%d\n",it.first,it.second);
		auto it=COST.find(1);
		if(it==COST.end())puts("-1");
		else printf("%d\n",it->second);
	}
	return 0;
}
