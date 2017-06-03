#include<cstdio>
#include<vector>
#include<cassert>
#include<stack>
using namespace std;
vector<int>ET[16000];
int N,M;
bool TAG[16000];
stack<int>STK;
bool Dfs(const int u)
{
	if(TAG[u^1])return false;
	if(TAG[u])return true;
	TAG[u]=true;STK.push(u);
	for(const int nxt:ET[u])if(!Dfs(nxt))return false;
	return true;
}
bool Solve()
{
	for(int i=0;i<N*2;i++)TAG[i]=false;
	for(int i=0;i<N;i++)if(!TAG[i*2]&&!TAG[i*2+1])
	{
		while(!STK.empty())STK.pop();
		if(!Dfs(i*2))
		{
			while(!STK.empty())TAG[STK.top()]=false,STK.pop();
			if(!Dfs(i*2+1))return false;
		}
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N*2;i++)ET[i].clear();
		for(int i=0;i<M;i++)
		{
			static int a,b;scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b^1),ET[b].push_back(a^1);
		}
		if(!Solve())puts("-1");
		else
		{
			int cnt=0;
			for(int i=0;i<N*2;i++)if(TAG[i])printf("%d\n",i+1),cnt++;
			assert(cnt==N);
		}
	}
	return 0;
}
