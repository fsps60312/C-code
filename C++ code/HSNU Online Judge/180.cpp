#include<cstdio>
#include<vector>
#include<cassert>
#include<queue>
#include<set>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
set<int>ET[50000];
int Dfs(const int u,const int fa,int &mx)
{
	int h1=0,h2=0;
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		const int th=Dfs(nxt,u,mx);
		if(th>=h1)h2=h1,h1=th;
		else if(th>h2)h2=th;
	}
	getmax(mx,h1+h2);
	return h1+1;
}
int N,M,K;
bool BUG[50000];
bool Check(const int u,const int fa,int color)
{
	if(BUG[u]&&color==1)return false;
	for(const int nxt:ET[u])if(nxt!=fa&&!Check(nxt,u,color^1))return false;
	return true;
}
void TrimLeaf()
{
	queue<int>q;
	for(int i=0;i<N;i++)if((int)ET[i].size()==1)q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(BUG[u])continue;
		const int nxt=*ET[u].begin();
		ET[u].erase(nxt),ET[nxt].erase(u);
		if((int)ET[nxt].size()==1)q.push(nxt);
	}
}
int Solve()
{
	scanf("%d",&K);
	if(!K)return 0;
	int root=-1;
	for(int i=0;i<K;i++)scanf("%d",&root),BUG[--root]=true;
	TrimLeaf();
	if(!Check(root,-1,0))return -1;
	int ans=-1;
	Dfs(root,-1,ans);
	assert(ans%2==0);
	return ans/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M),assert(N-1==M);
	for(int i=0;i<N;i++)ET[i].clear(),BUG[i]=false;
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].insert(b),ET[b].insert(a);
	}
	const int ans=Solve();
	if(ans==-1)puts("NIE");
	else printf("%d\n",ans);
	return 0;
}
