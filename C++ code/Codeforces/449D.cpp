#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int N;
LL CNT[21][1<<20],POW[1000001];
int CntBit(int x)
{
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
int main()
{
//	freopen("in.txt","r",stdin);
	POW[0]=1LL;
	for(int i=1;i<=1000000;i++)POW[i]=(POW[i-1]*2LL)%MOD;
	while(scanf("%d",&N)==1)
	{
		for(int s=0;s<(1<<20);s++)CNT[0][s]=0LL;
		for(int i=0,v;i<N;i++)scanf("%d",&v),CNT[0][v]++;
		for(int i=1;i<=20;i++)
		{
			for(int s=0;s<(1<<20);s++)
			{
				if(s&(1<<(i-1)))CNT[i][s]=CNT[i-1][s];
				else CNT[i][s]=CNT[i-1][s]+CNT[i-1][s+(1<<(i-1))];
			}
		}
		LL ans=0LL;
		for(int s=0;s<(1<<20);s++)
		{
			if(CntBit(s)&1)(ans-=POW[CNT[20][s]])%=MOD;
			else (ans+=POW[CNT[20][s]])%=MOD;
		}
		printf("%I64d\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}
