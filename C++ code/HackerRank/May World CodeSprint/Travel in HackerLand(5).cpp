#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost):a(_a),b(_b),cost(_cost){}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
void Erase(set<int>&s,const int val)
{
	const auto &it=s.find(val);
	assert(it!=s.end());
	s.erase(it);
}
int N,M,Q,COLOR[100000];
set<int>EQ[100000];
vector<Edge>EDGE,QUERY;
int ANS[100000];
struct DisjointSet
{
	int PARENT[100000],SZ[100000];
	multimap<int,int>QIN[100000];
	set<int>CS[100000];
	void Clear()
	{
		for(int i=0;i<N;i++)PARENT[i]=i,QIN[i].clear(),CS[i].clear(),CS[i].insert(COLOR[i]),SZ[i]=1;
	}
	int Find(const int a){return PARENT[a]==a?a:(PARENT[a]=Find(PARENT[a]));}
	bool Merge(int a,int b,const int cost)
	{
		if((a=Find(a))==(b=Find(b)))return false;
		if(SZ[a]>SZ[b])swap(a,b);
		for(const int qid:EQ[a])
		{
			const Edge &q=QUERY[qid];
			assert((Find(q.a)==a)!=(Find(q.b)==a));
			const int nxt=Find(Find(q.a)==a?q.b:q.a);
			if(nxt==b)Erase(EQ[nxt],qid),QIN[b].insert(make_pair(q.cost,qid));
			else EQ[b].insert(qid);
		}
		EQ[a].clear();
		for(const int c:CS[a])CS[b].insert(c);
		CS[a].clear();
		for(const auto &p:QIN[a])QIN[b].insert(p);
		QIN[a].clear();
		while(!QIN[b].empty()&&QIN[b].begin()->first<=(int)CS[b].size())ANS[QIN[b].begin()->second]=cost,QIN[b].erase(QIN[b].begin());
		SZ[b]+=SZ[a],SZ[a]=0;
		PARENT[a]=b;
		return true;
	}
}DJ;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&Q)==3)
	{
//		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%d",&COLOR[i]);
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			assert(a!=b);
			EDGE.push_back(Edge(a,b,c));
//			ET[a].push_back(i),ET[b].push_back(i);
		}
		for(int i=0;i<N;i++)EQ[i].clear();
		QUERY.clear();
		DJ.Clear();
		for(int i=0,a,b,k;i<Q;i++)
		{
			scanf("%d%d%d",&a,&b,&k),--a,--b;
			QUERY.push_back(Edge(a,b,k));
			ANS[i]=-1;
			if(a==b)
			{
//				if(k==1)ANS[i]=0;
//				else
				DJ.QIN[a].insert(make_pair(k,i));
			}
			else EQ[a].insert(i),EQ[b].insert(i),++DJ.SZ[a],++DJ.SZ[b];
		}
		sort(EDGE.begin(),EDGE.end());
		for(const Edge &e:EDGE)
		{
//			printf("e.cst=%d\n",e.cost);
			DJ.Merge(e.a,e.b,e.cost);
		}
		for(int i=0;i<Q;i++)printf("%d\n",ANS[i]);
	}
	return 0;
}
