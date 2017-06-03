#include<cstdio>
#include<cstdlib>
int main()
{
	while(scanf("%d%d",&n,&m)==2)
	{
		if(n==-1&&m==-1) break;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				S[i][j].garbage=false;
			}
		}
	}
	return 0;
}
