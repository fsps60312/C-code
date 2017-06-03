#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct Cable
{
	int from,to,bw,cost;
}CABLE[10000];
bool cmp_CABLE(Cable a,Cable b)
{
	return a.cost<b.cost;
}
int T,N,M,C,FA[60],DJSET[60];
int findset(int a)
{
	return DJSET[a]==a?a:(DJSET[a]=findset(DJSET[a]));
}
bool BuildCable(int limit)
{
	for(int i=0;i<N;i++)
	{
		FA[i]=-1;
		DJSET[i]=i;
	}
	int gpn=N;
	long long budjet=0;
	for(int i=0;;i++)
	{
		if(i==M)return false;
		if(CABLE[i].bw<limit)continue;
		int fx=findset(CABLE[i].from),fy=findset(CABLE[i].to);
		if(fx==fy)
		{
			if(FA[fy]==-1)
			{
				FA[fy]=i;
				budjet+=CABLE[i].cost;
			}
			else continue;
		}
		else
		{
			if(FA[fy]==-1)
			{
				FA[fy]=i;
				budjet+=CABLE[i].cost;
				gpn--;
			}
			else
			{
				budjet-=CABLE[FA[fy]].cost;
				FA[fy]=i;
				budjet+=CABLE[i].cost;
				gpn--;
			}
			DJSET[fx]=fy;
		}
		if(gpn==1)return budjet<=C;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&M,&C);
		int l=2147483647,r=0;
		for(int i=0;i<M;i++)
		{
			Cable &c=CABLE[i];
			scanf("%d%d%d%d",&c.from,&c.to,&c.bw,&c.cost);
			if(c.to==0)
			{
				i--,M--;
				continue;
			}
			if(c.bw>r)r=c.bw;
			if(c.bw<l)l=c.bw;
		}
		sort(CABLE,CABLE+M,cmp_CABLE);
		r++;
		if(!BuildCable(l))printf("streaming not possible.\n");
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
	}
	return 0;
}
