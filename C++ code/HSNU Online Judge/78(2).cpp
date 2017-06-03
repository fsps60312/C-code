#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N,K,KIND[500000],GROUP[500000],SZ[500000];
vector<int>ET[500000],EF[500000],ES[500000];
void Set(const int &u,const int &k,const int &g)
{
	if(GROUP[u]==g)return;
	SZ[GROUP[u]]--,SZ[g]++;
	GROUP[u]=g;
	KIND[u]=k;
	for(int i=0;i<ET[u].size();i++)Set(ET[u][i],(k+1)%3,g);
	for(int i=0;i<EF[u].size();i++)Set(EF[u][i],(k+2)%3,g);
	for(int i=0;i<ES[u].size();i++)Set(ES[u][i],k,g);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),EF[i].clear(),ES[i].clear(),KIND[i]=SZ[i]=0,GROUP[i]=i;
		int ans=0;
		while(K--)
		{
			static int d,x,y;
			scanf("%d%d%d",&d,&x,&y);
			x--,y--;
			if(x>=N||y>=N)ans++;
			else if(d==1)
			{
				if(GROUP[x]==GROUP[y])
				{
					if(KIND[x]!=KIND[y])ans++;
				}
				else
				{
					if(SZ[GROUP[x]]<SZ[GROUP[y]])Set(x,KIND[y],GROUP[y]);
					else Set(y,KIND[x],GROUP[x]);
					ES[x].push_back(y),ES[y].push_back(x);
				}
			}
			else if(d==2)
			{
				if(GROUP[x]==GROUP[y])
				{
					if((KIND[x]+1)%3!=KIND[y])ans++;
				}
				else
				{
					if(SZ[GROUP[x]]<SZ[GROUP[y]])Set(x,(KIND[y]+2)%3,GROUP[y]);
					else Set(y,(KIND[x]+1)%3,GROUP[x]);
					ET[x].push_back(y);
					EF[y].push_back(x);
				}
			}
			else assert(0);
		}
		printf("%d\n",ans);
	}
	return 0;
}
