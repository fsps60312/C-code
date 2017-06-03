#include<bits/stdc++.h>
using namespace std;
int N,VIS[10000],S[10000],KASE=0;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<10000;i++)VIS[i]=0;
	while(scanf("%d:",&N)==1&&N)
	{
		KASE++;
		bool ans=true;
		for(int i=0,j,k;i<N;i++)
		{
			int &v=S[i];
			scanf("%d",&v);
//			printf(" %d",v);
			if(!ans)continue;
			if(VIS[v]==KASE)
			{
//				printf("v=%d\n",v);
				ans=false;
			}
			VIS[v]=KASE;
			for(j=0;j<i;j++)
			{
				k=v*2-S[j];
//				printf("k=%d\n",k);
				if(k>=0&&k<N)VIS[k]=KASE;
			}
		}
		puts(ans?"yes":"no");
	}
	return 0;
}
