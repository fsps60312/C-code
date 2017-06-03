#include<cstdio>
#include<vector>
using namespace std;
int N;
vector<int>ET[100000],LEAF;
void Dfs(const int u,const int fa)
{
	if(ET[u].size()==1)LEAF.push_back(u);
	for(const auto nxt:ET[u])if(nxt!=fa)Dfs(nxt,u);
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1,a,b;i<N;i++)scanf("%d%d",&a,&b),ET[--a].push_back(--b),ET[b].push_back(a);
		LEAF.clear(),Dfs(0,-1);
		const int leaf=LEAF.size();
		printf("%d\n",(leaf+1)/2);
		for(int i=0;i<(leaf+1)/2;i++)printf("%d %d\n",LEAF[i]+1,LEAF[(i+leaf/2)%leaf]+1);
	}
	return 0;
}
