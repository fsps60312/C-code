#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int n,out[100];
vector<int> side[100];
double A[101][101];
double absf(double a)
{
    return a>=0?a:-a;
}
void solve()
{
    int Max;
    for(int i=0;i<n;i++)
    {
        Max=i;
        for(int j=i+1;j<n;j++)
        {
            if(absf(A[j][i])>absf(A[Max][i])) Max=j;
        }
        if(absf(A[Max][i])<1e-8) continue;//give up this line
        if(Max!=i)//move max line to line i
        {
            double c;
            for(int j=0;j<=n;j++)
            {
                c=A[Max][j];
                A[Max][j]=A[i][j];
                A[i][j]=c;
            }
        }
        for(int k=0;k<n;k++)
        {
            if(k!=i)
            {
                for(int j=n;j>=i;j--)//(i,j)*=(k,i)/(i,i)
                {
                    A[k][j]-=A[k][i]/A[i][i]*A[i][j];
                }
            }
        }
    }
}
int main()
{
	int T=1;
	freopen("in.txt","r",stdin);
    while(scanf("%d",&n)==1)
    {
        if(n==0) break;
        for(int i=0;i<n;i++)
        {
            out[i]=0;
            side[i].clear();
        }
        int a,b;
        while(scanf("%d%d",&a,&b)==2)//a->b
        {
        	if(a==0) break;
        	a--,b--;
            out[a]++;
            side[b].push_back(a);//b ins contain a: 1/out[a]
        }
        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=n;j++)
            {
                A[i][j]=0;
            }
        }
        for(int i=0;i<n;i++)
        {
            A[i][i]=1;
            for(int j=0;j<side[i].size();j++)//foreach k connect to i
            {
            	int k=side[i][j];
                A[i][k]-=1.0/out[k];
            }
            if(i==0) A[i][n]=1;
        }
        solve();
        bool inf[n];
        for(int i=0;i<n;i++) inf[i]=false;
        for(int i=n-1;i>=0;i--)
        {
        	if(absf(A[i][i]<1e-8)&&absf(A[i][n])>1e-8) inf[i]=true;
        	for(int j=i+1;j<n;j++)
        	{
        		if(absf(A[i][j])>1e-8&&inf[j]) inf[i]=true;
			}
		}
		int q,u;
		scanf("%d",&q);
		printf("Case #%d:\n",T++);
		while(q--)
		{
			scanf("%d",&u);
			u--;
			if(inf[u]) printf("infinity\n");
			else if(A[u][u]<1e-8) printf("0.000\n");
			else printf("%.3lf\n",A[u][n]/A[u][u]);//(u,u)x=(u,n)
		}
    }
    return 0;
}
