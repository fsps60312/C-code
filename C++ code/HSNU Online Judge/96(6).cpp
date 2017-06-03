#include<cstdio>
#include<queue>
#include<cassert>
#include<set>
using namespace std;
const int INF=2147483647;
int N,M,DT[40000],DF[40000];
vector<int>ET[40000];
bool VIS[40000];
void Bfs(const int s,int *dist)
{
	for(int i=0;i<N;i++)dist[i]=INF,VIS[i]=false;
	queue<int>q;
	VIS[s]=true;
	dist[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			if(VIS[nxt])continue;
			VIS[nxt]=true;
			dist[nxt]=dist[u]+1;
			q.push(nxt);
		}
	}
}
int TCNT[40000],FCNT[40000];
int main()
{
//	freopen("in.txt","r",stdin);
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
	for(int i=0;i<N;i++)TCNT[i]=FCNT[i]=0;
	for(int i=0;i<N;i++)TCNT[DT[i]]++,FCNT[DF[i]]++;
//	for(int i=0;i<N;i++)printf("%d:DT=%d,DF=%d\n",i,DT[i],DF[i]);
	int ans=0;
	for(int d=0;d<=3;d++)
	{
		int tcnt=0,fcnt=0,ta=0;
		for(int i=0;i<=d;i++)
		{
			tcnt+=TCNT[i];
			ta+=TCNT[i]*(TCNT[i]-1)/2;
			if(i)ta+=TCNT[i-1]*TCNT[i];
		}
		for(int i=0;i<=3-d;i++)
		{
			fcnt+=FCNT[i];
			ta+=FCNT[i]*(FCNT[i]-1)/2;
			if(i)ta+=FCNT[i-1]*FCNT[i];
		}
		int mid=N-tcnt-fcnt;
		ta+=mid*(mid-1)/2;
		ta+=TCNT[d]*mid;
		ta+=FCNT[3-d]*mid;
		if(ta>ans)ans=ta;
	}
//	printf("ans=%d\n",ans);
	printf("%d\n",ans-M); 
	return 0;
}
