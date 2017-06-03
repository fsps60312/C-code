#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
template<class T>inline void getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,R[1000];
vector<int>ET[1000];
int DP[1000][2];
int GetDP(const int u,const int v)
{
	int &dp=DP[u][v];
	if(dp!=-1)return dp;
	dp=R[u]*v;
	for(const int nxt:ET[u])
	{
		if(v==0)dp+=max(GetDP(nxt,0),GetDP(nxt,1));
		else dp+=GetDP(nxt,0);
	}
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&R[0]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1,v;i<N;i++)
		{
			scanf("%d%d",&v,&R[i]),--v;
			ET[v].push_back(i);
		}
		for(int i=0;i<N;i++)DP[i][0]=DP[i][1]=-1;
		printf("%d\n",max(GetDP(0,0),GetDP(0,1)));
	}
	return 0;
}
