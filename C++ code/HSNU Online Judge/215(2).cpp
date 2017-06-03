#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cassert>
typedef long long LL;
using namespace std;
int T,N,M,K;
struct Edge
{
	int a,b,c;
	Edge(){}
	Edge(const int &a,const int &b,const int &c):a(a),b(b),c(c){}
	bool operator<(const Edge &e)const{return c<e.c;}
};
vector<Edge>EDGE;
int IDX[100];
vector<int>ET[100];
struct Djset
{
	int dj[100],cnt;
	void Clear(const int &n){cnt=n;for(int i=0;i<n;i++)dj[i]=i;}
	int FindDJ(const int &a){return dj[a]==a?a:(dj[a]=FindDJ(dj[a]));}
	bool Merge(const int &a,const int &b){if(FindDJ(a)==FindDJ(b))return false;cnt--;dj[FindDJ(a)]=FindDJ(b);return true;}
}DJ;
struct Point
{
	int x,y;
	Point(){}
	Point(const int &a,const int &b):x(min(a,b)),y(max(a,b)){}
	bool operator<(const Point &p)const{return x!=p.x?x<p.x:y<p.y;}
};
void Dfs(const int &u,const int &g,const int &c)
{
	if(IDX[u]!=-1){assert(IDX[u]==g);return;}
	IDX[u]=g;
	for(auto &i:ET[u])
	{
		Edge &e=EDGE[i];
		if(e.c==c)continue;
		Dfs(e.a==u?e.b:e.a,g,c);
	}
}
int MarkVertex(const int &c)
{
	int i,g;
	for(i=0;i<N;i++)IDX[i]=-1;
	for(i=0,g=0;i<N;i++)
	{
		if(IDX[i]!=-1)continue;
		Dfs(i,g++,c);
	}
	return g;
}
bool BuildMST(set<int>&costs)
{
	sort(EDGE.begin(),EDGE.end());
	for(int i=0;i<N;i++)ET[i].clear();
	DJ.Clear(N);
	for(int i=0;i<M;i++)
	{
		Edge &e=EDGE[i];
		if(!DJ.Merge(e.a,e.b))continue;
		ET[e.a].push_back(i);
		ET[e.b].push_back(i);
		costs.insert(e.c);
	}
	return DJ.cnt==1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&M,&K);
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			EDGE.push_back(Edge(--a,--b,c));
		}
		set<int>costs;
		if(!BuildMST(costs)){puts("-1");continue;}
		LL ans=1LL;
		for(auto &c:costs)
		{
			int g=MarkVertex(c);
			map<Point,LL>edge;
			for(auto &e:EDGE)
			{
				if(e.c!=c||IDX[e.a]==IDX[e.b])continue;
				Point p=Point(IDX[e.a],IDX[e.b]);
				auto it=edge.find(p);
				if(it==edge.end())edge[p]=1LL;
				else it->second++;
			}
			LL ta=0LL;
//			for(auto it:edge)printf("c=%d:(%d,%d)%d\n",c,it.first.x,it.first.y,it.second);
			for(int s=0,limit=1<<edge.size();s<limit;s++)
			{
				DJ.Clear(g);
				int i=0;
				for(auto it:edge)if(s&(1<<(i++)))if(!DJ.Merge(it.first.x,it.first.y)){DJ.cnt=-1;break;}
				if(DJ.cnt==1)
				{
					LL v=1LL;
					i=0;
					for(auto it:edge)if(s&(1<<(i++)))
					{
//						printf("s=%d,c=%d:(%d,%d)%d\n",s,c,it.first.x,it.first.y,it.second);
						v*=it.second,v%=K;
					}
//					puts("");
					ta+=v,ta%=K;
				}
			}
			ans*=ta,ans%=K;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
