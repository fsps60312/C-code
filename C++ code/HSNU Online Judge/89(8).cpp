#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,X,Y,K;
vector<char>DP[2][10][901][910];
vector<int>V[2];
struct Edge
{
	int u,c;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),c(_c){}
};
vector<Edge>ET[10];
bool Better(const vector<char>&a,const vector<char>&b)
{
	if(a.empty())return true;
	for(int i=a.size()-1;i>=0;i--)if(a[i]!=b[i])return b[i]<a[i];
	return false;
}
int main()
{
//	N=2,X=9,Y=9,K=5;
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	for(int i=0;i<10;i++)for(int j=0;j<=X;j++)for(int k=0;k<=Y;k++)DP[0][i][j][k].clear(),DP[1][i][j][k].clear();
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
		for(int s=0;s<V[d].size();s++)
		{
			const int u=V[d][s];
			const int cost=u/10%1000;
			const int orig=u/10/1000;
			vector<char>&now=DP[d][u%10][orig][cost];
			for(int i=(digitloc==N?1:0);i<10;i++)
			{
				now.push_back(i);
				const Edge &e=ET[u%10][i];
				if(orig+i>X||orig+i+(N-digitloc)*9<X){now.pop_back();continue;}
				const int nxt=(orig+i)*10*1000+(cost+e.c)*10+e.u;
				vector<char>&dest=DP[d^1][e.u][orig+i][cost+e.c];
				if(Better(dest,now))
				{
					if(dest.empty())V[d^1].push_back(nxt);
					dest=now;
				}
				now.pop_back();
			}
			now.clear();
		}
		V[d].clear();
	}
	vector<char>ans;
	for(int i=0;i<10;i++)
	{
		vector<char>&dp=DP[N&1][i][X][Y];
//		printf("dp[%d]:",i);for(int j=0;j<dp.size();j++)printf(" %d",dp[j]);puts("");
		if(!dp.empty()&&Better(ans,dp)&&dp[dp.size()-1]!=0)ans=dp;
	}
	if(ans.size()!=N)puts("-1");
	else
	{
		for(int i=N-1;i>=0;i--)printf("%c",'0'+ans[i]);
		puts("");
	}
	return 0;
}
