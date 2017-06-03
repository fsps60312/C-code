#include<cstdio>
#include<queue>
using namespace std;
int N,M,DT[40000],DF[40000];
vector<int>ET[40000];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear(),DT[i]=DF[i]=INF;
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b);
		a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	DT[0]=0;
	queue<int>q;q.push(0);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			if(DT[nxt]!=INF)continue;
			DT[nxt]=DT[u]+1;
			q.push(nxt);
		}
	}
	DF[1]=0;
	q.push(1);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			if(DF[nxt]!=INF)continue;
			DF[nxt]=DF[u]+1;
			q.push(nxt);
		}
	}
	return 0;
}
