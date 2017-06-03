#include<cstdio>
#include<vector>
using namespace std;
int N,MAT[101][101],PRE[101][101];
int G[100];
vector<int> Gn[2];
struct Point
{
	vector<int> x;
	vector<int> y;
};
vector<Point> P;
bool dfs_group(int i,int g)
{
	if(G[i]==-1)
	{
		G[i]=g;
		Gn[g].push_back(i); 
	}
	else return G[i]==g;
	for(int j=0;j<N;j++)
	{
		if(MAT[i][j])continue;
		if(!dfs_group(j,g^1))return false;
	}
	return true;
}
bool find_solution()
{
	P.clear();
	for(int i=0;i<N;i++)
	{
		if(G[i]!=-1)continue;
		Gn[0].clear(),Gn[1].clear();
		if(!dfs_group(i,0))return false;
		P.push_back((Point){Gn[0],Gn[1]});
	}
	return true;
}
int abs(int a){return a>=0?a:-a;}
void dfs_ans(int pn,int i)
{
	if(pn==0)return;
	int &pre=PRE[pn][i];
	if(pre==0)
	{
		for(int j=0;j<P[pn-1].x.size();j++)Gn[0].push_back(P[pn-1].x[j]);
		for(int j=0;j<P[pn-1].y.size();j++)Gn[1].push_back(P[pn-1].y[j]);
		dfs_ans(pn-1,i-P[pn-1].x.size());
	}
	else
	{
		for(int j=0;j<P[pn-1].y.size();j++)Gn[0].push_back(P[pn-1].y[j]);
		for(int j=0;j<P[pn-1].x.size();j++)Gn[1].push_back(P[pn-1].x[j]);
		dfs_ans(pn-1,i-P[pn-1].y.size());
	}
}
int T;
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=0;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			G[i]=-1;
			for(int j=0;j<N;j++)
			{
				MAT[i][j]=false;
			}
			MAT[i][i]=true;
		}
		for(int i=0;i<N;i++)
		{
			int a;
			while(scanf("%d",&a)==1&&a)
			{
//				printf(" %d",a);
				a--;
				MAT[i][a]=true;
			}
//			printf("\n");
		}
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(MAT[i][j])continue;
				MAT[j][i]=false;
			}
		}
//		for(int i=0;i<N;i++)
//		{
//			for(int j=0;j<N;j++)
//			{
//				printf("%d",MAT[i][j]);
//			}puts("");
//		}
		if(kase++)printf("\n");
		if(!find_solution())printf("No solution\n");
		else
		{
			for(int i=0;i<=P.size();i++)
			{
				for(int j=0;j<=N;j++)
				{
					MAT[i][j]=0;
				}
			}
			MAT[0][0]=1;
			for(int i=0;i<P.size();i++)
			{
				for(int j=0;j<=N;j++)
				{
					if(!MAT[i][j])continue;
					MAT[i+1][j+P[i].x.size()]++;
					PRE[i+1][j+P[i].x.size()]=0;
					MAT[i+1][j+P[i].y.size()]++;
					PRE[i+1][j+P[i].y.size()]=1;
				}
			}
			int ans=-1,now=N+1;
			for(int i=0;i<=N;i++)
			{
				if(!MAT[P.size()][i])continue;
				if(abs(N-i-i)<now)
				{
					ans=i;
					now=abs(N-i-i);
				}
			}
			if(now==N)printf("No solution\n");
			else
			{
				Gn[0].clear(),Gn[1].clear();
				dfs_ans(P.size(),ans);
				printf("%d",Gn[0].size());
				for(int i=0;i<Gn[0].size();i++)printf(" %d",Gn[0][i]+1);
				printf("\n%d",Gn[1].size());
				for(int i=0;i<Gn[1].size();i++)printf(" %d",Gn[1][i]+1);
				printf("\n");
			}
		}
	}
	return 0;
}
