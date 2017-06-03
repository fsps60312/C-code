#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N;
vector<int>ET[500000];
int PATH[500000];
bool FindPath(const int u,const int parent)
{
	if(u==N-1)return true;
	for(const int nxt:ET[u])if(nxt!=parent&&FindPath(nxt,u)){PATH[u]=nxt;return true;}
	return false;
}
bool GO[500000],BACK[500000],VIS[500000];
void Dfs(const int u,const int parent)
{
	if(VIS[u])return;
	VIS[u]=GO[u]=BACK[u]=true;
	for(const int nxt:ET[u])if(nxt!=parent&&nxt!=PATH[u])
	{
		Dfs(nxt,u);
		if(!GO[nxt]&&!BACK[nxt]){GO[u]=BACK[u]=false;return;}
		else if(!GO[nxt])BACK[u]=false;
		else if(!BACK[nxt])GO[u]=false;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)PATH[i]=-1;
		assert(FindPath(0,-1));
		for(int i=0;i<N;i++)VIS[i]=false;
		
	}
	return 0;
}
