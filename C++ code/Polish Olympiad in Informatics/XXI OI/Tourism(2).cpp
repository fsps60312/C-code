#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
int POW3[12];
inline int Digit(const int s,const int i){return s/POW3[i]%3;}
inline void SetDigit(int &s,const int i,const int val)
{
	s=s/POW3[i+1]*POW3[i+1]+val*POW3[i]+s%POW3[i];
}
int N,M;
vector<int>ET[20000];
int C[20000],DEPTH[20000];
void BuildDepth(const int u,const int depth)
{
	assert(DEPTH[u]==-1);
	DEPTH[u]=depth;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(DEPTH[nxt]==-1)BuildDepth(nxt,depth+1);
	}
}
inline void Add(int &a,const int b)
{
	if(a==INF||b==INF){a=INF;return;}
	a+=b;
}
//typedef long long LL;
void GetDP(const int u,int *dp)
{
	vector<int*>ch_dps;
	vector<int>parents;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(DEPTH[nxt]==DEPTH[u]+1)
		{
			int *ch_dp=new int[POW3[DEPTH[nxt]]];
//			printf("%d->%d\n",u+1,nxt+1);
			GetDP(nxt,ch_dp);
			ch_dps.push_back(ch_dp);
		}
		else if(DEPTH[nxt]<DEPTH[u])parents.push_back(DEPTH[nxt]);
	}
	for(int s=0;s<POW3[DEPTH[u]];s++)dp[s]=INF;
	for(int s=0;s<POW3[DEPTH[u]+1];s++)
	{
		const int d=Digit(s,DEPTH[u]);
		if(true)
		{
			int covered_by_parents=0;
			for(int i=0;i<(int)parents.size();i++)if(Digit(s,parents[i])==2){covered_by_parents=1;break;}
			if(covered_by_parents==1&&d==0)continue;
		}
		const int nxts0=s%POW3[DEPTH[u]];
		int nxts1=nxts0;
		for(int i=0;i<(int)parents.size();i++)if(Digit(nxts1,parents[i])==0)SetDigit(nxts1,parents[i],1);
		int cost0=0;for(int i=0;i<(int)ch_dps.size();i++)Add(cost0,ch_dps[i][s]);
		int cost1=cost0;
		Add(cost1,C[u]);
		if(d==0)getmin(dp[nxts1],cost1);
		else if(d==1)
		{
			getmin(dp[nxts1],cost1);
			getmin(dp[nxts0],cost0);
		}
		else if(d==2)getmin(dp[nxts1],cost1);
		else assert(0);
	}
	for(int i=0;i<(int)ch_dps.size();i++)delete[]ch_dps[i];
	vector<int*>().swap(ch_dps);
	vector<int>().swap(parents);
}
int main()
{
	freopen("in.txt","r",stdin);
	POW3[0]=1;
	for(int i=1;i<=11;i++)POW3[i]=POW3[i-1]*3;
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)DEPTH[i]=-1;
		int ans=0;
		for(int i=0;i<N;i++)if(DEPTH[i]==-1)
		{
			puts("a");
			BuildDepth(i,0);
			puts("b");
			int *dp=new int[1];
			GetDP(i,dp);
			Add(ans,dp[0]);
		}
		printf("%d\n",ans);
		assert(ans!=INF);
	}
	return 0;
}
