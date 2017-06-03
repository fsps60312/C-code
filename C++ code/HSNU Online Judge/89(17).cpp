#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,X,Y,K,MX,MN;
struct Edge
{
	int u,c;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),c(_c){}
};
vector<Edge>ET[10];
int ANS[100],IDX;
bool VIS[100][901][910];
bool Dfs(const int digit,const int dep)
{
	IDX=dep;
	ANS[dep]=digit;
	int dsum=0,ksum=0,kdigit=0;
	for(int i=dep;i<N;i++)
	{
		dsum+=ANS[i];
		const Edge &e=ET[kdigit][ANS[i]];
		ksum+=e.c;
		kdigit=e.u;
	}
	if(VIS[dep][dsum][ksum])return false;
	VIS[dep][dsum][ksum]=true;
	if(dsum+9*dep<X||dsum>X)return false;
	if(dsum==X&&ksum==Y)return true;
	if(dep==0)return false;
	for(int i=0;i<=9;i++)if(Dfs(i,dep-1))return true;
	return false;
}
bool Solve()
{
	for(int i=1;i<=9;i++)if(Dfs(i,N-1))return true;
	return false;
}
int main()
{
//	N=2,X=9,Y=9,K=5;
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	for(int i=0;i<10;i++)//initial number
	{
		ET[i].clear();
		MX=-INF,MN=INF;
		for(int n=0,v,c;n<10;n++)//add n*k
		{
			v=i+n*K,c=v/10+v%10-i;
			ET[i].push_back(Edge(v/10,c));
			MX=max(MX,c),MN=min(MN,c);
		}
	}
	for(int i=0;i<=N*9;i++)for(int j=0;j<=(N+1)*9;j++)for(int n=0;n<N;n++)VIS[n][i][j]=false;
	if(!Solve())puts("-1");
	else
	{
		for(int i=N-1;i>=IDX;i--)printf("%d",ANS[i]);
		for(int i=IDX-1;i>=0;i--)printf("0");
		puts("");
	}
	return 0;
}
