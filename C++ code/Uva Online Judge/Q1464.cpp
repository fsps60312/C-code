#include<cstdio>
#include<vector>
#include<stack>
#include<cassert>
#include<set>
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
vector<int>TREE[110000],FA[110000];
int DEP[110000],CH[110000],ROOT;
void dfs(int u,int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
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
		dfs(k,u);
		getmin(LOW[u],LOW[k]);
		if(LOW[k]>=PRE[u])
		{
			CUT[u]=0;
			TREE[BCC_CNT].clear();
			while(STK.top()!=j)
			{
				BCC[STK.top()]=BCC_CNT;
				STK.pop();
			}
			BCC[j]=BCC_CNT++;
			STK.pop();
		}
	}
}
void BuildTree(int u,int fa,int dep)
{
	FA[u].clear();
	int tmp=1;
	if(fa!=-1)for(int i=0;i<FA[fa].size();i++,tmp<<=1)
	{
		int &f=FA[fa][i];
		FA[u].push_back(TREE[f][CH[f]]);
	}
	if(dep==tmp)FA[u].push_back(ROOT);
	DEP[u]=dep;
	for(int &i=CH[u]=0;i<TREE[u].size();i++)
	{
		int &j=TREE[u][i];
		if(j==fa)continue;
		BuildTree(j,u,dep+1);
	}
}
int GetLen(int a,int b)
{
	int ans=0;
	if(DEP[a]<DEP[b]){static int tmp;tmp=a,a=b,b=tmp;}
	while(DEP[a]>DEP[b])
	{
		static int dis,tmp,idx;
		dis=DEP[b]-DEP[a],tmp=1;
		for(idx=0;idx+1<FA[a].size()&&(tmp<<1)<=dis;idx++,tmp<<=1);
		ans+=tmp;
		a=FA[a][idx];
	}
	assert(DEP[a]==DEP[b]);
	while(a!=b)
	{
		static int tmp,idx,sz;
		tmp=1,sz=FA[a].size();
		for(idx=0;idx+1<sz&&FA[a][idx+1]!=FA[b][idx+1];idx++,tmp<<=1);
		a=FA[a][idx],b=FA[b][idx];
		ans+=tmp*2;
	}
	assert(ans%2==0);
	return ans/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
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
		ROOT=-1;
		for(int i=0,node=BCC_CNT;i<N;i++)
		{
			if(CUT[i]==-1)continue;
			ROOT=i;
			TREE[node].clear();
			CUT[i]=node;
			static set<int>s;s.clear();
			for(int j=0;j<AD[i].size();j++)
			{
				int &bcc=BCC[AD[i][j]];
				if(s.find(bcc)!=s.end())continue;
				s.insert(bcc);
//printf("add(%d):",i);for(int k=0;k<M;k++)if(BCC[k]==bcc)printf(" %d",k);puts(""); 
				TREE[node].push_back(bcc);
				TREE[bcc].push_back(node);
			}
			node++;
		}
		if(ROOT!=-1)BuildTree(ROOT,-1,0);
//		puts("d");
		static int q;scanf("%d",&q);
		while(q--)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			printf("%d\n",GetLen(BCC[a],BCC[b]));
		}
//		puts("e");
	}
	return 0;
}
