#include<cstdio>
#include<vector>
#include<cassert>
#include<utility>
#include<set>
#include<algorithm>
using namespace std;
int N,M;
struct Edge
{
	int a,b,type;
	Edge(){}
	Edge(const int _a,const int _b,const int _t):a(_a),b(_b),type(_t){}
	bool operator<(const Edge &e)const
	{
		if(type!=e.type)return type<e.type;
		return a!=e.a?a<e.a:b<e.b;
	}
};
set<Edge>ANS;
vector<int>ET[100000];
bool VIS[100000];
vector<vector<int> >LINK;
void Dfs(const int u,vector<int>&link)
{
	assert(!VIS[u]);
	VIS[u]=true;
	link.push_back(u);
	int cnt=0;
	for(const int nxt:ET[u])if(!VIS[nxt])Dfs(nxt,link),cnt++;
	assert(cnt<=1);
}
bool Cmp(const vector<int>&a,const vector<int>&b){return a.size()>b.size();}
void AddEdge(const int a,const int b,const int type){ANS.insert(Edge(a,b,type));}
bool Solve()
{
	if(N<=2)return M==0;
	for(int i=0;i<N;i++)VIS[i]=false;
	LINK.clear();
	for(int i=0;i<N;i++)if((int)ET[i].size()==1&&!VIS[i])
	{
		vector<int>s;Dfs(i,s);
		LINK.push_back(s);
	}
	for(int i=0;i<N;i++)if(!VIS[i])
	{
		vector<int>s;Dfs(i,s);
		LINK.push_back(s);
	}
	sort(LINK.begin(),LINK.end(),Cmp);
	ANS.clear();
	const int l0sz=LINK[0].size();
	if(l0sz==1)
	{
		assert((int)LINK.size()>=2);
		AddEdge(LINK[0][0],LINK[1][0],1);
		for(int i=0;i<2;i++)LINK.erase(LINK.begin());
	}
	else if(l0sz==2||l0sz==3)
	{
		const vector<int>&s=LINK[0];
		for(int i=0;i<(int)s.size();i++)AddEdge(s[i],s[(i+1)%l0sz],0);
		LINK.erase(LINK.begin());
	}
	else if(l0sz==4)
	{
		const vector<int>&s=LINK[0];
		AddEdge(s[0],s[1],0),AddEdge(s[2],s[3],0);
		AddEdge(s[0],s[2],1),AddEdge(s[1],s[3],1);
		LINK.erase(LINK.begin());
	}
	else if(l0sz>=5)
	{
		const int n=LINK[0].size();
		vector<int>tmp;
		int cur=0;
		while(cur<n)tmp.push_back(cur),cur+=2;
		if(cur==n)
		{
			tmp.push_back(1),cur=n-1;
			while(cur>1)tmp.push_back(cur),cur-=2;
		}
		else
		{
			cur=1;
			while(cur<n)tmp.push_back(cur),cur+=2;
		}
		assert((int)tmp.size()==n);
		for(int i=0;i<n;i++)AddEdge(LINK[0][tmp[i]],LINK[0][tmp[(i+1)%n]],1);
		tmp.clear(),vector<int>().swap(tmp);
		LINK.erase(LINK.begin());
	}
	else assert(0);
	int time=2;
	for(const auto &s:LINK)
	{
		vector<Edge>a,b;
		for(auto it=ANS.begin();a.size()<s.size();it++)a.push_back(*it);
		for(int i=0;i<(int)s.size();i++)
		{
			b.push_back(Edge(a[i].a,s[i],time++));
			b.push_back(Edge(s[i],a[i].b,time++));
		}
		for(const auto &v:a)ANS.erase(v);
		for(const auto &v:b)ANS.insert(v);
	}
	while(!ANS.empty()&&((ANS.begin()->type)==0||(int)ANS.size()>M))ANS.erase(ANS.begin());
	return (int)ANS.size()==M;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		if(Solve())for(const auto &e:ANS)printf("%d %d\n",e.a+1,e.b+1);
		else puts("-1");
		break;
	}
	return 0;
}
/*
4 3
1 2
2 3
3 4
*/
