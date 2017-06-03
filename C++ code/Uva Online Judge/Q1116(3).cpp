#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
#include<cassert>
#include<set>
using namespace std;
int T,N,M,VIS[10000];
set<int>AD[10000];
struct Deq
{
	vector<int>bse;
	int l,r;
	Deq(){bse.resize(2);Clear();}
	int Sz(){return ((r-l+1)+bse.size())%bse.size();}
	void Clear(){l=0,r=-1;}
	int Idx(int i){return (i%Sz()+Sz())%Sz();}
	int Front(int idx=0){return bse[Idx(l+idx)];}
	int Back(int idx=0){return bse[Idx(r-idx)];}
	int &operator[](int idx){return bse[Idx(l+idx)];}
	bool Empty(){return !Sz();}
	void ExpandSz()
	{
		static vector<int>v;
		v.resize(bse.size()*2);
		static int sz;sz=Sz();
		for(int i=0;i<sz;i++)v[i]=(*this)[i];
		l=0,r=sz-1;
		bse=v;
	}
	void PushFront(int v)
	{
		if(Sz()+1==bse.size())ExpandSz();
		bse[l=Idx(l-1)]=v;
	}
	void PushBack(int v)
	{
		if(Sz()+1==bse.size())ExpandSz();
		bse[r=Idx(r+1)]=v;
	}
	int PopFront(){return bse[l++];}
	int PopBack(){return bse[r--];}
	Deq(int a,int b){bse.resize(2);Clear();PushBack(a);PushBack(b);}
	int A(int idx=0){return Front(idx);}
	int B(int idx=0){return Back(idx);}
	int To(int from){return from!=A()?A():B();}
};
struct Edge
{
	int a,b;
	Edge(){}
	Edge(int a,int b):a(a),b(b){}
	int To(int from){return from!=a?a:b;} 
	bool operator<(const Edge &e)const
	{
		static int x,y,z,w;
		x=min(a,b),y=max(a,b);
		z=min(e.a,e.b),w=max(e.a,e.b);
		return x!=z?x<z:y<w;
	}
}EDGE[9997];
map<Edge,int>ALL;
int GetE(int u,int i)
{
	set<int>::iterator it=AD[u].begin();
	while(i--)it++;
	return *it;
}
int To(int u,int i){return EDGE[GetE(u,i)].To(u);}
int NxtE(int e,int a){return GetE(a,0)!=e?GetE(a,0):GetE(a,1);}
void DeleteEdge(int a,int b)
{
	int e=ALL[Edge(a,b)];
	ALL.erase(Edge(a,b));
	AD[a].erase(e);
	AD[b].erase(e);
}
void PrintAns(int u,int fa)
{
	if(u==0){puts("");return;}
	printf(" %d",u+1);
	if(To(u,0)!=fa)PrintAns(To(u,0),u);
	else PrintAns(To(u,1),u);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			M+=N;
			for(int i=0;i<N;i++)
			{
				AD[i].clear();
				VIS[i]=false;
			}
			ALL.clear();
			for(int i=0,a,b;i<M;i++)
			{
				scanf("%d%d",&a,&b);
				a--,b--;
				AD[a].insert(i);
				AD[b].insert(i);
				EDGE[i]=Edge(a,b);
				ALL[EDGE[i]]=i;
			}
			queue<Edge>q;
			for(int i=0;i<N;i++)
			{
				if(AD[i].size()==2&&!VIS[i])
				{
					int e=GetE(i,0);
					int l=EDGE[e].To(i);
					while(AD[l].size()==2)
					{
						e=NxtE(e,l);
						l=EDGE[e].To(l);
					}
					int r=EDGE[e].To(l);
					while(AD[r].size()==2)
					{
						VIS[r]=true;
						e=NxtE(e,r);
						r=EDGE[e].To(r);
					}
					q.push(Edge(l,r));
				}
			}
			while(!q.empty())
			{
				Edge e=q.front();q.pop();
				int &a=e.a,&b=e.b;
				if(VIS[a]||VIS[b])continue;
//				assert(DEG[a]>2&&DEG[b]>2&&!VIS[a]&&!VIS[b]);
				if(ALL.find(Edge(a,b))!=ALL.end())
				{
					DeleteEdge(a,b);
					M--;
					while(AD[a].size()==2&&a!=b)
					{
						VIS[a]=true;
						if(!VIS[To(a,0)])a=To(a,0);
						else a=To(a,1);
					}
					while(AD[b].size()==2&&b!=a)
					{
						VIS[b]=true;
						if(!VIS[To(b,0)])b=To(b,0);
						else b=To(b,1);
					}
					if(a==b)break;
				}
				q.push(Edge(a,b));
			}
			assert(M==N);
			for(int i=0;i<N;i++)assert(AD[i].size()==2);
			printf("1");
			if(To(0,0)<To(0,1))PrintAns(To(0,0),0);
			else PrintAns(To(0,1),0);
		}
	}
	return 0;
}
