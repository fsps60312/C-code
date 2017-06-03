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
int DEG[350];
int Solve()
{
	int l=0,r=-1,cnt=N,ans=INF;
	while(++r<M)
	{
		int &a=EDGE[r].a,&b=EDGE[r].b;
		if(!DEG[a]++)cnt--;
		if(!DEG[b]++)cnt--;
		for(;!cnt;l++)
		{
			ans=min(ans,EDGE[r].w-EDGE[l].w);
			int &la=EDGE[l].a,&lb=EDGE[l].b;
			DEG[la]--,DEG[lb]--;
			if(!DEG[la])cnt++;
			if(!DEG[lb])cnt++;
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d",&M);
		for(int i=0;i<N;i++)DEG[i]=0;
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
