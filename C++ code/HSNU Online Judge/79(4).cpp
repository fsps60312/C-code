#include<cstdio>
#include<vector>
#include<set>
using namespace std;
int N,S,K,FA[100000],W[100000],H[100000];
vector<int>ET[100000],G[100000];
set<int>COVER[100000][21];
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
			set<int>&s=COVER[u][k];
			static vector<set<int>::iterator>rem;rem.clear();
			for(auto it=s.begin();it!=s.end();it++)
			{
				if(!W[*it])rem.push_back(it);
				else if(o==-1||H[*it]>H[o])o=*it;
			}
			for(int j=0;j<rem.size();j++)s.erase(rem[j]);
		}
		if(i==K)break;
		u=FA[u];
	}
	if(o!=-1){W[o]--;return false;}
	W[u]+=S-1;
	o=u;
	if(W[u])
	{
		for(int i=0;i<=K;i++,u=FA[u])
		{
			COVER[u][K-i].insert(o);
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
			for(int j=0;j<=K;j++)COVER[i][j].clear();
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
