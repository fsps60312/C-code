#include<cstdio>
#include<vector>
#include<stack>
#include<cassert>
#include<map>
#include<set>
#include<queue>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(int &a,const int b){if(b<a)a=b;}
LL Sq(const LL &x){return x*x;}
LL RANGE[300];
int SCC_IDX[300],SCC_CNT,MNIDX[300];
LL SCCMN[300];
struct Solver1
{
	vector<int>ET[300];
	int PRE[300],LOW[300],PRE_CNT;
	stack<int>STK;
	void Dfs(const int u)
	{
		PRE[u]=LOW[u]=++PRE_CNT;
		STK.push(u);
		for(const auto nxt:ET[u])
		{
			if(!PRE[nxt])
			{
				Dfs(nxt);
				getmin(LOW[u],LOW[nxt]);
			}
			else if(SCC_IDX[nxt]==-1)getmin(LOW[u],PRE[nxt]);
		}
		if(LOW[u]==PRE[u])
		{
			MNIDX[SCC_CNT]=-1;
			LL &mn=SCCMN[SCC_CNT]=INF;
			for(;;)
			{
				const int t=STK.top();STK.pop();
				SCC_IDX[t]=SCC_CNT;
				if(RANGE[t]<mn)mn=RANGE[t],MNIDX[SCC_CNT]=t;
				if(t==u)break;
			}
			assert(MNIDX[SCC_CNT]!=-1);
			SCC_CNT++;
		}
	}
	void clear(const LL &n){for(int i=0;i<n;i++)ET[i].clear();}
	void Build(const LL &n,const LL *x,const LL *y,const LL *radius)
	{
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)
		{
			if(i!=j&&Sq(radius[i]+RANGE[i]+radius[j])>=Sq(x[i]-x[j])+Sq(y[i]-y[j]))ET[i].push_back(j);
		}
	}
	void Solve(const LL &n)
	{
		for(int i=0;i<n;i++)PRE[i]=0,SCC_IDX[i]=-1;
		PRE_CNT=SCC_CNT=0;
		for(int i=0;i<n;i++)if(!PRE[i])Dfs(i);
	}
}SOL1;
int IND[300],DEP[300];
vector<int>ET[300];
void Solve2(const int &n)
{
	for(int i=0;i<SCC_CNT;i++)IND[i]=0,DEP[i]=-1,ET[i].clear();
	for(int i=0;i<n;i++)for(const auto nxt:SOL1.ET[i])if(SCC_IDX[i]!=SCC_IDX[nxt])
	{
		ET[SCC_IDX[i]].push_back(SCC_IDX[nxt]);
		IND[SCC_IDX[nxt]]++;
	}
	queue<int>q;
	map<int,set<int>,greater<int> >ans;
	LL sum=0LL,cnt=0LL;
	for(int i=0;i<SCC_CNT;i++)if(IND[i]==0)
	{
		q.push(i);
		ans[DEP[i]=0].insert(MNIDX[i]);
		sum+=SCCMN[i],cnt++;
	}
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const auto nxt:ET[u])if(DEP[nxt]<DEP[u]+1)DEP[nxt]=DEP[u]+1,q.push(nxt);
	}
	multimap<LL,int>ch;
	for(int i=0;i<SCC_CNT;i++)
	{
		assert(DEP[i]!=-1);
		if(DEP[i]>0)ch.insert(make_pair(SCCMN[i],i));
	}
	do
	{
		auto it=ch.begin();
		while(!ch.empty()&&((it=ch.begin())->first)*cnt<sum)//it.first<sum/cnt
		{
			ans[DEP[it->second]].insert(MNIDX[it->second]);
			sum+=(it->first),cnt++;
			ch.erase(it);
		}
	}while(0);
	assert(!ans.empty());
	static int kase=1;printf("Case #%d:",kase++);
	for(const auto &it1:ans)for(const int it2:it1.second)printf(" %d",it2);
	puts("");
}
LL N;
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%lld",&N)==1);
		assert(N>0&&N<=300);
		static LL x[300],y[300],radius[300];
		for(int i=0;i<N;i++)assert(scanf("%lld%lld%lld%lld",&x[i],&y[i],&radius[i],&RANGE[i])==4);
		SOL1.clear(N);
		SOL1.Build(N,x,y,radius);
		SOL1.Solve(N);
		Solve2(N);
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
