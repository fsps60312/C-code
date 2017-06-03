#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
vector<int> next[101];
vector<int> ans;
bool used[101];
int top[101];
int n,m,a,b,use;
void dfs(int a)
{
	if(used[a]) return;
	//printf("%d\n",a);
	ans.push_back(a);
	used[a]=true;
	use++;
	for(int i=0;i<next[a].size();i++)
	{
		int j=next[a][i];
		top[j]--;
		if(top[j]==0) dfs(j);
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d%d",&n,&m)==2)
	{
		if(n==0&&m==0) break;
		for(int i=1;i<=n;i++)
		{
			next[i].clear();
			used[i]=false;
			top[i]=0;
		}
		use=0;
		ans.clear();
		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&a,&b);
			next[a].push_back(b);
			top[b]++;
		}
		while(use<n)
		{
			for(int i=1;i<=n;i++)
			{
				if(!used[i]&&top[i]==0)
				{
					dfs(i);
				}
			}
		}
		printf("%d",ans[0]);
		for(int i=1;i<n;i++) printf(" %d",ans[i]);
		printf("\n");
	}
	return 0;
}
