#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,X,Y,K;
int DIGIT[10][901][910],PRE[10][901][910];
struct Edge
{
	int u,c;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),c(_c){}
};
vector<Edge>ET[10];
void Dfs(const int u,const int dsum,const int ksum,const int kdigit,const int dep)
{
	if(u==0&&dsum==X&&ksum==Y)return;
	const Edge &e=ET[kdigit][u];
	int &digit=DIGIT[e.u][dsum+u][ksum+e.c];
	if(digit!=-1)
	{
		if(u<digit)digit=u,PRE[e.u][dsum+u][ksum+e.c]=dsum*10*1000+ksum*10+kdigit;
		return;
	}
	digit=u,PRE[e.u][dsum+u][ksum+e.c]=dsum*10*1000+ksum*10+kdigit;
	if(dep==N)return;
	for(int i=0;i<=9;i++)
	{
		Dfs(i,dsum+u,ksum+e.c,e.u,dep+1);
	}
}
vector<int>ANS[10];
bool Solve()
{
	for(int i=0;i<=9;i++)
	{
//		printf("start(%d)\n",i);
		Dfs(i,0,0,0,1);
	}
	for(int i=0;i<10;i++)
	{
		ANS[i].clear();
		if(DIGIT[i][X][Y]!=-1)
		{
			int u=X*10*1000+Y*10+i;
			for(;u!=-1;)
			{
				ANS[i].push_back(DIGIT[u%10][u/10000][u/10%1000]);
				u=PRE[u%10][u/10000][u/10%1000];
			}
		}
	}
	return true;
}
int main()
{
	N=2,X=9,Y=9,K=5;
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	for(int i=0;i<10;i++)//initial number
	{
		ET[i].clear();
		for(int n=0,v,c;n<10;n++)//add n*k
		{
			v=i+n*K,c=v/10+v%10-i;
			ET[i].push_back(Edge(v/10,c));
//			ET[v/10].push_back(Edge(i,c));
		}
	}
	for(int i=0;i<10;i++)for(int j=0;j<=N*9;j++)for(int k=0;k<=(N+1)*9;k++)DIGIT[i][j][k]=-1,PRE[i][j][k]=-1;
	if(!Solve())puts("-1");
	else
	{
		sort(ANS,ANS+10);
		bool found=false;
		for(int i=0;i<10;i++)
		{
			if(ANS[i].empty())continue;
			assert(ANS[i][0]!=0);
			while(ANS[i].size()<N)ANS[i].push_back(0);
			for(int j=0;j<N;j++)printf("%d",ANS[i][j]);
			puts("");
			found=true;
			break;
		}
		assert(found);
	}
	return 0;
}
