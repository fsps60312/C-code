#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cassert>
using namespace std;
int T,N,M,VIS[100000],IN[100000];
vector<int>TO[100000],FROM[100000];
void PushFront(int s)
{
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(VIS[u]&1)continue;
		VIS[u]|=1;
		for(int i=0;i<TO[u].size();i++)
		{
			int &j=TO[u][i];
			q.push(j);
		}
	}
}
void PushBack(int u)
{
	VIS[u]|=2;
	PushFront(u);
	for(int i=0;i<FROM[u].size();i++)
	{
		int &j=FROM[u][i];
		if(VIS[j]&2)continue;
		VIS[j]|=2;
		PushFront(j);
		u=j,i=-1;
		continue;
	}
}
void PushDomino(int s)
{
	PushBack(s);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
		{
			TO[i].clear(),FROM[i].clear();
			VIS[i]=0;
		}
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			assert(a>=0&&a<N&&b>=0&&b<N);
			TO[a].push_back(b);
			FROM[b].push_back(a);
		}
		int ans=0;
		for(int i=0;i<N;i++)
		{
			if(VIS[i])continue;
			PushDomino(i);
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
