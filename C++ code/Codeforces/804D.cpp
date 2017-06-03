#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
const int MAX_N=100000,MAX_M=100000,MAX_Q=100000;
template<class T>inline bool getmax(T&a,const T&b){return a<b?a=b,true:false;}
int N,M,Q;
vector<int>ET[MAX_N];
int DIST[MAX_N],GROUP_ID[MAX_N];
vector<vector<int>>DSUM,DIAM;
int Dfs1(const int u,const int pa,bool *vis)
{
	assert(!vis[u]);
	vis[u]=true;
	DIST[u]=0;
	for(const int nxt:ET[u])if(nxt!=pa)getmax(DIST[u],Dfs1(nxt,u,vis)+1);
	return DIST[u];
}
void Dfs2(const int u,const int pa,const int dist,bool *vis,vector<int>&his,const int group_id)
{
	assert(!vis[u]);
	vis[u]=true;
	GROUP_ID[u]=group_id;
	getmax(DIST[u],dist);
	his.push_back(DIST[u]);
	vector<int>lmx,rmx;
	lmx.push_back(0),rmx.push_back(0);
	for(const int nxt:ET[u])if(nxt!=pa)
	{
		lmx.push_back(DIST[nxt]+1);
		rmx.push_back(DIST[nxt]+1);
	}
	lmx.push_back(0),rmx.push_back(0);
	for(int i=1;i<(int)lmx.size();i++)getmax(lmx[i],lmx[i-1]),getmax(rmx[rmx.size()-i-1],rmx[rmx.size()-i]);
	{
		int i=1;
		for(const int nxt:ET[u])if(nxt!=pa)
		{
			Dfs2(nxt,u,max(max(lmx[i-1],rmx[i+1]),dist)+1,vis,his,group_id);
			i++;
		}
	}
}
map<pair<int,int>,double>DPsolve;
double Solve(const int a,const int b)
{
	if(a==b)return -1;
	if(a>b)return Solve(b,a);
	{
		const auto &it=DPsolve.find(make_pair(a,b));
		if(it!=DPsolve.end())return it->second;
	}
	double ans=0;
	const long long defaultDiameter=max(DIAM[a].back(),DIAM[b].back());
	for(int r=(int)DIAM[a].size()-1,l=0;r>=0;r--)
	{
		while(l<(int)DIAM[b].size()&&DIAM[a][r]+1+DIAM[b][l]<defaultDiameter)++l;
		ans+=(double)(DIAM[a][r]+1)*((int)DIAM[b].size()-l)+DSUM[b][l];
		ans+=(double)defaultDiameter*l;
	}
//	for(const int v:DIAM[a])printf(" %d",v);puts("");
//	for(const int v:DIAM[b])printf(" %d",v);puts("");
	ans/=(double)DIAM[a].size();
	ans/=(double)DIAM[b].size();
//	assert(0);
	return DPsolve[make_pair(a,b)]=ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&Q)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		{
			static bool vis[MAX_N];
			for(int i=0;i<N;i++)vis[i]=false;
			for(int i=0;i<N;i++)if(!vis[i])Dfs1(i,-1,vis);
			DSUM.clear();
			DIAM.clear();
			for(int i=0;i<N;i++)vis[i]=false;
			for(int i=0;i<N;i++)if(!vis[i])
			{
				vector<int>his;
				Dfs2(i,-1,0,vis,his,(int)DSUM.size());
				sort(his.begin(),his.end());
				DIAM.push_back(his);
				his.push_back(0);
				for(int j=(int)his.size()-1;j>=1;j--)his[j-1]+=his[j];
				DSUM.push_back(his);
			}
		}
		DPsolve.clear();
		for(int i=0,a,b;i<Q;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			printf("%.10f\n",Solve(GROUP_ID[a],GROUP_ID[b]));
		}
	}
	return 0;
}
