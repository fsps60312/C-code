#include<cstdio>
#include<cassert>
using namespace std;
int N,M,V,ALL;
int DP[1<<25];
bool MODDED[1<<25];
int GetDP(const int s)
{
	if(DP[s]!=-2)return DP[s];
	if(MODDED[s])return false;
	int &ans=DP[s]=-1;
	for(int t=s,i;t;t^=i)
	{
		i=t&(-t);
		const int ta=GetDP(s^i);
		if(ta==0)return ans=1;
		else if(ta==1)ans=0;
	}
	return ans;
}
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
		for(int i=0;i<(1<<N);i++)DP[i]=-2,MODDED[i]=((V^(ALL^i))%M==0);
		assert(!MODDED[ALL]);
		DP[0]=-1;
		const int ans=GetDP(ALL);
		if(ans==1)puts("Henry");
		else if(ans==0)puts("Rider");
		else printf("ans=%d\n",ans),assert(0);
	}
	return 0;
}
