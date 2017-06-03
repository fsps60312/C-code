#include<cstdio>
#include<algorithm>
using namespace std; 
int N,M;
struct Edge
{
	int a,b;
	double c;
	Edge(){}
	bool operator<(const Edge &e)const{return c>e.c;}
}EDGE[100000];
int DJ[100000];
int Find(int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
double Solve()
{
	if(N==1)return 0.0;
	int cnt=N;
	for(int i=0;i<M;i++)
	{
		int &a=EDGE[i].a,&b=EDGE[i].b;
//		printf("%d %d %.4f %d (%d,%d)\n",a,b,EDGE[i].c,cnt,Find(a),Find(b));
		if(Find(a)==Find(b))continue;
		if(--cnt==1)return EDGE[i].c;
		DJ[Find(a)]=Find(b);
	}
//	printf("cnt=%d\n",cnt);
	return 0.0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)DJ[i]=i;
		for(int i=0;i<M;i++)
		{
			int &a=EDGE[i].a,&b=EDGE[i].b;
			scanf("%d%d%lf",&a,&b,&EDGE[i].c);
		}
		sort(EDGE,EDGE+M);
		double ans=Solve();
		if(ans==0.0)puts(N==1?"No way.":"The empire of Arcturus is ending.");
		else printf("%.4f\n",ans);
	}
	return 0;
}
