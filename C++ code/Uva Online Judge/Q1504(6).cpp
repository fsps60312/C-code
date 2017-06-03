#include<cstdio>
#include<map>
#include<algorithm>
#include<cassert>
#include<vector>
using namespace std;
int N,M,DJ[3000];
vector<int>USED,VIS;
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
vector<int>AD[3000],OA[3000];
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(int _a,int _b,int _c):a(min(_a,_b)),b(max(_a,_b)),cost(_c){}
	int &To(int from){return from!=a?a:b;}
	bool operator<(const Edge &e)const{return a!=e.a?a<e.a:b<e.b;}
	bool operator==(const Edge &e)const{return a==e.a&&b==e.b;}
}EDGE[3000*2999/2];
bool cmpcost(const Edge &a,const Edge &b){return a.cost<b.cost;}
map<Edge,int>ME;
int KASE=0,VK=0,INIANS;
void Dfs(int u,int fa,vector<int>&node)
{
	assert(VIS[u]!=VK);
	VIS[u]=VK;
	node.push_back(u);
	for(int i=0;i<AD[u].size();i++)
	{
		int &j=AD[u][i];
		if(j==fa)continue;
		Dfs(j,u,node);
	}
}
int Adjust(int idx,int tc)
{
//	return 0;
	if(USED[idx]!=KASE)return INIANS;
//	printf("idx=%d\n");
	int &a=EDGE[idx].a,&b=EDGE[idx].b;
	vector<int>node;
	VK++;
	Dfs(a,b,node);
	int ans=tc;
	for(int i=0;i<node.size();i++)
	{
		int &u=node[i];
		for(int j=0;j<OA[u].size();j++)
		{
			Edge &e=EDGE[OA[u][j]];
			if(e==EDGE[idx])continue;
			int &nxt=e.To(u);
			if(VIS[nxt]==VK)continue;
			ans=min(ans,e.cost);
			break;
		}
	}
//	printf("INIANS=%d,idx=%d,tc=%d,ans=%d\n",INIANS,idx,tc,ans);
	return INIANS-EDGE[idx].cost+ans;
}
bool cmpAD(const int &a,const int &b){return EDGE[a].cost<EDGE[b].cost;}
int main()
{
//	for(int i=0;i<3000*2999/2;i++)USED[i]=VIS[i]=0;
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		while(USED.size()<M)USED.push_back(0),VIS.push_back(0);
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
			OA[i].clear();
			DJ[i]=i;
		}
		for(int i=0;i<M;i++)
		{
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			EDGE[i]=Edge(a,b,c);
		}
		sort(EDGE,EDGE+M,cmpcost);
		KASE++;
		INIANS=0;
		int cnt=N;
		ME.clear();
		for(int i=0;i<M;i++)
		{
			ME[EDGE[i]]=i;
			int &a=EDGE[i].a,&b=EDGE[i].b;
//			printf("%d %d %d\n",EDGE[i].a,EDGE[i].b,EDGE[i].cost);
			OA[a].push_back(i),OA[b].push_back(i);
			if(FindDJ(a)==FindDJ(b))continue;
			INIANS+=EDGE[i].cost;
			AD[a].push_back(b);
			AD[b].push_back(a);
			USED[i]=KASE;
			DJ[FindDJ(a)]=FindDJ(b);
			cnt--;
//			if(cnt==1)break;
		}
		for(int i=0;i<N;i++)sort(AD[i].begin(),AD[i].end(),cmpAD);
//		printf("INIANS=%d\n",INIANS);
		assert(cnt==1);
		double ans=0.0;
		int Q;
		scanf("%d",&Q);
		for(int i=0;i<Q;i++)
		{
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			Edge e=Edge(a,b,c);
			assert(ME.find(e)!=ME.end());
			int j=ME[e];
			int da=Adjust(j,c);
//			printf("da=%d\n");
			ans+=da;
		}
		printf("%.4f\n",ans/Q);
	}
	return 0;
}

