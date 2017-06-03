#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,K,GRID[4001][4001];
int COST[4001][4001];
void Build_COST()
{
	static int sum[4001][4001];//sum[i][j]=GRID[1][j]+GRID[2][j]+...+GRID[i][j]
	for(int i=1;i<=N;i++)assert(GRID[i][i]==0);
	for(int j=1;j<=N;j++)for(int i=1;i<=j;i++)sum[i][j]=sum[i-1][j]+GRID[i][j];
	for(int i=1;i<=N;i++)
	{
		COST[i][i]=0;
		for(int j=i+1;j<=N;j++)
		{
			COST[i][j]=COST[i][j-1]+(sum[j][j]-sum[i-1][j]);
		}
	}
}
int GetBestPeople(const int *pre,const int sum,const int min_people,const int max_people)
{
	assert(min_people<=max_people);
//	printf("sum=%d,min_people=%d,max_people=%d\n",sum,min_people,max_people);
	int mn=INF,ans=-1;
	for(int people=min_people;people<=max_people;people++)
	{
		if(people>=sum)continue;
		if(pre[sum-people]+COST[sum-people+1][sum]<mn)mn=pre[sum-people]+COST[sum-people+1][sum],ans=people;
	}
	assert(ans!=-1);
	return ans;
}
void Query(const int *pre,int *ans,const int left_sum,const int right_sum,const int min_people,const int max_people)
{
	if(left_sum>right_sum)return;
	const int mid_sum=(left_sum+right_sum)/2;
	const int best_people=GetBestPeople(pre,mid_sum,min_people,max_people);
	ans[mid_sum]=pre[mid_sum-best_people]+COST[mid_sum-best_people+1][mid_sum];
	Query(pre,ans,left_sum,mid_sum-1,min_people,best_people);
	Query(pre,ans,mid_sum+1,right_sum,best_people,max_people);
}
int DP[801][4001];//DP[i][j]=i cars contain j people
int Solve()
{
	if(K>=N)return 0;//one people one car
	for(int i=1;i<=N;i++)DP[1][i]=COST[1][i];
	for(int cars=2;cars<=K;cars++)
	{
		Query(DP[cars-1],DP[cars],cars,N,1,N-cars);
		assert(DP[cars][cars]==0);
	}
	return DP[K][N];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)scanf("%d",&GRID[i][j]);
		Build_COST();
		printf("%d\n",Solve());
	}
	return 0;
}
