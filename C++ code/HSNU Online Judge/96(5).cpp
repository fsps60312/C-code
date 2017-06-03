#include<cstdio>
#include<queue>
#include<cassert>
#include<set>
using namespace std;
int N,M,DT[40000],DF[40000];
vector<int>ET[40000];
void Bfs(const int s,int *dist)
{
	static bool vis[40000];
	for(int i=0;i<N;i++)dist[i]=4,vis[i]=false;
	queue<int>q;
	vis[s]=true;
	dist[s]=0;
	q.push(s);
	for(int d=1;d<=3;d++)
	{
		for(int cnt=q.size();cnt>=1;cnt--)
		{
			int u=q.front();q.pop();
			for(int i=0;i<ET[u].size();i++)
			{
				const int nxt=ET[u][i];
				if(vis[nxt])continue;
				vis[nxt]=true;
				dist[nxt]=d;
				q.push(nxt);
			}
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b);
		a--,b--;
		assert(a>=0&&a<N&&b>=0&&b<N);
		ET[a].push_back(b),ET[b].push_back(a);
	}
	Bfs(0,DT),Bfs(1,DF);
	for(int i=0;i<N;i++)printf("%d:DT=%d,DF=%d\n",i,DT[i],DF[i]);
	static bool vis[40000];
	int ans=0;
	for(int i=0;i<N;i++)vis[i]=false;
	for(int d=0;d<=4;d++)
	{
		int cnt=0,pre=0;
		for(int i=0;i<N;i++)
		{
			if(DT[i]>=d&&DF[i]>=4-d)
			{
				cnt++;
				if(vis[i])pre++;
				else vis[i]=true;
			}
		}
		ans+=cnt*(cnt-1)/2;
		ans-=pre*(pre-1)/2;
	}
//	printf("ans=%d\n",ans);
	printf("%d\n",ans-M); 
	return 0;
}
