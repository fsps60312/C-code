#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
vector<int> to[100];
int n,out[100];
double A[100][101];
bool inf[100];
bool zero(double a)
{
	if(a<0) a*=-1;
	return a<1e-8;
}
bool larger(double a,double b)
{
	if(a<0) a*=-1;
	if(b<0) b*=-1;
	return a>b;
}
void solve()
{
	int Max;
	for(int i=0;i<n;i++)
	{
		Max=i;
		for(int j=i+1;j<n;j++)
		{
			if(larger(A[j][i],A[Max][i])) Max=j;
		}
		if(zero(A[Max][i])) continue;
		if(Max!=i)
		{
			double k;
			for(int j=0;j<=n;j++)
			{
				k=A[Max][j];
				A[Max][j]=A[i][j];
				A[i][j]=k;
			}
		}
		for(int j=0;j<n;j++)
		{
			if(j!=i)
			{
				double l=A[j][i]/A[i][i];
				for(int k=n;k>=i;k--)
				{
					A[j][k]-=A[i][k]*l;
				}
			}
		}
		/*printf("  %d\n",i);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<=n;j++)
			{
				printf(" %.3lf",A[i][j]);
			}
			printf("\n");
		}*/
	}
}
int main()
{
	int T=1;
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&n)==1&&n)
	{
		int a,b;
		for(int i=0;i<n;i++)
		{
			out[i]=0;
			to[i].clear();
		}
		while(scanf("%d%d",&a,&b)==2&&a)
		{
			a--,b--;
			to[a].push_back(b);
			out[a]++;
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<=n;j++)
			{
				A[i][j]=0;
			}
		}
		A[0][n]=1;//initial state
		for(int i=0;i<n;i++)
		{
			A[i][i]=+1;
			for(int j=0;j<to[i].size();j++)
			{
				int k=to[i][j];
				A[k][i]-=1.0/out[i];//from i to k
			}
		}
		/*for(int i=0;i<n;i++)
		{
			for(int j=0;j<=n;j++)
			{
				printf(" %.3lf",A[i][j]);
			}
			printf("\n");
		}*/
		solve();
		/*for(int i=0;i<n;i++)
		{
			for(int j=0;j<=n;j++)
			{
				printf(" %.3lf",A[i][j]);
			}
			printf("\n");
		}*/
		//for(int i=0;i<n;i++) inf[i]=false;
		for(int i=n-1;i>=0;i--)
		{
			inf[i]=false;
			if(zero(A[i][i])&&!zero(A[i][n])) inf[i]=true;
			for(int j=i+1;j<n;j++)
			{
				if(!zero(A[i][j])&&inf[j]) inf[i]=true;
			}
		}
		scanf("%d",&a);
		printf("Case #%d:\n",T++);
		while(a--)
		{
			scanf("%d",&b);
			b--;
			if(inf[b]) printf("infinity\n");
			else if(zero(A[b][b])) printf("0.000\n");
			else printf("%.3lf\n",A[b][n]/A[b][b]);
		}
	}
}
