#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
vector<int> PATH[101];
int N,SP;
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=1;i<=N;i++)PATH[i].clear();
		scanf("%d",&SP);
		int a,b;
		while(scanf("%d%d",&a,&b)==2&&(a||b))PATH[a].push_back(b);
		queue<int> q;
		q.push(SP),q.push(0);
		int ans,p,ep;
		while(!q.empty())
		{
			p=q.front();q.pop();
			if(q.front()>ans)ep=p;
			ans=q.front();q.pop();
			for(int i=0;i<PATH[p].size();i++)
			{
				if(PATH[p][i]==SP)continue;
				q.push(PATH[p][i]),q.push(ans+1);
			}
			//printf("%d %d\n",p,ans);
		}
		printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n",kase++,SP,ans,ep);
	}
	return 0;
}
