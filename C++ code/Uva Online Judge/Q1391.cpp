#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int N,M,ASUM,AGE[100002],VIS[200004],REC[100000],RV;
vector<int> SIDE[200004];
bool sametask(int a,int b){return (AGE[a]*N<ASUM&&AGE[b]*N<ASUM)||(AGE[a]*N>=ASUM&&AGE[b]*N>=ASUM);}
bool dfs(int u)
{
	if(VIS[u])return true;
	if(VIS[u^1])return false;
	VIS[u]=1;
	REC[RV++]=u;
	for(int i=0;i<SIDE[u].size();i++)
	{
		if(!dfs(SIDE[u][i]))return false;
	}
	return true;
}
bool solve()
{
	for(int i=1;i<=N*2;i+=2)
	{
		if(VIS[i]||VIS[i^1])continue;
		RV=0;
		if(!dfs(i))
		{
			while(RV)VIS[REC[--RV]]=0;
			if(!dfs(i^1))return false;
		}
	}
	return true;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		ASUM=0;
		for(int i=1;i<=N;i++)
		{
			SIDE[i*2].clear(),SIDE[i*2+1].clear();
			VIS[i*2]=VIS[i*2+1]=0;
			scanf("%d",AGE+i);
			ASUM+=AGE[i];
		}
		while(M--)
		{
			int a,b;scanf("%d%d",&a,&b);
			SIDE[a*2].push_back(b*2+1);
			SIDE[b*2].push_back(a*2+1);
			if(sametask(a,b))
			{
				SIDE[a*2+1].push_back(b*2);
				SIDE[b*2+1].push_back(a*2);
			}
		}
		if(solve())
		{
			for(int i=1;i<=N;i++)
			{
				//printf("%d\t",i);
				if(VIS[i*2])printf("C\n");
				else if(AGE[i]*N<ASUM)printf("B\n");
				else printf("A\n");
			}
		}
		else printf("No solution.\n");
	}
	return 0;
}
