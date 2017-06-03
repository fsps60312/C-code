#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmax(LL &a,const LL &b){if(b>a)a=b;}
struct Edge
{
	int a,b;
	LL cost;
	bool used;
	Edge(){}
	Edge(const int _a,const int _b,const LL _c):a(_a),b(_b),cost(_c),used(false){}
	int Nxt(const int from)const{return from==a?b:a;}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
struct Djset
{
	vector<int>s;
	void clear(const int n){s.resize(n);for(int i=0;i<n;i++)s[i]=i;}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;s[a]=b;return true;}
}DJ;
vector<Edge>EDGE;
vector<vector<int> >ET;
vector<vector<int> >FA;
vector<vector<LL> >MXE;
vector<int>DEP;
void Dfs(const int u,const int ei,const int dep)
{
	DEP[u]=dep;
	if(ei!=-1)
	{
		LL mxe=EDGE[ei].cost;
		for(int tmp=EDGE[ei].Nxt(u),i=0;;getmax(mxe,MXE[tmp][i]),tmp=FA[tmp][i++])
		{
//			printf("mxe=%lld\n",mxe);
			FA[u].push_back(tmp);
			MXE[u].push_back(mxe);
			if(i>=(int)FA[tmp].size())break;
		}
	}
	for(const auto i:ET[u])if(i!=ei)
	{
		const Edge &e=EDGE[i];
		Dfs(e.Nxt(u),i,dep+1);
	}
}
LL GetMxEdge(int a,int b)
{
	assert(a!=b);
	LL ans=-INF;
	if(DEP[a]<DEP[b])swap(a,b);
	for(int dis=DEP[a]-DEP[b],i=30;i>=0;i--)if(dis&(1<<i))getmax(ans,MXE[a][i]),a=FA[a][i];
	assert(DEP[a]==DEP[b]);
	if(a==b){assert(ans!=-INF);return ans;}
	for(int i=30;i>=0;i--)
	{
		assert(FA[a].size()==FA[b].size());
		if(i<(int)FA[a].size()&&FA[a][i]!=FA[b][i])getmax(ans,max(MXE[a][i],MXE[b][i])),a=FA[a][i],b=FA[b][i];
	}
	assert(DEP[a]==DEP[b]&&FA[a][0]==FA[b][0]);
	return max(ans,max(MXE[a][0],MXE[b][0]));
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	static int casenumber;scanf("%d",&casenumber);
	while(casenumber--)
	{
		scanf("%d%d",&N,&M);
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			static LL cost;scanf("%d%d%lld",&a,&b,&cost);
			EDGE.push_back(Edge(a,b,cost));
		}
		sort(EDGE.begin(),EDGE.end());
		DJ.clear(N);
		ET.clear(),ET.resize(N);
		for(int i=0,cnt=N-1;i<M&&cnt>=0;i++)
		{
			Edge &e=EDGE[i];
			if(!DJ.Merge(e.a,e.b))continue;
			cnt--;
			e.used=true;
			ET[e.a].push_back(i),ET[e.b].push_back(i);
		}
		FA.clear(),MXE.clear(),FA.resize(N),MXE.resize(N);
		DEP.resize(N);
		Dfs(0,-1,0);
		LL ans=INF;
		for(const Edge &e:EDGE)if(!e.used)
		{
//			printf("%lld (%d,%d)=%lld\n",e.cost,e.a,e.b,GetMxEdge(e.a,e.b));
			LL dis=e.cost-GetMxEdge(e.a,e.b);
//			printf("dis=%lld\n",dis);
			assert(dis>=0LL);
			if(dis>0LL&&dis<ans)ans=dis;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
