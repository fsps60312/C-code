#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
vector<int>ET[200000];
int N,M;
char ANS[200000];
int Dfs(const int u,const char k)
{
	if(ANS[u]!='N')return 0;
	ANS[u]=k;
	int ans=1;
	for(int i=0;i<(int)ET[u].size();i++)ans+=Dfs(ET[u][i],k=='K'?'S':'K');
	return ans;
}
bool Solve()
{
	for(int i=0;i<N;i++)ANS[i]='N';
	for(int i=0;i<N;i++)if(ANS[i]=='N')
	{
		if(Dfs(i,'K')==1)return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		if(!Solve())puts("NIE");
		else
		{
			puts("TAK");
			for(int i=0;i<N;i++)putchar(ANS[i]),putchar('\n');
		}
	}
	return 0;
}
