#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
int N,X,Y,K;
vector<int>DP[2][10][910];
vector<int>V[2];
struct Edge
{
	int u,c;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),c(_c){}
};
vector<Edge>ET[10];
bool Better(const vector<int>&a,const vector<int>&b)
{
	if(a.empty())return true;
	if(a.size()!=b.size())
	{
		printf("a(%d):",a.size());for(int i=0;i<a.size();i++)printf(" %d",a[i]);puts("");
		printf("b(%d):",b.size());for(int i=0;i<b.size();i++)printf(" %d",b[i]);puts("");
	}
	assert(a.size()==b.size());
	for(int i=a.size()-1;i>=0;i--)if(a[i]!=b[i])return b[i]<a[i];
	return false;
}
int main()
{
	N=4,X=9,Y=9,K=5;
//	scanf("%d%d%d%d",&N,&X,&Y,&K);
	assert(N>0);
	for(int i=0;i<10;i++)for(int j=0;j<=(N+1)*9;j++)DP[0][i][j].clear(),DP[1][i][j].clear();
	V[0].clear(),V[1].clear();
	for(int i=0;i<10;i++)//initial number
	{
		ET[i].clear();
		for(int n=0,v;n<10;n++)//add n*k
		{
			v=i+n*K;
			ET[i].push_back(Edge(v/10,v/10+v%10-i));
		}
	}
	V[0].push_back(0);
	for(int d=0,digitloc=1;digitloc<=N;digitloc++,d^=1)
	{
sort(V[d].begin(),V[d].end());
assert(unique(V[d].begin(),V[d].end())==V[d].end());
		for(int s=0;s<V[d].size();s++)
		{
			const int u=V[d][s];
			const int cost=u/10;
			vector<int>&now=DP[d][u%10][cost];
			for(int i=0;i<10;i++)
			{
				now.push_back(i);
				const Edge &e=ET[u%10][i];
				const int nxt=(cost+e.c)*10+e.u;
				assert(e.u>=0&&e.u<=9);
				vector<int>&dest=DP[d^1][e.u][cost+e.c];
				if(Better(dest,now))
				{
					if(dest.empty())V[d^1].push_back(nxt);
					dest=now;
					assert(!dest.empty());
				}
				now.pop_back();
			}
			now.clear();
		}
		V[d].clear();
	}
	vector<int>ans;
	for(int i=1;i<10;i++)
	{
		for(int j=0;j<=(N+1)*9;j++)if(Better(ans,DP[N&1][i][j]))ans=DP[N&1][i][j];
	}
	if(ans.size()!=N)puts("-1");
	else
	{
		for(int i=N-1;i>=0;i--)printf("%d",ans[i]);
		puts("");
	}
	return 0;
}
