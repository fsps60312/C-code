#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
inline void getmax(int &a,const int b){if(a<b)a=b;}
int N;
vector<int>QUERIES,ET[1000000];
int DEPTH[1000000];
void Build(const int u)
{
	DEPTH[u]=1;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		Build(ET[u][i]);
		getmax(DEPTH[u],DEPTH[ET[u][i]]+1);
	}
}
int ANS[1000001],SUM[1000000];
int main()
{
	freopen("in.txt","r",stdin);
	if(true)
	{
		int cnt;
		scanf("%d%d",&N,&cnt);
		QUERIES.clear();
		for(int i=0,v;i<cnt;i++)
		{
			scanf("%d",&v);
			QUERIES.push_back(v);
		}
	}
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=1,fa;i<N;i++)scanf("%d",&fa),ET[--fa].push_back(i);
	Build(0);
	for(int i=1;i<=DEPTH[0];i++)SUM[i]=0;
	for(int i=0;i<N;i++)++SUM[DEPTH[i]];
	for(int i=DEPTH[0]-1;i>=1;i--)SUM[i]+=SUM[i+1]; 
	for(int i=1;i<=N;i++)
	{
		ANS[i]=0;
		for(int j=0;j<DEPTH[0];j++)
		{
			
		}
	}
	return 0;
}
