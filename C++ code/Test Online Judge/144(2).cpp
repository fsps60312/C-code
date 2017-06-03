#include<cstdio>
const int INF=2147483647;
bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
int T,N,SUM[1001],S[1001],DP[1001][1001],REC[1001][1001];
inline int Sum(const int l,const int r){return SUM[r]-SUM[l-1];}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),DP[i][i]=0,SUM[i]=SUM[i-1]+S[i],REC[i][i]=i;
		for(int gap=1;gap<N;gap++)
		{
			for(int i=1;i+gap<=N;i++)
			{
				DP[i][i+gap]=INF;
				for(int j=REC[i][i+gap-1];j<=REC[i+1][i+gap];j++)if(getmin(DP[i][i+gap],DP[i][j]+DP[j+1][i+gap]))REC[i][i+gap]=j;
				DP[i][i+gap]+=Sum(i,i+gap);
			}
		}
		printf("%d\n",DP[1][N]);
	}
	return 0;
}
