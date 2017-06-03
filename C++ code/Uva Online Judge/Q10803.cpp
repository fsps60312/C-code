#include<bits/stdc++.h>
using namespace std;
const double EPS=1e-9,INF=1e100;
int T,N,X[100],Y[100];
vector<int>AD[100];
double DIST[100];
bool INQ[100];
inline int Hypot(const int &a,const int &b){return a*a+b*b;}
inline double Dis(const int &a,const int &b){return sqrt(Hypot(X[a]-X[b],Y[a]-Y[b]));}
void Build(const int &s)
{
	for(int i=0;i<N;i++)DIST[i]=INF,INQ[i]=false;
	queue<int>q;
	DIST[s]=0.0;
	q.push(s);
	INQ[s]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<AD[u].size();i++)
		{
			int &to=AD[u][i];
			if(DIST[u]+Dis(u,to)+EPS<DIST[to])
			{
				DIST[to]=DIST[u]+Dis(u,to);
				if(!INQ[to])
				{
					q.push(to);
					INQ[to]=true;
				}
			}
		}
	}
}
int main()
{
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			for(int i=0;i<N;i++)
			{
				AD[i].clear();
				scanf("%d%d",&X[i],&Y[i]);
			}
			for(int a=0;a<N;a++)
			{
				for(int b=a+1;b<N;b++)
				{
					if(Hypot(X[a]-X[b],Y[a]-Y[b])<=100)
					{
						AD[a].push_back(b);
						AD[b].push_back(a);
					}
				}
			}
			double ans=-INF;
			for(int i=0;i<N;i++)
			{
				Build(i);
				for(int j=0;j<N;j++)ans=max(ans,DIST[j]);
			}
			static int kase=1;
			printf("Case #%d:\n",kase++);
			if(ans==INF)puts("Send Kurdy");
			else printf("%.4f\n",ans);
			puts("");
		}
	}
	return 0;
}
