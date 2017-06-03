#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int n;
vector<int> to[100];
int out[100];
double A[100][101];
void solve()
{
	int Max;
	for(int i=0;i<n;i++)
	{
		Max=i;
		for(int j=i+1;j<n;j++)
		{
			if(A[j][i]>A[Max][i]) Max=j;
		}
		if(A[Max][i]<1e-8) continue;
		if(Max!=i)//change line i to max value
		{
			double a;
			for(int j=0;j<=n;j++)
			{
				a=A[i][j];
				A[i][j]=A[Max][j];
				A[Max][j]=a;
			}
		}
		for(int j=0;j<n;j++)
		{
			if(j!=i)
			{
				for(int k=0;k<=n;k++)
				{
					A[j][k]-=A[i][k]*A[j][i]/A[i][i];
				}
			}
		}
	}
}
int main()
{
	int T=1;
	freopen("in.txt","r",stdin);
	while(scanf("%d",&n)==1&&n)
	{
		int a,b;
		for(int i=0;i<n;i++)
		{
			to[i].clear();
			out[i]=0;
		}
		while(scanf("%d%d",&a,&b)==2)
		{
			if(a==0) break;
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
		A[0][n]=1;
		for(int i=0;i<n;i++)
		{
			A[i][i]+=1;
			for(int j=0;j<to[i].size();j++)
			{
				int k=to[i][j];//from i to k
				A[k][i]-=1.0/out[i];
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
		int q;
		scanf("%d",&q);
		bool inf[n];
		for(int i=0;i<n;i++) inf[i]=false;
		for(int i=n-1;i>=0;i--)
		{
			if(A[i][i]<1e-8&&A[i][n]>1e-8) inf[i]=true;
			for(int j=i+1;j<n;j++)
			{
				if(A[i][j]>1e-8&&inf[j]) inf[i]=true;
			}
		}
		printf("Case #%d:\n",T++);
		while(q--)
		{
			scanf("%d",&a);
			a--;
			if(inf[a]) printf("infinity\n");
			else if(A[a][a]<1e-8) printf("0.000\n");
			else printf("%.3lf\n",A[a][n]/A[a][a]);
		}
	}
	return 0;
}
