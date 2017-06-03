#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
int N,M,IN[100000];
vector<int>ET[100000];
bool VIS[100000];
void Dfs(const int u)
{
	if(VIS[u])return;
	VIS[u]=true;
	for(const int nxt:ET[u])Dfs(nxt);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)IN[i]=0,ET[i].clear(),VIS[i]=false;
		for(int a,b,i=0;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b);
			IN[b]++;
		}
		int ans=0;
		queue<int>q;
		for(int i=0;i<N;i++)if(IN[i]==0)q.push(i),ans++;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			VIS[u]=true;
			for(const int nxt:ET[u])
			{
				if(!--IN[nxt])q.push(nxt);
			}
		}
		for(int i=0;i<N;i++)if(!VIS[i])Dfs(i),ans++;
		printf("%d\n",ans);
	}
	return 0;
}
