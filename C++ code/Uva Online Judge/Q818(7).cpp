#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,DEGR[15],DEG[15];
bool V1[15],V2[15],E[15][15];
bool flaw(int u,bool &loop)
{
	if(V2[u])return false;
	V2[u]=true;
	if(DEG[u]!=2)loop=false;
	if(DEG[u]>2)return true;
	for(int i=0;i<N;i++)if(E[u][i])if(flaw(i,loop))return true;
	return false;
}
bool dfs(int u,int &cut,int dep)
{
	V1[u]=true;
	if(dep==cut)
	{
		for(int i=0;i<N;i++)DEG[i]=DEGR[i],V2[i]=V1[i];
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(E[i][j]&&V1[j])DEG[i]--;
			}
			if(V1[i])DEG[i]=0;
		}
		int cnt=0;
		for(int i=0;i<N;i++)
		{
			if(V2[i])continue;
			cnt++;
			bool loop=true;
			if(flaw(i,loop)||loop){V1[u]=false;return false;}
		}
		cnt--;
		V1[u]=false;
		return cnt<=cut;
	}
	for(int i=u+1;i<N;i++)if(dfs(i,cut,dep+1)){V1[u]=false;return true;}
	V1[u]=false;
	return false;
}
int solve()
{
	int cnt=0;
	for(int i=0;i<N;i++)DEG[i]=DEGR[i];
	for(int i=0;i<N;i++)
	{
		if(V2[i])continue;
		cnt++;
		bool loop=true;
		if(flaw(i,loop)||loop){cnt=INF;break;}
	}
	cnt--;
	if(!cnt)return 0;
	for(int cut=1;cut<N;cut++)
	{
		int s=0;
		for(int i=0;i<N;i++)if(dfs(i,cut,1))return cut;
		for(int i=0;i<N;i++)assert(V1[i]==false);
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)E[i][j]=false;
			V1[i]=V2[i]=false;
			DEGR[i]=0;
		}
		for(int a,b;scanf("%d%d",&a,&b)==2&&!(a==-1||b==-1);)
		{
			a--,b--;
			if(E[a][b])continue;
			DEGR[a]++,DEGR[b]++;
			E[a][b]++,E[b][a]++;
		}
		static int kase=1;
		printf("Set %d: Minimum links to open is %d\n",kase++,solve());
	}
	return 0;
}
