#include<cstdio>
#include<vector>
#include<stack>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
int N,M;
int PRE[1000],PRE_CNT,LOW[1000],BCC[1000],BCC_CNT;
vector<int>TO[1000];
stack<int>STK;
struct Edge
{
	int a,b;
	bool vis;
	Edge(){}
	Edge(int a,int b):a(a),b(b),vis(false){}
	int To(int from){return from!=a?a:b;}
};
vector<Edge>EDGE;
void dfs(int u,int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(int i=0;i<TO[u].size();i++)
	{
		Edge &e=EDGE[TO[u][i]];
		if(e.vis)continue;
		e.vis=true;
		int j=e.To(u);
		if(!PRE[j])
		{
			dfs(j,u);
			getmin(LOW[u],LOW[j]);
		}
		else
		{
			getmin(LOW[u],PRE[j]);
		}
	}
	if(fa==-1||LOW[u]==PRE[u])
	{
		while(STK.top()!=u)
		{
			BCC[STK.top()]=BCC_CNT;
			STK.pop();
		}
		BCC[u]=BCC_CNT;
		STK.pop();
		BCC_CNT++;
	}
}
int solve()
{
	vector<int>v1;
	for(int i=0;i<N;i++)if(!PRE[i])
	{
		int pre_bcc=BCC_CNT;
		dfs(i,-1);
		v1.push_back(BCC_CNT-pre_bcc);
	}
	for(int i=0;i<BCC_CNT;i++)PRE[i]=0;
	for(int i=0;i<EDGE.size();i++)
	{
		Edge &e=EDGE[i];
		if(BCC[e.a]==BCC[e.b])continue;
		PRE[e.a]++,PRE[e.b]++;
	}
	vector<int>v2;
	for(int i=0,idx=0,cnt=0;i<v1.size();i++,cnt=0)
	{
		for(int j=0;j<v1[i];j++)
		{
			if(PRE[idx++]==1)cnt++;
		}
		v2.push_back(cnt);
	}
	if(v2.size()==1)return (v2[0]+1)/2;
	int ans=0;
	for(int i=0;i<v2.size();i++)
	{
		ans+=(v2[i]-1)/2;
	}
	ans+=v2.size();
	return ans;
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			PRE[i]=0;
			BCC[i]=-1;
		}
		EDGE.clear();
		PRE_CNT=BCC_CNT=0;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			if(a==b)continue;
			a--,b--;
			int sz=EDGE.size();
			EDGE.push_back(Edge(a,b));
			TO[a].push_back(sz);
			TO[b].push_back(sz);
		}
		printf("%d\n",solve());
	}
	return 0;
}
