#include<cstdio>
typedef long long LL;
LL ANS[101][101];
LL DP[1<<10][100];
inline bool CanSpell(int s)
{
	for(int cnt=0;;s>>=1)
	{
		if(s&1)cnt++;
		else
		{
			if(cnt&1)return false;
			cnt=0;
		}
		if(!s)break;
	}
	return true;
}
void Solve(int column)
{
	for(int s=0;s<(1<<column);s++)DP[s][0]=CanSpell(s)?1LL:0LL;
	int all=(1<<column)-1;
	for(int r=1;(r+1)*column<=100;r++)
	{
		DP[0][r]=DP[all][r-1];
		for(int s=1;s<(1<<column);s++)
		{
			DP[s][r]=DP[all^s][r-1];
			for(int t=s;t;)
			{
				t=(t-1)&s;
				if(CanSpell(s^t))DP[s][r]+=DP[all^t][r-1];
			}
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=1;i<=10;i++)
	{
		Solve(i);
		for(int j=1;j*i<=100;j++)
		{
			ANS[i][j]=ANS[j][i]=DP[(1<<i)-1][j-1];
		}
	}
	int N,M;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		printf("%lld\n",ANS[N][M]);
	}
	return 0;
}
