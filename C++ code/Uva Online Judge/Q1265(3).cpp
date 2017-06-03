#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF=2147483647;
int T,N,M,DJ[5000],SZ[5000];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
struct Edge
{
	int a,b,se;
	Edge(){}
	Edge(int a,int b,int se):a(a),b(b),se(se){}
	bool operator<(const Edge &e)const{return se>e.se;}
	int &To(int from){return from!=a?a:b;}
}EDGE[5000*(5000-1)/2];
vector<int>AD[5000];
bool Check(int o)
{
	o=FindDJ(o);
	int mn=INF,mx=-INF;
	for(int u=0;u<N;u++)
	{
		if(FindDJ(u)!=o)continue;
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=EDGE[AD[u][i]];
			int &nxt=e.To(u);
			if(FindDJ(nxt)==o)mn=min(mn,e.se);
			else mx=max(mx,e.se);
		}
		if(mn<=mx)return false;
	}
	return mn>mx;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			for(int i=0;i<N;i++)
			{
				DJ[i]=i;
				SZ[i]=1;
				AD[i].clear();
			}
			for(int i=0;i<M;i++)
			{
				static int a,b,se;
				scanf("%d%d%d",&a,&b,&se);
				a--,b--;
				EDGE[i]=Edge(a,b,se);
			}
			sort(EDGE,EDGE+M);
			for(int i=0;i<M;i++)
			{
				int &a=EDGE[i].a,&b=EDGE[i].b;
				AD[a].push_back(i);
				AD[b].push_back(i);
			}
			int ans=0;
			for(int i=0;i<M;i++)
			{
				int a=EDGE[i].a,b=EDGE[i].b;
				a=FindDJ(a),b=FindDJ(b);
				if(a==b)continue;
				SZ[b]+=SZ[a];
				DJ[a]=b;
//				printf("(%d,%d,%d)",EDGE[i].a+1,EDGE[i].b+1,EDGE[i].se);
				if(Check(b))
				{
					ans+=SZ[b];
//					printf("SZ[%d]=%d",b,SZ[b]);
				}
//				puts("");
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
