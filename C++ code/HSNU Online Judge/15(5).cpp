#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M,MAT[100][100];
struct Edge
{
	int to,l;
	Edge(){}
	Edge(int to,int l):to(to),l(l){}
};
vector<Edge>AD[100];
void Expand(int s,int &ans)
{
	for(int i=0;i<AD[s].size();i++)
	{
		for(int j=i+1;j<AD[s].size();j++)
		{
			Edge &a=AD[s][i],&b=AD[s][j];
			int &l=MAT[a.to][b.to];
			if(l!=INF)ans=min(ans,a.l+b.l+l);
			l=min(l,a.l+b.l);
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
			for(int j=0;j<N;j++)MAT[i][j]=INF;
		}
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			if(c<MAT[a][b]&&a!=b)MAT[a][b]=MAT[b][a]=c;
		}
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(MAT[i][j]!=INF)AD[i].push_back(Edge(j,MAT[i][j]));
		int ans=INF;
		for(int i=0;i<N;i++)
		{
			Expand(i,ans);
		}
		if(ans==INF)puts("No solution.");
		else printf("%d\n",ans);
	}
	return 0;
}
