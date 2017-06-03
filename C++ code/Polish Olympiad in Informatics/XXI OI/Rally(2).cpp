#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
const int INF=2147483647;
template<class T>void getmax(T &a,const T&b){if(a<b)a=b;}
pair<int,int>Get(pair<int,int>*dp,const int *path_id,const vector<int>*es,const int u)
{
	pair<int,int>&ans=dp[u];
	if(ans.first!=-1)return ans;
	ans=make_pair(1,-1);
	for(int i=0;i<(int)es[u].size();i++)
	{
		pair<int,int>p=Get(dp,path_id,es,es[u][i]);
		++p.first;
		getmax(ans,p);
	}
	getmax(ans.second,path_id[u]);
	return ans;
}
vector<int>ET[500000],EF[500000];
int N,M,PATH_ID[500000];
vector<int>GetPath(pair<int,int>*dist)
{
	for(int i=0;i<N;i++)dist[i].first=-1;
	vector<int>path;path.push_back(0);
	for(int i=1;i<N;i++)if(Get(dist,PATH_ID,ET,i).first>Get(dist,PATH_ID,ET,path[0]).first)path[0]=i;
	while(!ET[path.back()].empty())
	{
		const int u=path.back();
		path.push_back(ET[u][0]);
		for(int i=1;i<(int)ET[u].size();i++)if(Get(dist,PATH_ID,ET,ET[u][i]).first>Get(dist,PATH_ID,ET,path.back()).first)path.back()=ET[u][i];
	}
	return path;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("raj3ocen.in","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),EF[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),EF[b].push_back(a);
		}
		static pair<int,int>dist[500000];
		const vector<int>&path=GetPath(dist);
		for(int i=0;i<N;i++)dist[i].first=-1,PATH_ID[i]=-1;
		for(int i=0;i<(int)path.size();i++)PATH_ID[path[i]]=(int)path.size()-1-i;
		vector<int>anses;
		anses.resize(path.size(),0);
		for(int i=1;i<(int)path.size();i++)
		{
			const int df=(i-1)-0+1;
			getmax(anses[i],df);
			for(int j=0;j<(int)ET[path[i-1]].size();j++)
			{
				const int nxt=ET[path[i-1]][j];
				if(nxt!=path[i])getmax(anses[i],df+Get(dist,PATH_ID,ET,nxt));
			}
		}
		for(int i=(int)path.size()-1;i>=1;i--)
		{
			const int dt=Get(DT,ET,path[i]);
			getmax(anses[i-1],dt);
			for(int j=0;j<(int)EF[path[i]].size();j++)
			{
				const int nxt=EF[path[i]][j];
				if(nxt!=path[i-1])getmax(anses[i-1],dt+Get(DF,PATH_ID,EF,nxt));
			}
		}
		static bool is_path[500000];
		for(int i=0;i<N;i++)is_path[i]=false;
		for(int i=0;i<(int)path.size();i++)is_path[path[i]]=true;
		for(int i=0;i<N;i++)
		{
			vector<int>tmp;
			for(int j=0;j<(int)ET[i].size();j++)
			{
				const int nxt=ET[i][j];
				if(!is_path[nxt])tmp.push_back(nxt);
			}
			ET[i].swap(tmp);
		}
		if(true)
		{
			int ta=0;
			for(int i=0;i<N;i++)DT[i]=-1;
			for(int i=0;i<N;i++)if(!is_path[i])getmax(ta,Get(DT,ET,i));
			for(int i=0;i<(int)anses.size();i++)getmax(anses[i],ta);
		}
		pair<int,int>ans=make_pair(2147483647,-1);
		for(int i=0;i<(int)anses.size();i++)
		{
//			printf("%d:%d\n",path[i],anses[i]);
			const pair<int,int>&ta=make_pair(anses[i],path[i]);
			if(ta<ans)ans=ta;//,printf("(%d,%d)\n",ta.first,ta.second);
		}
		assert(ans.second!=-1);
		printf("%d %d\n",ans.second+1,ans.first-1);
	}
	return 0;
}
