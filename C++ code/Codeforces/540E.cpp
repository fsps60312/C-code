#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
struct Bit
{
	int S[100001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i){++i;while(i<=N)++S[i],i+=(i&(-i));}
	int Query(int i){++i;int ans=0;while(i)ans+=S[i],i-=(i&(-i));return ans;}
	int rQuery(int i){int ans=0;while(i)ans+=S[i],i-=(i&(-i));return N-ans;}
}BIT;
map<int,int>S;
void DoSwap(const int a,const int b)
{
	auto it=S.find(a);
	const int av=(it==S.end()?a:it->second);
		 it=S.find(b);
	const int bv=(it==S.end()?b:it->second);
	S[a]=bv,S[b]=av;
}
int N,A[100000],B[100000];
vector<int>V;
int Query()
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		S.clear();
		for(int i=0;i<N;i++)scanf("%d%d",&A[i],&B[i]),DoSwap(A[i],B[i]);
		V.clear();
		vector<int>locs;
		for(const auto &p:S)V.push_back(p.second),locs.push_back(p.first);
		sort(V.begin(),V.end()),sort(locs.begin(),locs.end());
		BIT.Clear(N);
		LL ans=0LL;
		int vis=0;
		for(const auto &p:S)
		{
			ans+=BIT.rQuery(Id(p.second));
			if(p.second<p.first)
			{
				ans+=((p.first-1)-p.second)-(upper_bound(locs.begin(),locs.end(),p.first-1)-lower_bound(locs.begin(),locs.end(),p.second+1));
			}
			BIT.Add(Id(p.second));
		}
	}
	return 0;
}
