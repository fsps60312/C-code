#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int P,M,S[4][4][4];
int NOW[4][4],USED[4][4],VIS[100];
void Tag(const int &v,const int &d)
{
	for(int i=0;i<P;i++)for(int j=0;j<M;j++)
	{
		if(NOW[i][j]==v)USED[i][j]+=d;
		for(int k=0;k<M;k++)
		{
			if(S[i][j][k]==v)LINE[i][0][j]+=d,LINE[i][1][k]+=d;
		}
	}
}
bool Legal(const int &idx)
{
	bool fulled=false;
	for(int i=P-1;i>=idx;i--)
	{
		bool win=false;
		for(int k=0;k<2;k++)for(int j=0;j<M;j++)if(LINE[i][k][j]==3){win=true;break;}
		if(!fulled&&win)return false;
		if(win)fulled=true;
	}
	return true;
}
bool Permutate(const int &idx)
{
	bool found=false;
	for(int i=0;i<M;i++)
	{
		if(!USED[idx][i])
		{
			found=true;
			Tag(NOW[idx][i],1);
			if(Legal(idx)&&Permutate(idx))return true;
			Tag(NOW[idx][i],-1);
		}
	}
	if(!found)return true;
	return false;
}
bool Dfs(int dep)
{
	if(dep==P)return true;
	if(!Permutate(dep))return false;
	return Dfs(dep+1);
}
int Solve()
{
	static int kase=0;kase++;
	int ans=0;
	for(int i=0;i<P;i++)for(int j=0;j<M;j++)
	{
		USED[i][j]=0;
		if(VIS[NOW[i][j]]!=kase)VIS[NOW[i][j]]=kase,ans++;
	}
	return Dfs(0)?ans:INF;
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<100;i++)VIS[i]=0;
	while(scanf("%d%d",&P,&M)==2&&P&&M)
	{
		for(int i=0;i<P;i++)
		{
			for(int r=0;r<M;r++)
			{
				for(int c=0;c<M;c++)
				{
					scanf("%d",&S[i][r][c]);
				}
			}
		}
		int limit=1;
		for(int i=0;i<P;i++)limit*=M*2+2;
		int ans=INF;
		for(int s=0;s<limit;s++)
		{
			for(int i=0,t=s;i<P;i++,t/=M*2+2)
			{
				int v=t%(M*2+2);
				for(int j=0;j<M;j++)
				{
					if(v<M)NOW[i][j]=S[i][v][j];
					else if(v<M*2)NOW[i][j]=S[i][j][v-M];
					else if(v==M*2)NOW[i][j]=S[i][j][j];
					else NOW[i][j]=S[i][j][M-1-j];
				}
			}
			int ta=Solve();
//			if(ta!=INF)
//			{
//				for(int i=0;i<P;i++)for(int j=0;j<M;j++)printf(" %d",NOW[i][j]);puts("");
//			}
			ans=min(ans,ta);
		}
		printf("%d\n",ans==INF?0:ans);
	}
	return 0;
}
