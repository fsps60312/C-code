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
void Eliminate(const int l,const int r)
{
	DJ[l]=Find(l-1),DJ[r]=Find(r-1);
	BIT.Add(l,-1),BIT.Add(r,-1);
}
int main()
{
	freopen("in.txt","r",stdin);
	DJ[0]=0;
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)LOC[i].clear();
		BIT.clear(N*2);
		for(int i=1;i<=N*2;i++)scanf("%d",&S[i]),LOC[--S[i]].push_back(i),BIT.Add(i,1),DJ[i]=i;
		multimap<int,int>sot;
		for(int i=0;i<N;i++)sot.insert(make_pair(LOC[i][1]-LOC[i][0],i));
		static vector<int>ans;ans.clear();
		for(const auto &it:sot)
		{
			const int l=LOC[it.second][0],r=LOC[it.second][1];
			if(Find(l)<l)continue;
			const int lsum=BIT.Query(l),rsum=BIT.Query(r);
			assert(lsum<rsum);
			assert(Find(l)==l),assert(Find(r)==r);
			for(int i=rsum-1,cur=Find(r-1),pre=r;i>lsum;i--)
			{
				if(S[cur]==S[pre])ans.pop_back(),Eliminate(cur,pre);
				else ans.push_back(i);
				pre=cur,cur=Find(cur-1);
			}
			Eliminate(l,r);
		}
		printf("%d\n",(int)ans.size());
		for(const int v:ans)printf("%d\n",v);
//		break;
	}
	return 0;
}
