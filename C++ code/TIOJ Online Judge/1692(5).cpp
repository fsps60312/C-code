#include "lib1692.h"
#include<cstdio>
#include<cassert> 
#include<vector>
#include<set>
#include<stack>
using namespace std;
//void Init(){}
//void GetVE(int &V,int &E){V=5,E=4;}
//void Get(int &a,int &b)
//{
//	static int tick=0;
//	static int as[4]={1,1,3,1},bs[4]={2,2,5,4};
//	a=as[tick],b=bs[tick];
//	tick++;
//}
//void ReportVst(int u){printf("start from %d\n",u);}
//void ReportE(int u){printf(" %d",u);}
//void ReportVed(int u){printf("\nend at %d\n",u);}
//void Final(){}
///////////////////////////////////////////////////////////////
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
set<int>ET[1000];
void AddEdge(const int a,const int b)
{
	assert(a!=b);
	const int sz=EDGE.size();
	EDGE.push_back(Edge(a,b));
	ET[a].insert(sz),ET[b].insert(sz);
}
void DeleteEdge(const int ei)
{
	const Edge &e=EDGE[ei];
	ET[e.a].erase(ei),ET[e.b].erase(ei);
}
void Dfs(const int u,vector<int>&path)
{
	if(ET[u].empty())return;
	int nxt,ei;
	while(!ET[u].empty())
	{
		ei=*ET[u].begin();
		const Edge &e=EDGE[ei];
		nxt=(u==e.a?e.b:e.a);
		DeleteEdge(ei);
		Dfs(nxt,path);
	}
	path.push_back(nxt),path.push_back(ei);
}
int N,M;
int main()
{
	Init();
	GetVE(N,M);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,a,b;i<M;i++)Get(a,b),AddEdge(--a,--b);
	for(int i=0,pre=-1;i<N;i++)if((int)ET[i].size()&1)
	{
		if(pre==-1)pre=i;
		else AddEdge(pre,i),pre=-1;
	}
	for(int i=0;i<N;i++)assert((int)ET[i].size()%2==0);
	vector<vector<int> >paths;
	for(int i=0;i<N;i++)if(!ET[i].empty())
	{
		vector<int>path;
		Dfs(i,path);
		assert(ET[i].empty());
		path.push_back(i);
		paths.push_back(path);
	}
	vector<vector<int> >anses;
	for(const vector<int>&path:paths)
	{
		assert((int)path.size()&1);
		vector<int>ans;
		ans.push_back(path[0]);
		for(int i=1;i<(int)path.size();i+=2)
		{
			if(path[i]<M)ans.push_back(path[i]);
			else
			{
				ans.push_back(path[i-1]);
				assert(ans[0]==ans[ans.size()-1]);
				if((int)ans.size()>2)anses.push_back(ans);
				ans.clear();
				ans.push_back(path[i+1]);
			}
		}
		ans.push_back(path[(int)path.size()-1]);
		anses.push_back(ans);
		vector<int>().swap(ans);
	}
	for(const vector<int>&ans:anses)
	{
		ReportVst(ans[0]+1);
		int u=ans[0];
		for(int i=1;i+1<(int)ans.size();i++)
		{
			ReportE(ans[i]+1);
			const Edge &e=EDGE[ans[i]];
			assert((u==e.a)!=(u==e.b));
			u=(u==e.a?e.b:e.a);
		}
		assert(u==ans[(int)ans.size()-1]);
		ReportVed(u+1);
	}
	Final();
	return 0;
}
