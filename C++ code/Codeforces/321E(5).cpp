#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647,ZERO='0',NINE='9';
int N,K,GRID[4001][4001];
int COST[4001][4001];
inline void GetInt(int &v)
{
	static int c;c=getchar();
	while(c<ZERO||c>NINE)c=getchar();
	v=0;
	while(c>=ZERO&&c<=NINE)v*=10,v+=c-ZERO,c=getchar();
}
void Build_COST()
{
	static int sum[4001][4001];//sum[i][j]=GRID[1][j]+GRID[2][j]+...+GRID[i][j]
	for(int i=1;i<=N;i++)assert(GRID[i][i]==0);
	for(int j=1;j<=N;j++)
	{
		int *tsum=sum[j];
		for(int i=1;i<=j;i++)tsum[i]=tsum[i-1]+GRID[i][j];
	}
	for(int j=1;j<=N;j++)
	{
		COST[j][j]=0;
		int *tsum=sum[j],*cost0=COST[j],*cost1=COST[j-1];
		for(int i=1;i<j;i++)
		{
			cost0[i]=cost1[i]+(tsum[j]-tsum[i-1]);
		}
	}
}
int GetBestPeople(const int *pre,const int sum,const int min_people,const int max_people)
{
	assert(min_people<=max_people);
//	printf("sum=%d,min_people=%d,max_people=%d\n",sum,min_people,max_people);
	int mn=INF,ans=-1;
	int *cost=COST[sum];
	for(int people=min_people;people<=max_people;people++)
	{
		if(pre[people-1]+cost[people]<mn)mn=pre[people-1]+cost[people],ans=people;
	}
	assert(ans!=-1);
	return ans;
}
void Query(const int *pre,int *ans,const int left_sum,const int right_sum,const int min_people,const int max_people)
{
	if(left_sum>right_sum)return;
	const int mid_sum=(left_sum+right_sum)/2;
	const int best_people=GetBestPeople(pre,mid_sum,min_people,max_people);
	ans[mid_sum]=pre[best_people-1]+COST[mid_sum][best_people];
	Query(pre,ans,left_sum,mid_sum-1,min_people,best_people);
	Query(pre,ans,mid_sum+1,right_sum,best_people,max_people);
}
int DP[801][4001];//DP[i][j]=i cars contain j people
int Solve()
{
	if(K>=N)return 0;//one people one car
	for(int i=1;i<=N;i++)DP[1][i]=COST[i][1];
	for(int cars=2;cars<=K;cars++)
	{
		Query(DP[cars-1],DP[cars],cars,N,cars,N);
		assert(DP[cars][cars]==0);
	}
	return DP[K][N];
}
int main()
{
//	freopen("in.txt","r",stdin);
	GetInt(N),GetInt(K);
	for(int i=1;i<=N;i++)
	{
		int *grid=GRID[i];
		for(int j=1;j<=N;j++)GetInt(grid[j]);
	}
	Build_COST();
	printf("%d\n",Solve());
	return 0;
}
