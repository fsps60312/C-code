#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,X,Y,K;
bool VIS[10000000];
struct Edge
{
	int a,b,d;
	Edge(){}
	Edge(const int _a,const int _b,const int _d):a(_a),b(_b),d(_d){}
};
vector<Edge>EDGE;
vector<int>ET[10000000];
struct Trans
{
	int u,c;
	Trans(){}
	Trans(const int _u,const int _c):u(_u),c(_c){}
};
vector<Trans>TRANS[10];
void TagVIS()
{
	for(int i=0;i<10;i++)for(int j=0;j<=N*9;j++)for(int k=0;k<=(N+1)*9;k++)VIS[j*10000+k*10+i]=false;
	queue<int>q;
	q.push(0);
	VIS[0]=true;
	for(int i=1;i<N;i++)
	{
		for(int j=q.size();j>0;j--)
		{
			int u=q.front();q.pop();
			int dsum=u/10000,ksum=u/10%1000;
			for(int d=0;d<10;d++)
			{
				const Trans &t=TRANS[u%10][d];
				const int nxt=t.u+(dsum+d)*10000+(ksum+t.c)*10;
				if(VIS[nxt])continue;
				VIS[nxt]=true;
				int sz=EDGE.size();
				EDGE.push_back(Edge(u,nxt,d));
				ET[u].push_back(sz),ET[nxt].push_back(sz);
				q.push(nxt);
			}
		}
	}
}
bool Solve()
{
	TagVIS();
	
}
int main()
{
	N=2,X=9,Y=9,K=5;
//	scanf("%d%d%d%d",&N,&X,&Y,&K);
	for(int i=0;i<10;i++)//initial number
	{
		TRANS[i].clear();
		for(int n=0,v,c;n<10;n++)//add n*k
		{
			v=i+n*K,c=v/10+v%10-i;
			TRANS[i].push_back(Trans(v/10,c));
		}
	}
	if(!Solve())puts("-1");
	else
	{
	}
	return 0;
}
