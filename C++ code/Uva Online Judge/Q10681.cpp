#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int C,SP,EP,DAY;
vector<int> LINK[101];
int REACHABLE[2][101];
int solve()
{
	int *x=REACHABLE[0],*y=REACHABLE[1];
	for(int i=1;i<=C;i++)x[i]=0;
	x[SP]=1;
	for(int k=1;k<=DAY;k++)
	{
		for(int i=1;i<=C;i++)y[i]=0;
		for(int i=1;i<=C;i++)
		{
			if(!x[i])continue;
			for(int ti=0;ti<LINK[i].size();ti++)
			{
				int j=LINK[i][ti];
				y[j]=1;
			}
		}
		int *t=x;x=y,y=t;
	}
	return x[EP];
}
int main()
{
	int L;
	while(scanf("%d%d",&C,&L)==2&&(C||L))
	{
		for(int i=1;i<=C;i++)LINK[i].clear();
		while(L--)
		{
			int a,b;scanf("%d%d",&a,&b);
			LINK[a].push_back(b);
			LINK[b].push_back(a);
		}
		scanf("%d%d%d",&SP,&EP,&DAY);
		if(solve())printf("Yes, Teobaldo can travel.\n");
		else printf("No, Teobaldo can not travel.\n");
	}
	return 0;
}
