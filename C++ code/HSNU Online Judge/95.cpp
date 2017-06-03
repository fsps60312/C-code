#include<cstdio>
#include<vector>
using namespace std;
int N,M,ANS[200000];
vector<int>ET[200000];
int Dfs(const int u)
{
	int ans=1;
	for(int i=0;i<ET[u].size();i++)
	{
		const int &nxt=ET[u][i];
		if(ANS[nxt]!=-1)continue;
		ANS[nxt]=ANS[u]^1;
		ans+=Dfs(nxt);
	}
	return ans;
}
bool Solve()
{
	for(int i=0;i<N;i++)
	{
		if(ANS[i]!=-1)continue;
		ANS[i]=0;
		if(Dfs(i)==1)return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear(),ANS[i]=-1;
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b);
		a--,b--;
		ET[a].push_back(b);
		ET[b].push_back(a);
	}
	if(!Solve())puts("NIE");
	else
	{
		puts("TAK");
		for(int i=0;i<N;i++)puts(ANS[i]?"K":"S");
	}
	return 0;
}
