#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int N,VIS[101];
vector<int> TASK[101];
int solve(int sp)
{
	queue<int> q;
	q.push(sp);
	int ans=-1;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		VIS[u]=sp;
		ans++;
		for(int i=0;i<TASK[u].size();i++)
		{
			int j=TASK[u][i];
			if(VIS[j]!=sp)q.push(j);
		}
	}
	return ans;
}
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=1,j,k;i<=N;i++)
		{
			VIS[i]=0;
			TASK[i].clear();
			scanf("%d",&k);
			while(k--)
			{
				scanf("%d",&j);
				TASK[i].push_back(j);
			}
		}
		int ans=1,now=0;
		for(int i=1;i<=N;i++)
		{
			int j=solve(i);
			printf("%d:%d\n",i,j);
			if(j>now)ans=i,now=j;
		}
		printf("%d\n",ans);
	}
	return 0;
}
