#include<cstdio>
#include<vector>
using namespace std;
int N,M,DP[200][1000];//pos, speed
struct Road
{
	int to,velo;
	Road(){}
	Road(int to int velo):to(to),velo(velo){}
};
vector<Road>TO[200];
struct Pq
{
	int u,
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
		}
		for(int i=0,a,b,v;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&v);
			TO[a].push_back(b,v);
		}
	}
	return 0;
}
