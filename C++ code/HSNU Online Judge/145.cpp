#include<cstdio>
#include<vector>
using namespace std;
int N,M,COLOR[50000];
vector<int>ET[50000];
bool Dfs(const int u,const int c)
{
	if(COLOR[u]!=-1)return COLOR[u]==c;
	COLOR[u]=c;
	for(const int nxt:ET[u])if(!Dfs(nxt,c^1))return false;
	return true;
}
bool Solve()
{
	for(int i=0;i<N;i++)COLOR[i]=-1;
	for(int i=0;i<N;i++)if(COLOR[i]==-1)if(!Dfs(i,0))return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	puts(Solve()?"yes":"no");
	return 0;
}
