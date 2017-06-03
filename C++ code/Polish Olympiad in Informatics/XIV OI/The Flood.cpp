#include<cstdio>
#include<cassert>
#include<vector> 
#include<utility>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,M;
int G[1002][1002];
vector<pair<int,int> >LOC[1001];
int VIS[1002][1002],WANT[1002][1002];
bool Dfs(const int r,const int c,const int h)
{
	if(VIS[r][c])return false;
	VIS[r][c]=true;
	static int d[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
	bool ans=WANT[r][c];
	for(int i=0;i<4;i++)
	{
		const int nxtr=r+d[i][0],nxtc=c+d[i][1];
		if(G[nxtr][nxtc]>=h)ans|=Dfs(nxtr,nxtc);
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<=1000;i++)LOC[i].clear();
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
		{
			scanf("%d",&G[i][j]);
			VIS[i][j]=false,WANT[i][j]=(G[i][j]>=1);
			if(G[i][j]<0)G[i][j]*=-1;
			LOC[G[i][j]].push_back(make_pair(i,j));
		}
		for(int i=1;i<=N||i<=M;i++)VIS[0][i]=VIS[N+1][i]=VIS[i][0]=VIS[i][M+1]=true;
		int ans=0;
		for(int h=0;h<=1000;h++)
		{
			for(int i=0;i<(int)LOC[h].size();i++)
			{
				const pair<int,int>&p=LOC[h][i];
//				puts("a");
				if(!VIS[p.first][p.second]&&Dfs(p.first,p.second))++ans;
//				puts("b");
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
