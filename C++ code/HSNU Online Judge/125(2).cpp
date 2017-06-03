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
int S[100001],DJ[100001];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)LOC[i].clear();
		BIT.clear(N*2);
		for(int i=1;i<=N*2;i++)scanf("%d",&S[i]),LOC[--S[i]].push_back(i),DJ[i]=i,BIT.Add(i,1);
		multimap<int,int>sot;
		for(int i=0;i<N;i++)assert((int)LOC[i].size()==2),sot.insert(make_pair(LOC[i][1]-LOC[i][0],i));
		static vector<int>ans;ans.clear();
		for(const auto &it:sot)
		{
			const int l=Find(LOC[it.second][0]),r=Find(LOC[it.second][1]);
			if(r==l)continue;
			const int lsum=BIT.Query(l),rsum=BIT.Query(r);
			printf("(%d,%d)(%d,%d)\n",l,r,lsum,rsum);
			assert(0<lsum&&lsum<rsum);
			DJ[r]=Find(r-1),DJ[l]=Find(l-1);
			BIT.Add(l,-1),BIT.Add(r,-1);
			for(int i=rsum-1,cur=Find(l-1),pre=-1;i>lsum;i--,cur=Find(cur-1))
			{
				if(S[cur]==S[pre])ans.pop_back(),BIT.Add(pre,-1),BIT.Add(cur,-1),DJ[pre]=DJ[cur]=Find(cur-1);
				else ans.push_back(i),pre=cur;
			}
		}
		printf("%d\n",(int)ans.size());
		for(const int v:ans)printf("%d\n",v);
//		break;
	}
	return 0;
}
