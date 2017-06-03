#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
typedef long long LL;
const LL INF=9223372036854775807LL;
int N,C[500000];
vector<int>ET[500000];
LL CSUM,ANS;
inline void UpdateAns(const LL equal)
{
//	printf("equal=%lld\n",equal);
	if(equal*3<CSUM)return;
	getmin(ANS,equal*3-CSUM);
}
LL Dfs(const int u,const int parent,set<LL>*sz)
{
	LL ans=C[u];
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		set<LL>*chsz=new set<LL>();
		const LL chsum=Dfs(nxt,u,chsz);
		chsz->insert(chsum);
		for(const LL v:*chsz)
		{
			if(sz->find(v)!=sz->end())UpdateAns(v);
			const LL upsum=CSUM-v;
			if(upsum%2==0&&sz->find(upsum/2)!=sz->end())UpdateAns(upsum/2);
			if(sz->find(upsum-v)!=sz->end())UpdateAns(v);
		}
		for(const LL v:*chsz)sz->insert(v);
		ans+=chsum;
	}
//	printf("u=%d,",u+1);for(const LL v:*sz)printf(" %lld",v);puts("");
	if(ans%2==0&&sz->find(ans/2)!=sz->end())UpdateAns(ans/2);
	if(true)
	{
		const LL upsum=CSUM-ans;
		if(sz->find(upsum)!=sz->end())UpdateAns(upsum);
		if(sz->find(ans-upsum)!=sz->end())UpdateAns(upsum);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		CSUM=0;
		for(int i=0;i<N;i++)scanf("%d",&C[i]),CSUM+=C[i];
//		printf("CSUM=%lld\n",CSUM);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		ANS=INF;
		set<LL>*sz=new set<LL>();
		Dfs(0,-1,sz);
//		for(const LL v:*sz)printf(" %lld",v);puts("");
		if(ANS==INF)ANS=-1;
		printf("%lld\n",ANS);
	}
	return 0;
}
