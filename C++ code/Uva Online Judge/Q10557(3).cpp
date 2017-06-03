#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int N,ENE[101],BEST[101],DIS[101];
vector<int> DOOR[101];
bool solve()
{
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(u==N)return true;
		for(int i=0;i<DOOR[u].size();i++)
		{
			int j=DOOR[u][i];
			if(BEST[j]>=BEST[u]+ENE[j])continue;
			BEST[j]=BEST[u]+ENE[j];
			DIS[j]=DIS[u]+1;
			if(DIS[j]>=N)return true;
			q.push(j);
		}
	}
	return false;
}
int main()
{
    while(scanf("%d",&N)==1&&N!=-1)
    {
        for(int i=1;i<=N;i++)
        {
            scanf("%d",&ENE[i]);
            DOOR[i].clear();
            BEST[i]=DIS[i]=0;
            int j;scanf("%d",&j);
            while(j--)
            {
                int k;scanf("%d",&k);
                DOOR[i].push_back(k);
            }
        }
        BEST[1]=100;
        if(solve())printf("winnable\n");
        else printf("hopeless\n");
    }
    return 0;
}
