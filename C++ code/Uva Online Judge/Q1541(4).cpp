#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,T,BOARD[52];
double DP[51][40];
double GetDP(const int loc,const int cnt)
{
	if(cnt>T)return 0.0;
	if(loc==N+1)return 1.0;
	if(cnt==T)return 0.0;
	double &ans=DP[loc][cnt];
	if(ans!=-1.0)return ans;
	ans=0.0;
	for(int move=1;move<=2;move++)
	{
		const int nxt=min(N+1,loc+move);
		if(BOARD[nxt]==INF)ans+=0.5*GetDP(nxt,cnt+2);
		else ans+=0.5*GetDP(nxt+BOARD[nxt],cnt+1);
	}
	return ans;
}
int main()
{
	int casenum;scanf("%d",&casenum);
	while(casenum--)
	{
		scanf("%d%d",&N,&T);
		for(int i=1;i<=N;i++)
		{
			static char elem[10];
			scanf("%s",elem);
			if(elem[0]=='L')BOARD[i]=INF;
			else sscanf(elem,"%d",&BOARD[i]);
		}
		BOARD[0]=BOARD[N+1]=0;
		for(int i=0;i<=N;i++)for(int j=0;j<T;j++)DP[i][j]=-1.0;
		double ans=GetDP(0,0);
		if(fabs(ans-0.5)<1e-9)puts("Push. 0.5000");
		else if(ans<0.5)printf("Bet against. %.4f\n",ans);
		else printf("Bet for. %.4f\n",ans);
	}
	return 0;
}
