#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const int INF=2147483647;
const double EPS=1e-9;
int N,T,BOARD[50];
double DP[41][50],LOSE[41][50];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	static int casenumber;
	for(scanf("%d",&casenumber);casenumber--;)
	{
		scanf("%d%d",&N,&T);
		for(int i=0;i<N;i++)
		{
			static char elem[10];scanf("%s",elem);//element
			if(elem[0]=='L')BOARD[i]=INF;
			else assert(sscanf(elem,"%d",&BOARD[i])==1);
		}
		for(int i=0;i<N;i++)DP[1][i]=LOSE[1][i]=0.0;
		if(BOARD[0]==INF)LOSE[1][0]+=0.5;
		else DP[1][0+BOARD[0]]+=0.5;
		if(1<N)
		{
			if(BOARD[1]==INF)LOSE[1][1]+=0.5;
			else DP[1][1+BOARD[1]]+=0.5;
		}
		for(int d=1;d<T;d++)
		{
//			for(int i=0;i<N;i++)printf(" %.3f",DP[d][i]);puts("");
			for(int i=0;i<N;i++)DP[d+1][i]=LOSE[d+1][i]=0.0;
			for(int i=0;i<N;i++)
			{
				DP[d+1][i]+=LOSE[d][i];
				if(i+1<N)
				{
					if(BOARD[i+1]==INF)LOSE[d+1][i+1]+=0.5*DP[d][i];
					else DP[d+1][i+1+BOARD[i+1]]+=0.5*DP[d][i];
				}
				if(i+2<N)
				{
					if(BOARD[i+2]==INF)LOSE[d+1][i+2]+=0.5*DP[d][i];
					else DP[d+1][i+2+BOARD[i+2]]+=0.5*DP[d][i];
				}
			}
		}
//		for(int i=0;i<N;i++)printf(" %.3f",DP[T][i]);puts("");
		double ans=0.0;
		for(int i=0;i<N;i++)ans+=DP[T][i]+LOSE[T][i];
		ans=1.0-ans;
		if(fabs(ans-0.5)<EPS)printf("Push");
		else if(ans<0.5)printf("Bet against");
		else printf("Bet for");
		printf(". %.4f\n",ans);
	}
	return 0;
}
