#include<cstdio>
#include<cstdlib>
#define min(x,y) (x)<(y)?(x):(y)
int N,M,LIKE[1001][1001],PRE[1001],LOW[1001],ISCUT[1001],BCC[1001],PRE_CNT,BCC_CNT,ISB[1001],COLOR[1001],ANS;
void show()
{for(int i=1;i<=N;i++)printf("LOW=%d\tISCUT=%d\tPRE=%d\tBCC=%d\tISB=%d\n",LOW[i],ISCUT[i],PRE[i],BCC[i],ISB[i]);}
struct Stack
{
	int sz,s[1001][2];
	void clear(){sz=0;}
	void push(int x,int y)
	{
		s[sz][0]=x,s[sz][1]=y;
		sz++;
	}
	void pop(){sz--;}
	int *front(){return s[sz-1];}
}SIDE;
bool dfsbinary(int u,int bccn,int color)
{
	COLOR[u]=color;
	for(int i=1;i<=N;i++)
	{
		if(!LIKE[u][i]||BCC[i]!=bccn)continue;
		if(COLOR[i]==0)
		{
			if(!dfsbinary(i,bccn,3-color))return false;
		}
		else if(COLOR[i]==color)return false;
	}
	return true;
}
void minusans(int u,int bccn)
{
	COLOR[u]=0;
	if(!ISB[u])
	{
		ANS--;
		printf("ANS=%d\n",u);
	}
	ISB[u]++;
	for(int i=1;i<=N;i++)
	{
		if(!COLOR[i]||!LIKE[u][i]||BCC[i]!=bccn)continue;
		minusans(i,bccn);
	}
}
void dfs(int u,int fa)
{
	int lowu=LOW[u]=PRE[u]=++PRE_CNT;
	int child=0;
	for(int i=1;i<=N;i++)
	{
		child++;
		if(!LIKE[u][i])continue;
		if(!PRE[i])
		{
			SIDE.push(u,i);
			child++;
			dfs(i,u);
			if(LOW[i]>=lowu)
			{
				ISCUT[u]=true;
				//BCC[i]=++BCC_CNT;
				BCC_CNT++;
				while(1)
				{
					int *v=SIDE.front();SIDE.pop();
					BCC[v[0]]=BCC[v[1]]=BCC_CNT;
					COLOR[v[0]]=COLOR[v[1]]=0;
					if(v[0]==u&&v[1]==i)break;
				}
				/*for(int i=1;i<=N;i++)
				{
					if(BCC[i]==BCC_CNT)printf("BCC%d\t%d\n",BCC_CNT,i);
				}*/
				if(!dfsbinary(i,BCC_CNT,1))minusans(i,BCC_CNT);
			}
			LOW[u]=min(LOW[u],LOW[i]);
		}
		else if(PRE[i]<PRE[u]&&i!=fa)
		{
			LOW[u]=min(LOW[u],PRE[i]);
		}
	}
	if(fa==-1&&child==1)ISCUT[u]=false;
}
int main()
{
	freopen("inn.txt","r",stdin);
	SIDE.clear();
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		PRE_CNT=BCC_CNT=0;
		for(int k1=1;k1<=N;k1++)
		{
			PRE[k1]=LOW[k1]=ISCUT[k1]=BCC[k1]=ISB[k1]=0;
			for(int k2=1;k2<=N;k2++)
			{
				LIKE[k1][k2]=k1==k2?false:true;
			}
		}
		while(M--)
		{
			int k1,k2;scanf("%d%d",&k1,&k2);
			LIKE[k1][k2]=LIKE[k2][k1]=false;
		}
		ANS=N;
		for(int i=1;i<=N;i++)
		{
			if(!PRE[i])dfs(i,-1);
		}
		//show();
		printf("%d\n",ANS);
	}
	return 0;
}
