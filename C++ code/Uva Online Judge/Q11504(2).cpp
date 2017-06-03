#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cassert>
using namespace std;
int T,N,M;
bool VIS[100000];
vector<int>TO[100000],FROM[100000];
void PushBack(int u)
{
	for(int i=0;i<FROM[u].size();i++)
	{
		int &j=FROM[u][i];
		if(VIS[j])continue;
		VIS[j]=true;
		u=j,i=-1;
		continue;
	}
}
void PushDomino(int s)
{
	PushBack(s);
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(VIS[u])continue;
		VIS[u]=true;
		for(int i=0;i<TO[u].size();i++)
		{
			int &j=TO[u][i];
			q.push(j);
		}
	}
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
			VIS[i]=false;
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
