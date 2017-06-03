#include "lib1692.h"
#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<stack>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
void ReportPath(const vector<int>&ans)
{
	if((int)ans.size()==2)return;
	ReportVst(ans[0]+1);
	for(int i=1;i+1<(int)ans.size();i++)ReportE(ans[i]+1);
	ReportVed(ans[(int)ans.size()-1]+1);
}
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
	while(!ET[u].empty())
	{
		const int ei=*ET[u].begin();
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		DeleteEdge(ei);
		Dfs(nxt,path);
		path.push_back(nxt),path.push_back(ei);
	}
}
int N,M;
void SplitPath(const vector<int>&path)
{
	const int n=path.size();
	int found=-1;
	for(int i=1;i<n;i+=2)if(path[i]>=M){found=i;break;}
	if(found!=-1)
	{
		vector<int>ans;
		ans.push_back(path[(found+1)%n]);
		for(int i=found+2;i!=found;i+=2,i%=n)
		{
			if(path[i]<M)ans.push_back(path[i]);
			else
			{
				ans.push_back(path[(i-1+n)%n]);
				ReportPath(ans);
				ans.clear();
				ans.push_back(path[(i+1)%n]);
			}
		}
		ans.push_back(path[(found-1+n)%n]);
		ReportPath(ans);
		vector<int>().swap(ans);
	}
	else
	{
		vector<int>ans;
		ans.push_back(path[0]);
		for(int i=1;i<n;i+=2)ans.push_back(path[i]);
		ans.push_back(path[0]);
		ReportPath(ans);
	}
}
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
	for(int i=0;i<N;i++)if(!ET[i].empty())
	{
		vector<int>path;
		Dfs(i,path);
		assert(ET[i].empty()&&path[0]==i);
		SplitPath(path);
	}
	Final();
	return 0;
}
