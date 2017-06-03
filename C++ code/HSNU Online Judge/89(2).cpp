#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
int N,X,Y,K;
vector<int>DP[10][910];
struct Edge
{
	int u,c;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),c(_c){}
};
vector<Edge>ET[10];
bool INQ[9100];
bool Better(const vector<int>&a,const vector<int>&b)
{
	if(a.size()<b.size())return true;
	assert(a.size()==b.size());
	for(int i=a.size()-1;i>=0;i--)if(a[i]!=b[i])return b[i]<a[i];
	return false;
}
int main()
{
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	assert(N>0);
	for(int i=0;i<10;i++)for(int j=0;j<=(N+1)*9;j++)DP[i][j].clear(),INQ[j*10+i]=false;
	for(int i=0;i<10;i++)//initial number
	{
		ET[i].clear();
		for(int n=0,v;n<10;n++)//add n*k
		{
			v=i+n*K;
			ET[i].push_back(Edge(v/10,v/10+v%10-i));
		}
	}
	queue<int>q;
	q.push(0);INQ[0]=true;
	for(int digitloc=1;digitloc<=N;digitloc++)
	{
		for(int cnt=q.size();cnt>0;cnt--)
		{
			const int u=q.front();q.pop();
			INQ[u]=false;
			const int cost=u/10;
			vector<int>&now=DP[u%10][cost];
			for(int i=0;i<ET[u%10].size();i++)
			{
				now.push_back(i);
				const Edge &e=ET[u%10][i];
				const int nxt=(cost+e.c)*10+e.u;
				vector<int>&dest=DP[e.u][cost+e.c];
				if(Better(dest,now))
				{
					dest=now;
					if(!INQ[nxt])
					{
						q.push(nxt);
						INQ[nxt]=true;
					}
				}
				now.pop_back();
			}
		}
	}
	vector<int>ans;
	for(int i=1;i<10;i++)
	{
		for(int j=0;j<=(N+1)*9;j++)if(Better(ans,DP[i][j]))ans=DP[i][j];
	}
	if(ans.size()!=N)puts("-1");
	else
	{
		for(int i=N-1;i>=0;i--)printf("%d",ans[i]);
		puts("");
	}
	return 0;
}
