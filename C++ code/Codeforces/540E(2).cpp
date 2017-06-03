#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
struct Bit
{
	int S[100001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i){++i;while(i<=N)++S[i],i+=(i&(-i));}
	int Query(int i){++i;int ans=0;while(i)ans+=S[i],i-=(i&(-i));return ans;}
//	int rQuery(int i){return Query(N-1)-Query(i-1);}
}BIT1,BIT2;
map<int,int>S;
void DoSwap(const int a,const int b)
{
	auto it=S.find(a);
	const int av=(it==S.end()?a:it->second);
		 it=S.find(b);
	const int bv=(it==S.end()?b:it->second);
	S[a]=bv,S[b]=av;
}
int N,M,A[100000],B[100000];
vector<int>V;
int Id(const vector<int>&s,const int v){return lower_bound(s.begin(),s.end(),v)-s.begin();}
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
		M=S.size();
		BIT1.Clear(M),BIT2.Clear(M);
		LL ans=0LL;
		for(const auto &p:S)
		{
			ans+=BIT1.Query(M-1)-BIT1.Query(Id(V,p.second));
//			printf("[%d]%d-[%d]%d\n",N-1,BIT1.Query(N-1),Id(V,p.second),BIT1.Query(Id(V,p.second)));
			if(p.second+1<=p.first-1)
			{
//				printf("ans=%lld\n",ans);
				ans+=((p.first-1)-(p.second+1))+1;
//				printf("ans=%lld\n",ans);
				const int r=upper_bound(locs.begin(),locs.end(),p.first-1)-locs.begin()-1;
				const int l=lower_bound(locs.begin(),locs.end(),p.second+1)-locs.begin();
				ans-=BIT2.Query(r)-BIT2.Query(l-1);
//				printf("ans=%lld\n",ans);
			}
			BIT1.Add(Id(V,p.second));
			BIT2.Add(Id(locs,p.first));
//			printf("[%d]=%d,ans=%lld\n",p.first,p.second,ans);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
