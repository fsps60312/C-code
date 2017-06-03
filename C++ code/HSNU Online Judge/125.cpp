#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
struct Bit
{
	int s[100001],n;
	void clear(const int _n){n=_n;for(int i=1;i<=n;i++)s[i]=0;}
	void Add(int i,const int v){while(i<=n)s[i]+=v,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=s[i],i-=(i&(-i));return ans;}
}BIT;
int N;
vector<int>LOC[50000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)LOC[i].clear();
		BIT.clear(N*2);
		for(int i=1,v;i<=N*2;i++)scanf("%d",&v),LOC[--v].push_back(i),BIT.Add(i,1);
		multimap<int,int>sot;
		for(int i=0;i<N;i++)assert((int)LOC[i].size()==2),sot.insert(make_pair(LOC[i][1]-LOC[i][0],i));
		static vector<int>ans;ans.clear();
		for(const auto &it:sot)
		{
			const int l=LOC[it.second][0],r=LOC[it.second][1];
			const int lsum=BIT.Query(l),rsum=BIT.Query(r);
			assert(lsum<rsum);
			for(int i=rsum-1;i>lsum;i--)ans.push_back(i);
			BIT.Add(l,-1),BIT.Add(r,-1);
		}
		printf("%d\n",(int)ans.size());
		for(const int v:ans)printf("%d\n",v);
		break;
	}
	return 0;
}
