//#define SELF
#ifndef SELF
#include "lib1692.h"
#endif
#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<stack>
using namespace std;
#ifdef SELF
void Init(){freopen("in.txt","r",stdin);}
void GetVE(int &V,int &E){scanf("%d%d",&V,&E);}
void Get(int &a,int &b)
{
	scanf("%d%d",&a,&b);
//	static int tick=0;
//	static int as[4]={1,1,3,1},bs[4]={2,2,5,4};
//	a=as[tick],b=bs[tick];
//	tick++;
}
void ReportVst(int u){printf("start from %d\n",u);}
void ReportE(int u){printf(" %d",u);}
void ReportVed(int u){printf("\nend at %d\n",u);}
void Final(){}
#endif
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
void Erase(set<int>&s,const int v)
{
	const auto it=s.find(v);
	assert(it!=s.end());
	s.erase(it);
}
void DeleteEdge(const int ei)
{
	const Edge &e=EDGE[ei];
	Erase(ET[e.a],ei);
	Erase(ET[e.b],ei);
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
		assert(path[0]==i);
		paths.push_back(path);
	}
	vector<vector<int> >anses;
	for(const vector<int>&path:paths)
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
					anses.push_back(ans);
					ans.clear();
					ans.push_back(path[(i+1)%n]);
				}
			}
			ans.push_back(path[(found-1+n)%n]);
			anses.push_back(ans);
			vector<int>().swap(ans);
		}
		else
		{
			vector<int>ans;
			ans.push_back(path[0]);
			for(int i=1;i<n;i+=2)ans.push_back(path[i]);
			ans.push_back(path[0]);
			anses.push_back(ans);
		}
	}
	int cnt=0;
	for(vector<int>&ans:anses)if((int)ans.size()>2)
	{
		for(int l=0,r=(int)ans.size()-1;l<r;l++,r--)swap(ans[l],ans[r]);
		ReportVst(ans[0]+1);
		int u=ans[0];
		for(int i=1;i+1<(int)ans.size();i++)
		{
			ReportE(ans[i]+1),cnt++;
			const Edge &e=EDGE[ans[i]];
			assert((u==e.a)!=(u==e.b));
			u=(u==e.a?e.b:e.a);
		}
		assert(u==ans[(int)ans.size()-1]);
		ReportVed(u+1);
	}
	assert(cnt==M);
	Final();
	return 0;
}
