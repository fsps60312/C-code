#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
int CNT[7][7];
int GetLen(char *s)
{
	int ans=-1;while(s[++ans]);
	return ans;
}
int DJ[2000001];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
vector<int>VERTEX[7];
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
bool AddEdge(const int a,const int b)
{
	EDGE.push_back(Edge(a,b));
	assert(Find(a)!=Find(b));
	DJ[Find(a)]=Find(b);
}
bool Solve()
{
	EDGE.clear();
	for(int type=1;type<=6;i++)
	{
		if((int)VERTEX[type].size()<CNT[type][type]+1)return false;
		for(int i=(int)VERTEX[type].size()-1,j=0;j<CNT[type][type];i--,j++)
		{
			AddEdge(VERTEX[type][i-1],VERTEX[type][i]),VERTEX[type].pop_back();
		}
	}
	for(int a=1;a<=6;a++)for(int b=1;b<=6;b++)if(a!=b)
	{
		
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<=6;i++)for(int j=0;j<=6;j++)CNT[i][j]=0;
		for(int i=1;i<=6;i++)VERTEX[i].clear();
		for(int i=1;i<=9&&i<=N;i++)VERTEX[1].push_back(i);
		for(int i=10;i<=99&&i<=N;i++)VERTEX[2].push_back(i);
		for(int i=100;i<=999&&i<=N;i++)VERTEX[3].push_back(i);
		for(int i=1000;i<=9999&&i<=N;i++)VERTEX[4].push_back(i);
		for(int i=10000;i<=99999&&i<=N;i++)VERTEX[5].push_back(i);
		for(int i=100000;i<=999999&&i<=N;i++)VERTEX[6].push_back(i);
		for(int i=1;i<N;i++)
		{
			static char v1[70],v2[70];scanf("%s%s",v1,v2);
			int a=GetLen(v1),b=GetLen(v2);
			CNT[a][b]++;
		}
		for(int i=1;i<=N;i++)DJ[i]=i;
		if(!Solve())puts("-1");
		else
		{
			for(const Edge &e:EDGE)printf("%d %d\n",e.a,e.b);
		}
	}
	return 0;
}
