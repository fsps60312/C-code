#include<cstdio>
#include<cassert>
using namespace std;
int N,M,V,ALL;
int DP[1<<25];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		V=0;
		for(int i=0,a;i<N;i++)
		{
			scanf("%d",&a);
			V=(V<<1)+a;
		}
		scanf("%d",&M),M=(1<<M)-1;
//		printf("V=%d,M=%d\n",V,M);
		ALL=(1<<N)-1;
		for(int i=0;i<(1<<N);i++)DP[i]=-1;
		DP[0]=-1;
		for(int s=1,i;s<=ALL;s++)
		{
			if((V^(ALL^s))%M==0)DP[s]=0;
			else
			{
				for(int t=s;t;t^=i)
				{
					i=t&(-t);
					const int ta=DP[s^i];
					if(ta==0){DP[s]=1;break;}
					else if(ta==1)DP[s]=0;
				}
			}
		}
		const int ans=DP[ALL];
		if(ans==1)puts("Henry");
		else if(ans==0)puts("Rider");
		else printf("ans=%d\n",ans),assert(0);
		break;
	}
	return 0;
}
