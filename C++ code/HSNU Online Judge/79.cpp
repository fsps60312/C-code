#include<cstdio>
#include<algorithm>
using namespace std;
int N,S,K,H[100000],SZ[100000];
int BuildH(const int &u,const int &fa)
{
	int &h=H[u]=0;
	SZ[u]=1;
	for(int i=0;i<ET[u].size();i++)
	{
		const int &nxt=ET[u][i];
		h=max(h,BuildH(nxt,u)+1);
		SZ[u]+=SZ[nxt];
	}
	return h;
}
int DP[100000][20];
void BuildDP(const int &u,const int &fa)
{
	if(H[u]<=K&&SZ[u]<=S)
	{
		DP[u]=1;
		return;
	}
}
int main()
{
	while(scanf("%d%d%d",&N,&S,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		BuildH(0);
	}
	return 0;
}
