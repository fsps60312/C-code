#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M;
struct Edge
{
	int a,b,w;
	Edge(){}
	Edge(int a,int b,int w):a(a),b(b),w(w){}
	bool operator<(const Edge &e)const{return w<e.w;}
}EDGE[350*(350-1)/2];
int DJ[350],JUMP[350];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
int Solve()
{
	for(int i=0;i<N;i++)DJ[i]=i,JUMP[i]=i;
	int cnt=N;
	for(int i=0;i<M;i++)
	{
		int &a=EDGE[i].a,&b=EDGE[i].b;
		if(FindDJ(a)!=FindDJ(b))
		{
			DJ[FindDJ(a)]=FindDJ(b);
			cnt--;
		}
		else
		{
			
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d",&M);
		for(int i=0;i<M;i++)
		{
			int &a=EDGE[i].a,&b=EDGE[i].b,&w=EDGE[i].w;
			scanf("%d%d%d",&a,&b,&w);
		}
		sort(EDGE,EDGE+M);
		int ans=Solve();
		printf("%d\n",ans);
	}
	return 0;
}
