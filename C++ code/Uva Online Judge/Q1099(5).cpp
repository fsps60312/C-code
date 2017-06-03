#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,W,H,P[15];
int DP[1<<15][101],AREA[1<<15];
int cntbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
int getDP(int w,int s)
{
	int h=AREA[s]/w;
	if(w>h)swap(h,w);
	int &dp=DP[s][w];
	if(dp!=-1)return dp;
	if(cntbits(s)==1)return dp=1;
	for(int s0=(s-1)&s;s0>0;s0=(--s0)&s)
	{
		if(AREA[s0]%w==0&&getDP(w,s0)&&getDP(w,s^s0))return dp=1;
		if(AREA[s0]%h==0&&getDP(h,s0)&&getDP(h,s^s0))return dp=1;
	}
	return dp=0;
}
int main()
{
//	freopen("inn.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d%d",&W,&H);
		if(W>H)swap(W,H);
		int sum=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&P[i]);
			sum+=P[i];
		}
		for(int i=0,a=0,k;i<(1<<N);i++,a=0)
		{
			for(k=0;k<N;k++)if(i&(1<<k))a+=P[k];
			AREA[i]=a;
		}
		for(int i=0;i<(1<<N);i++)for(int j=0;j<=W;j++)DP[i][j]=-1;
		printf("Case %d: ",kase++);
		printf(sum==W*H&&getDP(W,(1<<N)-1)?"Yes\n":"No\n");
	}
	return 0;
}
