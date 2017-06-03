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
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
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
		bool *has_parent=new bool[DEPTH[u]];
		for(int i=0;i<DEPTH[u];i++)has_parent[i]=false;
		for(int i=0;i<(int)parents.size();i++)has_parent[DEPTH[parents[i]]]=true;
		for(int s=0;s<(1<<DEPTH[u]);s++)
		{
			bool covered_by_parents=false;
			for(int i=0;i<(int)parents.size();i++)if(s&(1<<DEPTH[parents[i]])){covered_by_parents=true;break;}
			if(covered_by_parents)
			{
				int nxts=0;
				for(int i=0;i<DEPTH[u];i++)if(s&(1<<i))nxts+=2*POW3[i];
				getmin(dp[nxts],0);
			}
			int nxts=0;
			for(int i=0;i<DEPTH[u];i++)
			{
				if(s&(1<<i))nxts+=2*POW3[i];
				else if(has_parent[i])nxts+=POW3[i];
			}
			getmin(dp[nxts],C[u]);
//			getmin(dp[s],C[u]);
//			int extra=0;
//			vector<int>extras;
//			for(int i=0;i<DEPTH[u];i++)if(Get(nxts,i)==1)extra|=1<<i,extras.push_back(i);
//			for(int t=extra;t;t=(t-1)&extra)
//			{
//				int ts=nxts;
//				for(int i=0;i<(int)extras.size();i++)if(!(t&(1<<extras[i])))ts-=POW3[extras[i]];
//				getmin(dp[ts],C[u]);
//			}
//			vector<int>().swap(extras);
		}
		delete[]has_parent;
	}
	else
	{
		for(int s=0;s<POW3[DEPTH[u]];s++)
		{
			bool covered_by_parents=false;
			for(int i=0;i<(int)parents.size();i++)if(Get(s,DEPTH[parents[i]])==2){covered_by_parents=true;break;}
			if(covered_by_parents)//covered by parents
			{
				int cost=0;
				for(int i=0;i<(int)ch_dps.size();i++)Add(cost,min(ch_dps[i][s],ch_dps[i][s+POW3[DEPTH[u]]]));
				getmin(dp[s],cost);
			}
			assert(!ch_dps.empty());//covered by childs
			{
				int cost=0,min_dif=INF;
				for(int i=0;i<(int)ch_dps.size();i++)
				{
					if(ch_dps[i][s+POW3[DEPTH[u]]]<ch_dps[i][s])printf("%d %d\n",ch_dps[i][s+POW3[DEPTH[u]]],ch_dps[i][s]);
//					assert(ch_dps[i][s+POW3[DEPTH[u]]]>=ch_dps[i][s]);
					if(ch_dps[i][s+POW3[DEPTH[u]]]>=ch_dps[i][s])
					{
						Add(cost,ch_dps[i][s]);
						getmin(min_dif,ch_dps[i][s+POW3[DEPTH[u]]]-ch_dps[i][s]);
					}
					else Add(cost,ch_dps[i][s+POW3[DEPTH[u]]]),min_dif=0;
				}
				Add(cost,min_dif);
				getmin(dp[s],cost);
			}
			if(true)//color myself
			{
				int cost=C[u];
				for(int i=0;i<(int)ch_dps.size();i++)Add(cost,ch_dps[i][s+2*POW3[DEPTH[u]]]);
				int nxts=s;
				for(int i=0;i<(int)parents.size();i++)if(Get(nxts,DEPTH[parents[i]])==0)nxts+=POW3[DEPTH[parents[i]]];
				getmin(dp[nxts],cost);
//				getmin(dp[s],cost);
//				int extra=0;
//				vector<int>extras;
//				for(int i=0;i<DEPTH[u];i++)if(Get(nxts,i)==1)extra|=1<<i,extras.push_back(i);
//				for(int t=extra;t;t=(t-1)&extra)
//				{
//					int ts=nxts;
//					for(int i=0;i<(int)extras.size();i++)if(!(t&(1<<extras[i])))ts-=POW3[extras[i]];
//					getmin(dp[ts],cost);
//				}
//				vector<int>().swap(extras);
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
//			puts("a");
			BuildDepth(i,0);
//			puts("b");
			int *dp=new int[1];
			GetDP(i,dp);
			Add(ans,dp[0]);
		}
		printf("%d\n",ans);
		assert(ans!=INF);
	}
	return 0;
}
