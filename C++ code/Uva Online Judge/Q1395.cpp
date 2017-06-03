#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b,l;
	Edge(int a,int b,int l):a(a),b(b),l(l){}
	bool operator<(const Edge &e)const{return l<e.l;}
};
int N,M;
vector<Edge>EDGE;
int DJ[100],CNT;
void ClearDJ()
{
	for(int i=0;i<N;i++)DJ[i]=i;
	CNT=N;
}
int FindDJ(int a)
{
	if(DJ[a]==a)return a;
	return DJ[a]=FindDJ(DJ[a]);
}
void Connect(int a,int b)
{
	if(FindDJ(a)==FindDJ(b))return;
	CNT--;
	DJ[FindDJ(a)]=FindDJ(b);
}
int Solve()
{
	int l=0,r=-1,ans=INF;
	ClearDJ();
	while(++r<M)
	{
		Connect(EDGE[r].a,EDGE[r].b);
		while(CNT==1)
		{
//			printf("(l,r)=(%d,%d)\n",l,r);
			ans=min(ans,EDGE[r].l-EDGE[l].l);
			ClearDJ();
			l++;
			for(int i=l;i<=r;i++)Connect(EDGE[i].a,EDGE[i].b);
		}
	}
	if(ans==INF)ans=-1;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b,l;
			scanf("%d%d%d",&a,&b,&l);
			a--,b--;
			EDGE.push_back(Edge(a,b,l));
		}
		sort(EDGE.begin(),EDGE.end());
		printf("%d\n",Solve());
	}
	return 0;
}
