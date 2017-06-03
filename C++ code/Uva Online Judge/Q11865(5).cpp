#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<stack>
#define LL long long
using namespace std;
struct Cable
{
	int from,to,bw,cost;
}TCABLE[10000];
bool cmp_Cable(Cable a,Cable b)
{
	return a.cost<b.cost;
}
struct Dmst
{
	Cable CBL[10000];
	int CSZ,USZ,COST[60],PRE[60],LOW[60],PRE_CNT,BCC_CNT,VIS[60],BCCN[60];
	vector<int> BCC[60];
	int CBLED[60][60];
	void init(Cable *c,int length,int limit,int usz,int root)
	{
		ROOT=root;
		CSZ=0;
		USZ=usz;
		for(int i=0;i<usz;i++)
		{
			for(int j=0;j<usz;j++)
			{
				CBLED[i][j]=-1;
			}
		}
		for(int i=0;i<length;i++)
		{
			if(c[i].bw<limit||c[i].to==root)continue;
			int &ced=CBLED[c[i].from][c[i].to];
			if(ced!=-1)
			{
				if(c[i].cost<CBL[ced].cost)CBL[ced]=c[i];
				continue;
			}
			ced=CSZ;
			CBL[CSZ++]=c[i];
		}
	}
	void initvalue(){for(int i=0;i<USZ;i++)COST[i]=0;}
	void setvalue(int *v){for(int i=0;i<USZ;i++)COST[i]=v[i];}
	int DJSET[60];
	int findset(int a){return DJSET[a]==a?a:(DJSET[a]=findset(DJSET[a]));}
	int FROM[60];
	LL getcost()
	{
		LL ans=COST[ROOT];
		for(int i=0;i<USZ;i++)
		{
			if(i==ROOT)continue;
			ans+=COST[i]+CBL[FROM[i]].cost;
		}
		return ans;
	}
	LL buildfrom()
	{
		sort(CBL,CBL+CSZ,cmp_Cable);
		for(int i=0;i<USZ;i++)
		{
			DJSET[i]=i;
			VIS[i]=0;
		}
		int visn=0,gpn=USZ;
		for(int i=0;;i++)
		{
			if(i==CSZ)return -1;
			Cable &c=CBL[i];
			if(VIS[c.to])continue;
			VIS[c.to]=1;
			visn++;
			FROM[c.to]=i;
			int fx=findset(c.from),fy=findset(c.to);
			if(fx!=fy)
			{
				DJSET[fx]=fy;
				gpn--;
			}
			if(visn==USZ-1)
			{
				if(gpn==1)return getcost();
				else
				{
					buildBCC();
					return -2;
				}
			}
		}
	}
	stack<int> STACK;
	void dfs_PRE(int u)
	{
		//printf("enter %d\n",u);
		STACK.push(u);
		PRE[u]=LOW[u]=++PRE_CNT;
		if(u!=ROOT)
		{
			int nxu=CBL[FROM[u]].from;
			if(!PRE[nxu])
			{
				dfs_PRE(nxu);
				LOW[u]=min(LOW[u],LOW[nxu]);
			}
			else if(BCCN[nxu]==-1)
			{
				LOW[u]=min(LOW[u],PRE[nxu]);
			}
		}
		//printf("%d: pre=%d low=%d\n",u,PRE[u],LOW[u]);
		if(LOW[u]==PRE[u])//set BCCN
		{
			while(1)
			{
				int s=STACK.top();STACK.pop();
				BCCN[s]=BCC_CNT;
				//printf("%d is in %d\n",s,BCC_CNT);
				if(s==u)break;
			}
			BCC_CNT++;
		}
	}
	int BCC_COST[60];
	Cable BCC_CABLE[10000];
	int BCC_CSZ,ROOT;
	void buildBCC()
	{
		PRE_CNT=BCC_CNT=0;
		for(int i=0;i<USZ;i++)
		{
			PRE[i]=0;
			BCCN[i]=-1;
			//printf("from[%d]=(%d,%d)\n",i,CBL[FROM[i]].from,CBL[FROM[i]].to);
		}
		for(int i=0;i<USZ;i++)
		{
			if(!PRE[i])
			{
				dfs_PRE(i);
			}
		}
		for(int i=0;i<BCC_CNT;i++)
		{
			BCC[i].clear();
			BCC_COST[i]=0;
		}
		//build BCC group
		ROOT=BCCN[ROOT];
		for(int i=0;i<USZ;i++)
		{
			BCC[BCCN[i]].push_back(i);
			//printf("push %d to %d\n",i,BCCN[i]);
			BCC_COST[BCCN[i]]+=COST[i];
		}
		for(int i=0;i<USZ;i++)
		{
			if(BCC[BCCN[i]].size()>1)
			{
				BCC_COST[BCCN[i]]+=CBL[FROM[i]].cost;
			}
		}
		//add BCC_COST(from CBL in same group)
		//add BCC_CABLE(size is BCC_CSZ)
		BCC_CSZ=0;
		for(int i=0;i<CSZ;i++)
		{
			Cable &c=CBL[i];
			if(BCCN[c.from]==BCCN[c.to])continue;
			else//add BCC_CABLE
			{
				Cable &bc=BCC_CABLE[BCC_CSZ++];
				bc.from=BCCN[c.from];
				bc.to=BCCN[c.to];
				bc.cost=c.cost;
				if(BCC[bc.to].size()>1)bc.cost-=CBL[FROM[c.to]].cost;
				bc.bw=c.bw;
			}
		}
	}
	void show_CBL()
	{
		printf("\tshow_CBL()\n");
		for(int i=0;i<CSZ;i++)
		{
			Cable &c=CBL[i];
			printf("%d->%d bw=%d cost=%d\n",c.from,c.to,c.bw,c.cost);
		}
	}
	void show_BCC()
	{
		printf("\tshow_BCC(ROOT=%d)\n",ROOT);
		for(int i=0;i<BCC_CNT;i++)
		{
			printf("{%d",BCC[i][0]);
			for(int j=1;j<BCC[i].size();j++)printf(",%d",BCC[i][j]);
			printf("}");
			printf("cost=%d\n",BCC_COST[i]);
		}
	}
}DMST[2];
int T,N,M,C;
bool BuildCable(int limit)
{
	DMST[0].init(TCABLE,M,limit,N,0);
	DMST[0].initvalue();
	for(int i=0;;i^=1)
	{
		//DMST[i].show_CBL();
		LL result=DMST[i].buildfrom();
		if(result==-1)return false;
		else if(result!=-2)return result<=C;
		//DMST[i].show_BCC();
		DMST[i^1].init(DMST[i].BCC_CABLE,DMST[i].BCC_CSZ,limit,DMST[i].BCC_CNT,DMST[i].ROOT);
		DMST[i^1].setvalue(DMST[i].BCC_COST);
	}
}
int main()
{
	//freopen("inn.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&M,&C);
		int l=2147483647,r=0;
		for(int i=0;i<M;i++)
		{
			Cable &c=TCABLE[i];
			scanf("%d%d%d%d",&c.from,&c.to,&c.bw,&c.cost);
			if(c.to==0)
			{
				i--,M--;
				continue;
			}
			if(c.bw>r)r=c.bw;
			if(c.bw<l)l=c.bw;
		}
		r++;
		//BuildCable(538733);return 0;
		if(N==1)printf("1061109567 kbps\n");
		else if(!BuildCable(l))printf("streaming not possible.\n");
		else
		{
			while(l<r)
			{
				int m=(l+r)/2;
				if(BuildCable(m))l=m+1;
				else r=m;
			}
			printf("%d kbps\n",r-1);
		}
		//return 0;
	}
	return 0;
}
/*
6 14 1633083
2 0 27309 196807
3 2 367099 173528
4 2 9783 627952
5 3 283895 777804
1 4 802626 113705
0 4 866526 60285
1 2 984286 381398
0 3 755670 423150
2 3 733095 861302
4 1 541831 87240
3 1 661270 396535
2 0 331225 650186
2 5 538733 652324
5 4 617654 52661
*/
//538733
/*
1 4 802626 113705
0 4 866526 60285
1 2 984286 381398
0 3 755670 423150
2 3 733095 861302
4 1 541831 87240
3 1 661270 396535
2 5 538733 652324
5 4 617654 52661
*/
//538733
/*
5 4 617654 52661
1 2 984286 381398
0 3 755670 423150
4 1 541831 87240
2 5 538733 652324
*/
/*
1 4 802626 113705
0 4 866526 60285
2 3 733095 861302
3 1 661270 396535
*/
