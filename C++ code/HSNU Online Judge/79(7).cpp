#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,S,K,SUPPLY[100000][21],DEMAND[100000][21],ANS;
vector<int>ET[100000];
void Dfs(const int &u,const int &fa)
{
	int *sup=SUPPLY[u],*dem=DEMAND[u];
	for(int i=0;i<=K;i++)sup[i]=dem[i]=0;
	for(int i=0;i<ET[u].size();i++)
	{
		const int &nxt=ET[u][i];
		if(nxt==fa)continue;
		Dfs(nxt,u);
		for(int i=0;i<K;i++)sup[i]+=SUPPLY[nxt][i+1],dem[i+1]+=DEMAND[nxt][i];
	}
	if(dem[K])
	{
		int d=(dem[K]+S-1)/S;
		sup[K]+=d*S-dem[K],ANS+=d,dem[K]=0;
	}
	dem[0]=1;
	for(int i=0,d;i<=K;i++)d=min(sup[i],dem[i]),sup[i]-=d,dem[i]-=d;
	for(int i=0,d;i<K;i++)d=min(sup[i+1],dem[i]),sup[i+1]-=d,dem[i]-=d;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&S,&K)==3)
	{
		for(int i=1,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		ANS=0;
		Dfs(0,-1);
		int ans=0,*sup=SUPPLY[0],*dem=DEMAND[0];
		for(int i=0;i<=K;i++)
		{
			ans+=dem[i];
			ans-=min(ans,sup[i]);
		}
		printf("%d\n",ANS+(ans+S-1)/S);
		break;
	}
	return 0;
}
