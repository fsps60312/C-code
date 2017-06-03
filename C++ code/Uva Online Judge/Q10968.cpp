#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
int N,M,DEG[1000];
vector<int>TO[1000];
inline int solve()
{
	int s=-1,t=-1,cnt=0;
	for(int i=0;i<N;i++)
	{
		if(DEG[i]&1)
		{
			cnt++;
			if(s==-1)s=i;
			else if(t==-1)t=i;
		}
		else if(!DEG[i])return -1;
	}
	assert(cnt==2||cnt==0);
	if(!cnt)return 0;
	if(DEG[s]==1||DEG[t]==1)return -1;
	queue<int>q;
	q.push(s);q.push(0);
	static int VIS[1000];
	for(int i=0;i<N;i++)VIS[i]=DEG[i]==2?1:0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		int l=q.front();q.pop();
		if(VIS[u]++)continue;
		if(u==t)return l;
		for(int i=0;i<TO[u].size();i++)
		{
			int &j=TO[u][i];
			q.push(j);q.push(l+1);
		}
	}
	return -1;
}
int main()
{
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			DEG[i]=0;
		}
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			TO[a].push_back(b);
			TO[b].push_back(a);
			DEG[a]++,DEG[b]++;
		}
		int ans=solve();
		if(ans==-1)printf("Poor Koorosh\n");
		else printf("%d\n",ans);
	}
	return 0;
}
