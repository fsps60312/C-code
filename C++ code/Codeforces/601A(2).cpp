#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
//const int INF=2147483647;
struct Pq
{
	int A,B,DIST;
	Pq(){}
	Pq(const int _A,const int _B,const int _DIST):A(_A),B(_B),DIST(_DIST){}
};
bool operator<(const Pq &a,const Pq &b){return a.DIST>b.DIST;}
int N,M,DIST[400][400];
vector<int>ET[400];
bool V1[400][400],V2[400][400];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=-1,V1[i][j]=V2[i][j]=false;
		priority_queue<Pq>pq;pq.push(Pq(0,0,0));
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(DIST[p.A][p.B]!=-1)continue;
			DIST[p.A][p.B]=p.DIST;
			if(p.A!=0&&p.A==p.B)continue;
			for(const int mida:ET[p.A])if(!V1[mida][p.B])
			{
				V1[mida][p.B]=true;
				for(const int bnxt:ET[p.B])if(!V2[mida][bnxt])
				{
					V2[mida][bnxt]=true;
					for(const int anxt:ET[mida])
					{
						pq.push(Pq(anxt,bnxt,p.DIST+1));
					}
				} 
			}
		}
		printf("%d\n",DIST[N-1][N-1]);
	}
	return 0;
}
