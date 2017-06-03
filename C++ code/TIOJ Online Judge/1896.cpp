//#define SELF
#ifndef SELF
#include "lib1896.h"
#endif
#include<cassert>
using namespace std;
int N;
int EDGE[1500][1500];
int DJ[1500];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int hasEdge(int	u,int v)
{
	u=Find(u),v=Find(v);
	--EDGE[u][v],--EDGE[v][u];
	if(EDGE[u][v])return 0;
	DJ[u]=v;
	for(int i=0;i<N;i++)
	{
		const int a=EDGE[u][i];
		EDGE[v][i]+=a,EDGE[i][v]+=a;
	}
	return 1;
}
void initialize(int _N)
{
	N=_N;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=(i!=j);
	for(int i=0;i<N;i++)DJ[i]=i;
}
#ifdef SELF
int main(){return 0;}
#endif
