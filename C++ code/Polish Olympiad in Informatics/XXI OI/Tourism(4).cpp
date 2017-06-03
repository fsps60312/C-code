#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
int POW3[12];
inline int Get(const int s,const int i){return s/POW3[i]%3;}
inline void Set(int &s,const int i,const int val)
{
	const int dis=val-Get(s,i);
	s+=POW3[i]*dis;
	assert(Get(s,i)==val);
}
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
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
		else if(DEPTH[nxt]<DEPTH[u])parents.push_back(nxt);
	}
	for(int s=0;s<POW3[DEPTH[u]];s++)dp[s]=INF;
	if(ch_dps.empty())
	{
		vector<int>depth_no_parent;
		if(true)
		{
			bool *has_parents=new bool[DEPTH[u]];
			for(int i=0;i<DEPTH[u];i++)has_parents[i]=false;
			for(int i=0;i<(int)parents.size();i++)has_parents[DEPTH[parents[i]]]=true;
			for(int i=0;i<DEPTH[u];i++)if(!has_parents[i])depth_no_parent.push_back(i);
			delete[]has_parents;
		}
		for(int s=0;s<POW3[DEPTH[u]];s++)
		{
			bool covered_by_parents=false,invalid_parents_covered=false;
			for(int i=0;i<(int)parents.size();i++)if(Get(s,DEPTH[parents[i]])==2){covered_by_parents=true;break;}
			for(int i=0;i<(int)depth_no_parent.size();i++)if(Get(s,depth_no_parent[i])==1){invalid_parents_covered=true;break;}
			if(invalid_parents_covered)continue;
			
		}
		vector<int>().swap(depth_no_parent);
	}
	else
	{
		for(int s=0;s<POW3[DEPTH[u]];s++)
		{
			bool covered_by_parents=false,parents_all_covered=true;
			for(int i=0;i<(int)parents.size();i++)if(Get(s,DEPTH[parents[i]])==2){covered_by_parents=true;break;}
			for(int i=0;i<(int)parents.size();i++)if(Get(s,DEPTH[parents[i]])==0){parents_all_covered=false;break;}
			if(covered_by_parents)//covered by parents
			{
				int cost=0;
				for(int i=0;i<(int)ch_dps.size();i++)Add(cost,ch_dps[i][s]);
				getmin(dp[s],cost);
			}
			assert(!ch_dps.empty());//covered by childs
			{
				int cost=0;
				for(int i=0;i<(int)ch_dps.size();i++)Add(cost,ch_dps[i][s+POW3[DEPTH[u]]]);
				getmin(dp[s],cost);
			}
			if(parents_all_covered)//color myself
			{
				int cost=C[u];
				for(int i=0;i<(int)ch_dps.size();i++)Add(cost,ch_dps[i][s+2*POW3[DEPTH[u]]]);
				getmin(dp[s],cost);
			}
		}
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