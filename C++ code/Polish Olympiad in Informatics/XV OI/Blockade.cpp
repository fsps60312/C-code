#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<set>
using namespace std;
template<class T>void getmin(T &a,const T &b){if(a<b)a=b;}
void AddEdge(vector<int>*et,const int a,const int b){et[a].push_back(b),et[b].push_back(a);}
int N,M,L,PRE[100000],SZ[100000];
int CUT_ID[100000];
bool VIS[100000];
vector<int>ET[100000],ES[100000];
vector<int>CUT;
int Dfs(const int u,const int parent,int &pre_cnt)
{
	int low=PRE[u]=++pre_cnt;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		const int nxt=ET[u][i];
		if(!PRE[nxt])getmin(low,Dfs(nxt,u,pre_cnt));
		else getmin(low,PRE[nxt]);
	}
	if(low==PRE[u])CUT.push_back(u);
	return low;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),AddEdge(ET,--a,--b);
		for(int i=0;i<N;i++)PRE[i]=0;
		{
			int pre_cnt=0;
			CUT.clear();
			Dfs(0,-1,pre_cnt);
		}
		for(int i=0;i<N;i++)ES[i].clear(),CUT_ID[i]=-1,VIS[i]=false;
		L=(int)CUT.size();
		for(int i=0;i<L;i++)CUT_ID[CUT[i]]=i,VIS[CUT[i]]=true;
		for(int i=0;i<L;i++)
		{
			const int u=CUT[i];
			SZ[i]=1;
			for(int j=0;j<(int)ET[u].size();j++)if(u<ET[u][j]&&CUT_ID[ET[u][j]]!=-1)AddEdge(ES,i,CUT_ID[ET[u][j]]);
		}
		for(int i=0;i<N;i++)if(CUT_ID[i]==-1)
		{
			queue<int>q;q.push(i);
			int &cnt=SZ[L]=0;
			set<int>cut_vis;
			while(!q.empty())
			{
				const int u=q.front();q.pop();
				if(CUT_ID[u]!=-1)cut_vis.insert(CUT_ID[u]);
				if(VIS[u])continue;
				VIS[u]=true,++cnt;
				for(int j=0;j<(int)ET[u].size();j++)q.push(ET[u][j]);
			}
			for(set<int>::iterator it=cut_vis.begin();it!=cut_vis.end();++it)AddEdge(ES,*it,L);
			++L;
		}
		assert(0);
	}
	return 0;
}
