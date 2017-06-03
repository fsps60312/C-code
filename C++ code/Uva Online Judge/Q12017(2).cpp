#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int T,N,VIS[1001];
vector<int> LINK[1001];
int dfsreach(int u)
{
	if(VIS[u])return 0;
	VIS[u]=1;
	int ans=1;
	for(int i=0;i<LINK[u].size();i++)
	{
		ans+=dfsreach(LINK[u][i]);
	}
	return ans;
}
#define sma(x,y) (x)<(y)?(x):(y)
#include<stack>
int BCC[1001],BCCSUM[1001],BCC_CNT,PRE[1001],PRE_CNT,LOW[1001];
stack<int> STA;
void findBCC(int u)
{
	LOW[u]=PRE[u]=++PRE_CNT;
	STA.push(u);
	for(int i=0;i<LINK[u].size();i++)
	{
		int tu=LINK[u][i];
		if(!PRE[tu])
		{
			findBCC(tu);
			LOW[u]=sma(LOW[u],LOW[tu]);
		}
		else if(!BCC[tu])LOW[u]=sma(LOW[u],PRE[tu]);
	}
	if(LOW[u]==PRE[u])
	{
		BCC_CNT++;
		for(;;)
		{
			int s=STA.top();STA.pop();
			BCC[s]=BCC_CNT;
			BCCSUM[BCC_CNT]++;
			if(s==u)break;
		}
	}
}
vector<int> BCCLINK[1001];
int BCCMAT[1001][1001];
void dfsreachbcc(int sp,int u)
{
	if(VIS[u])return;
	VIS[u]=1;
	if(sp!=u)BCCMAT[sp][u]=1;
	for(int i=0;i<BCCLINK[u].size();i++)dfsreachbcc(sp,BCCLINK[u][i]);
}
int main()
{
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		int m;scanf("%d%d",&N,&m);
		for(int i=1;i<=N;i++)
		{
			LINK[i].clear();
		}
		while(m--)
		{
			int a,b;scanf("%d%d",&a,&b);
			LINK[a].push_back(b);
		}
		int lans=0;
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=N;j++)VIS[j]=0;
			lans+=dfsreach(i);
			PRE[i]=BCC[i]=BCCSUM[i]=0;
		}
		BCC_CNT=PRE_CNT=0;
		for(int i=1;i<=N;i++)
		{
			if(!PRE[i])findBCC(i);
		}
		for(int i=1;i<=BCC_CNT;i++)
		{
			BCCLINK[i].clear();
			for(int j=1;j<=BCC_CNT;j++)
			{
				BCCMAT[i][j]=0;
			}
		}
		for(int i=1;i<=N;i++)
		{
			for(int ti=0;ti<LINK[i].size();ti++)
			{
				int j=LINK[i][ti];
				int &a=BCC[i],&b=BCC[j];
				if(a!=b&&!BCCMAT[a][b])
				{
					BCCLINK[a].push_back(b);
					BCCMAT[a][b]=1;
				}
			}
		}
		for(int i=1;i<=BCC_CNT;i++)
		{
			for(int j=1;j<=BCC_CNT;j++)VIS[j]=0;
			dfsreachbcc(i,i);
		}
		int sans=0;
		for(int i=1;i<=BCC_CNT;i++)
		{
			if(BCCSUM[i]!=1)sans+=BCCSUM[i];
			for(int ti=0;ti<BCCLINK[i].size();ti++)
			{
				int u=BCCLINK[i][ti];
				for(int k=1;k<=BCC_CNT;k++)
				{
					if(BCCMAT[i][k]&&BCCMAT[k][u])
					{
						sans--;
						break;
					}
				}
				sans++;
			}
		}
		printf("Case #%d: %d %d\n",kase++,sans,lans-N);
	}
	return 0;
}
