#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
vector<int> TO[1001];
int T,N,S,K,DEP[1001];
int getmin(int &a,int b){if(b<a)a=b;}
struct Bfs
{
	int u, dep;
	Bfs(int _u,int d):u(_u),dep(d){}
};
int solve()
{
	int ans=-1;
	queue<Bfs> q;
	vector<int> serve;
	int last=S;
	while(DEP[last]>K)
	{
		serve.push_back(last);
		for(int i=1;i<serve.size();i++)q.push(Bfs(serve[i],-K));
		bool pushed=false;
		while(1)
		{
			if(q.empty())
			{
				if(!pushed)
				{
					q.push(Bfs(serve[0],0));
					pushed=true;
				}
				else break;
			}
			Bfs b=q.front();q.pop();
			if(b.dep>=-1&&!pushed)
			{
				q.push(Bfs(serve[0],0));
				pushed=true;
			}
			if(DEP[b.u]<b.dep)continue;
			DEP[b.u]=b.dep;
			for(int i=0;i<TO[b.u].size();i++)
			{
				q.push(Bfs(TO[b.u][i],b.dep+1));
			}
			if(b.dep>DEP[last])last=b.u;
		}
		ans++;
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&S,&K);
		if(K>=N)K=N-1;
		for(int i=1;i<=N;i++)
		{
			TO[i].clear();
			DEP[i]=2147483647;
		}
		for(int i=1;i<N;i++)
		{
			int a,b;scanf("%d%d",&a,&b);
			TO[a].push_back(b);
			TO[b].push_back(a);
		}
		printf("%d\n",solve());
	}
	return 0;
}
