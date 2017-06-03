#include<cstdio>
using namespace std;
int T,N,M,GUILT[100001],ANNO[100001],EVID[100001],SUS[100001];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++)GUILT[i]=ANNO[i]=SUS[i]=0;
		int tru=0;
		for(int i=1;i<=N;i++)
		{
			int &e=EVID[i];
			scanf("%d",&e);
			if(e<0)ANNO[-e]++,tru++;
			else GUILT[e]++;
		}
//		printf("tru=%d\n",tru);
		int cnt=0;
		for(int i=1;i<=N;i++)
		{
			if(tru+GUILT[i]-ANNO[i]==M)SUS[i]=1,cnt++;
		}
//		printf("cnt=%d\n",cnt);
		for(int i=1;i<=N;i++)
		{
			int &e=EVID[i];
			if(e<0)
			{
				if(SUS[-e]==1)puts(cnt==1?"Lie":"Not defined");
				else puts("Truth");
			}
			else
			{
				if(SUS[e]==0)puts("Lie");
				else puts(cnt==1?"Truth":"Not defined");
			}
		}
	}
	return 0;
}
