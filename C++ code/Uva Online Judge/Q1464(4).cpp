#include<cstdio>
#include<vector>
#include<stack>
#include<set>
#include<cassert>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
int N,M;
int PRE[10000],PRE_CNT,LOW[10000],BCC[100000],BCC_CNT,CUT[10000];
bool VIS[100000];
vector<int>AD[10000];
struct Road
{
	int a,b;
	Road(){}
	Road(int a,int b):a(a),b(b){}
	int To(int from){return from!=a?a:b;}
};
vector<Road>ROAD;
stack<int>STK;
void dfs(int u,int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	int ch=0;
	for(int i=0;i<AD[u].size();i++)
	{
		int &j=AD[u][i];
		if(VIS[j])continue;VIS[j]=true;
		STK.push(j);
		int k=ROAD[j].To(u);
		if(PRE[k])
		{
			getmin(LOW[u],PRE[k]);
			continue;
		}
		ch++;
		dfs(k,u);
		getmin(LOW[u],LOW[k]);
		if(LOW[k]>=PRE[u])
		{
			bool empty=true;
			while(STK.top()!=j)
			{
				empty=false;
				BCC[STK.top()]=BCC_CNT;
				STK.pop();
			}
			CUT[u]=0;
			if(LOW[k]>PRE[u]&&!empty)CUT[k]=0,BCC_CNT++;
			BCC[j]=BCC_CNT++;
			STK.pop();
		}
	}
	if(fa==-1)CUT[u]=ch>=2?0:-1;
}
vector<int>TREE[110000],FA[110000];
int DEP[110000],CH[110000],ROOT;
void BuildTree(int u,int fa,int dep)
{
	assert(!VIS[u]);
	VIS[u]=true;
	FA[u].clear();
	DEP[u]=dep;
	static int tmp;tmp=1;
	if(fa!=-1)for(int i=0;i<FA[fa].size();i++,tmp<<=1)
	{
		int &f=FA[fa][i];
		FA[u].push_back(TREE[f][CH[f]]);
	}
	if(dep==tmp)FA[u].push_back(ROOT);
	for(int &i=CH[u]=0;i<TREE[u].size();i++)
	{
		int &j=TREE[u][i];
		if(j==fa)continue;
		BuildTree(j,u,dep+1);
	}
}
int GetLen(int a,int b)
{
	int ans=0,cnt=0;
	if(DEP[a]<DEP[b]){static int tmp;tmp=a,a=b,b=tmp;}
	while(DEP[a]>DEP[b])
	{
		assert(cnt++<=100);
		static int dis,tmp,idx;
		dis=DEP[a]-DEP[b],tmp=1;
		for(idx=0;idx+1<FA[a].size()&&(tmp<<1)<=dis;idx++,tmp<<=1);
		ans+=tmp;
		a=FA[a][idx];
	}
	cnt=0;
	while(a!=b)
	{
		assert(cnt++<=100);
		static int tmp,idx,sz;
		tmp=1,sz=FA[a].size();
		for(idx=0;idx+1<sz&&FA[a][idx+1]!=FA[b][idx+1];idx++,tmp<<=1);
		a=FA[a][idx],b=FA[b][idx];
		ans+=tmp*2;
	}
	return ans/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		assert(STK.empty());
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
			PRE[i]=0;
			CUT[i]=-1;
		}
		ROAD.clear();
		PRE_CNT=BCC_CNT=0;
		for(int i=0,a,b;i<M;i++)
		{
			VIS[i]=false;
			scanf("%d%d",&a,&b);
			a--,b--;
			static int sz;sz=ROAD.size();
			AD[a].push_back(sz);
			AD[b].push_back(sz);
			ROAD.push_back(Road(a,b));
		}
		for(int i=0;i<N;i++)if(!PRE[i])dfs(i,-1);
		for(int i=0;i<BCC_CNT;i++)TREE[i].clear(),VIS[i]=false;
		for(int i=0,node=BCC_CNT;i<N;i++)
		{
			if(CUT[i]==-1)continue;
			TREE[node].clear(),VIS[node]=false;
			CUT[i]=node;
			static set<int>s;s.clear();
			for(int j=0;j<AD[i].size();j++)
			{
				int &bcc=BCC[AD[i][j]];
				if(s.find(bcc)!=s.end())continue;
				s.insert(bcc);
				TREE[node].push_back(bcc);
				TREE[bcc].push_back(node);
			}
			node++;
		}
		for(int i=0;i<N;i++)if(CUT[i]!=-1&&!VIS[CUT[i]])BuildTree(ROOT=CUT[i],-1,0);
		static int q;scanf("%d",&q);
		while(q--)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			printf("%d\n",GetLen(BCC[a],BCC[b]));
		}
	}
	return 0;
}
