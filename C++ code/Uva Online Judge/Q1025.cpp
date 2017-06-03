#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
int N,T,ITV[49],TS[50][50],TE[50][50],M1,M2,T_T[50];
int DP[201][50];//[time][station]=min wait time at stations
void getmin(int &a,int b){if(b<a)a=b;}
int get_lasttrain_S(int t,int s)
{
	int i;
	for(i=M1-1;i>=0;i--)
	{
		if(TS[i][s]<=t)break;
	}
	return i;
}
int get_lasttrain_E(int t,int s)
{
	int i;
	for(i=M2-1;i>=0;i--)
	{
		if(TE[i][s]<=t)break;
	}
	return i;
}
int cal_waittime()
{
	for(int i=0;i<=T;i++)
	{
		for(int j=0;j<N;j++)
		{
			DP[i][j]=2147483647;
		}
	}
	for(int t=0;t<=T;t++)
	{
		getmin(DP[t][0],t);
		for(int s=0;s<N;s++)
		{
			if(s!=0)//train from left
			{
				int i=get_lasttrain_S(t,s);
				if(i!=-1&&DP[TS[i][s-1]][s-1]!=2147483647)getmin(DP[t][s],DP[TS[i][s-1]][s-1]+(t-TS[i][s]));
			}
			if(s!=N-1)//train from right
			{
				int i=get_lasttrain_E(t,s);
				if(i!=-1&&DP[TE[i][s+1]][s+1]!=2147483647)getmin(DP[t][s],DP[TE[i][s+1]][s+1]+(t-TE[i][s]));
			}
		}
	}
	return DP[T][N-1];
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d",&T);
		for(int i=0;i<N-1;i++)scanf("%d",&ITV[i]);
		scanf("%d",&M1);
		for(int i=0;i<M1;i++)scanf("%d",&T_T[i]);
		sort(T_T,T_T+M1);
		for(int i=0;i<M1;i++)
		{
			TS[i][0]=T_T[i];
			for(int s=1;s<N;s++)
			{
				TS[i][s]=TS[i][s-1]+ITV[s-1];
			}
		}
		scanf("%d",&M2);
		for(int i=0;i<M2;i++)scanf("%d",&T_T[i]);
		sort(T_T,T_T+M2);
		for(int i=0;i<M2;i++)
		{
			TE[i][N-1]=T_T[i];
			for(int s=N-2;s>=0;s--)
			{
				TE[i][s]=TE[i][s+1]+ITV[s];
			}
		}
		int ans=cal_waittime();
		printf("Case Number %d: ",kase++);
		if(ans==2147483647)printf("impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
