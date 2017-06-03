#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;
struct DisjointSets
{
	int DATA[500000];
	void Clear(const int n){for(int i=0;i<n;i++)DATA[i]=i;}
	int Find(const int a){return DATA[a]==a?a:(DATA[a]=Find(DATA[a]));}
	int operator[](const int i){return Find(i);}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;DATA[a]=b;return true;}
}DJ;
struct Edge
{
	int a,b;
	int oa,ob;
	Edge(){}
	Edge(const int _a,const int _b,const int _oa,const int _ob):a(min(_a,_b)),b(max(_a,_b)),oa(_oa),ob(_ob){}
	bool operator<(const Edge &e)const{return a!=e.a?a<e.a:b<e.b;}
};
set<Edge>EDGE1,EDGE2;
int N;
set<int>ET1[500000],ET2[500000];
void Erase(set<int>&s,const int v){auto it=s.find(v);assert(it!=s.end());s.erase(it);}
int Merge(int a,int b)
{
	EDGE1.erase(Edge(a,b,-1,-1)),EDGE2.erase(Edge(a,b,-1,-1));
	Erase(ET1[a],b),Erase(ET1[b],a);
	Erase(ET2[a],b),Erase(ET2[b],a);
	if(ET1[a].size()+ET2[a].size()>ET1[b].size()+ET2[b].size())swap(a,b);
	for(const int v:ET1[a])
	{
		ET1[b].insert(v),Erase(ET1[v],a),ET1[v].insert(b);
		const auto it=EDGE1.find(Edge(a,v,-1,-1));
		assert(it!=EDGE1.end());
		Edge e=*it;
		EDGE1.erase(it);
		EDGE1.insert(Edge(b,v,e.oa,e.ob));
	}
	for(const int v:ET2[a])
	{
		ET2[b].insert(v),Erase(ET2[v],a),ET2[v].insert(b);
		const auto it=EDGE2.find(Edge(a,v,-1,-1));
		assert(it!=EDGE2.end());
		Edge e=*it;
		EDGE2.erase(it);
		EDGE2.insert(Edge(b,v,e.oa,e.ob));
	}
	ET1[a].clear(),ET2[a].clear();
	return b;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET1[i].clear(),ET2[i].clear();
		EDGE1.clear(),EDGE2.clear();
		for(int i=0,a,b;i<2*(N-1);i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			auto &et=(i<N-1?ET1:ET2);
			et[a].insert(b),et[b].insert(a);
			(i<N-1?EDGE1:EDGE2).insert(Edge(a,b,a+1,b+1));
		}
		DJ.Clear(N);
		auto edge1=EDGE1,edge2=EDGE2;
		for(auto it=edge1.begin();it!=edge1.end();)
		{
			auto iu=edge2.find(*it);
			if(iu!=edge2.end())
			{
				const int a=DJ[it->a],b=DJ[it->b];
				edge2.erase(iu),edge1.erase(it++);
				const int u=Merge(a,b);
				if(u==a)assert(DJ.Merge(b,a));
				else assert(DJ.Merge(a,b));
			}
			else it++;
		}
		set<int>leafs;
		for(int i=0;i<N;i++)if((int)ET1[i].size()==1)leafs.insert(i);
		vector<pair<pair<int,int>,pair<int,int> > >ans;
		while(!leafs.empty())
		{
			const int u=*leafs.begin();leafs.erase(u);
//			printf("u=%d\n",u);
			assert((int)ET1[u].size()==1);
			const int nxt=*ET1[u].begin();
			const int goal=*ET2[u].begin();
			if(true)
			{
				const auto e1=EDGE1.find(Edge(u,nxt,-1,-1)),e2=EDGE2.find(Edge(u,goal,-1,-1));
				assert(e1!=EDGE1.end());
				assert(e1!=EDGE2.end());
				ans.push_back(make_pair(make_pair(e1->oa,e1->ob),make_pair(e2->oa,e2->ob)));
			}
			ET1[u].erase(nxt),ET1[nxt].erase(u);
			if((int)ET1[nxt].size()==1)leafs.insert(nxt);
			else if(ET1[nxt].empty())leafs.erase(nxt);
			ET1[u].insert(goal),ET1[goal].insert(u);
			Merge(u,goal);
			if(ET1[goal].empty()&&leafs.count(goal))
			{
				leafs.erase(goal),leafs.insert(u);
			}
//			for(int i=0;i<N;i++){printf("%d:",i);for(const int v:ET1[i])printf(" %d",v);puts("");}//puts("");
//			for(int i=0;i<N;i++){printf("%d:",i);for(const int v:ET2[i])printf(" %d",v);puts("");}puts("");
		}
		printf("%d\n",(int)ans.size());
		for(const auto &p:ans)
		{
			printf("%d %d %d %d\n",p.first.first,p.first.second,p.second.first,p.second.second);
		}
	}
	return 0;
}
