#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int N,S,K,FA[100000],W[100000],H[100000];
vector<int>ET[100000],G[100000];
int LIDX[100000][21];
vector<int>COVER[100000][21];
void BuildH(const int &u,const int &fa,const int &dep)
{
	FA[u]=fa;
	H[u]=dep;
	G[dep].push_back(u);
	for(int i=0;i<ET[u].size();i++)
	{
		const int &nxt=ET[u][i];
		if(nxt==fa)continue;
		BuildH(nxt,u,dep+1);
	}
}
bool PutWeapon(int u)
{
	int o=-1;
	for(int i=0;;i++)
	{
		for(int k=i;k<=K;k++)
		{
			vector<int>&v=COVER[u][k];
			int &l=LIDX[u][k];
			while(l<v.size())
			{
				const int &now=v[l];
				if(!W[now])l++;
				else
				{
					if(o==-1||H[now]>H[o])o=now;
					break;
				}
			}
		}
		if(i==K)break;
		u=FA[u];
	}
	if(o!=-1){W[o]--;return false;}
	W[u]+=S-1;
	if(W[u])
	{
		o=u;
		for(int i=0;i<=K;i++,u=FA[u])
		{
			COVER[u][K-i].push_back(o);
		}
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&S,&K)==3)
	{
		for(int i=0;i<N;i++)
		{
			W[i]=0;
			ET[i].clear(),G[i].clear();
			for(int j=0;j<=K;j++)COVER[i][j].clear(),LIDX[i][j]=0;
		}
		for(int i=1,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		BuildH(0,0,0);
		int ans=0;
		for(int h=N-1;h>=0;h--)
		{
			for(int j=0;j<G[h].size();j++)
			{
				const int &u=G[h][j];
				if(PutWeapon(u))ans++;
			}
		}
		printf("%d\n",ans);
		break;
	}
	return 0;
}
