#include<cstdio>
#include<cassert>
using namespace std;
int CntBit(int x)
{
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
int N,K,CB[1<<20];
double P[20],DP[1<<20][20];
double GetDP(const int s,const int last)
{
	assert(s&(1<<last));
	double &ans=DP[s][last];
	if(ans!=-1.0)return ans;
	const int nxts=s-(1<<last);
	assert(CntBit(s)==CntBit(nxts)+1);
	ans=0.0;
	for(int i=0;i<N;i++)if(nxts&(1<<i))
	{
		ans+=P[last]*GetDP(nxts,i);
	}
//	printf("DP[%d][%d]=%.10f\n",s,last,ans);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int s=0;s<(1<<N);s++)for(int i=0;i<N;i++)DP[s][i]=-1.0;
		for(int i=0;i<N;i++)scanf("%lf",&P[i]),DP[1<<i][i]=P[i];
//		for(int i=0;i<(1<<N);i++)CB[i]=CntBit(i);
		static double ans[20];
		for(int i=0;i<N;i++)ans[i]=0.0;
		for(int s=0;s<(1<<N);s++)if(CntBit(s)==K)
		{
			for(int i=0;i<N;i++)if(s&(1<<i))
			{
				const double dp=GetDP(s,i);
				for(int j=0;j<N;j++)if(s&(1<<j))ans[j]+=dp;
			}
		}
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%.10f",ans[i]);
		}
		puts("");
	}
	return 0;
}
