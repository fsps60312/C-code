#include<cstdio>
#include<cassert>
using namespace std;
const int ALL=(1<<16)-1;
int S[16];
inline int cntbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
int PM[24][4]=
{
	{0,1,2,3},{0,1,3,2},{0,2,1,3},{0,2,3,1},{0,3,1,2},{0,3,2,1},
	{1,0,2,3},{1,0,3,2},{1,2,0,3},{1,2,3,0},{1,3,0,2},{1,3,2,0},
	{2,0,1,3},{2,0,3,1},{2,1,0,3},{2,1,3,0},{2,3,0,1},{2,3,1,0},
	{3,0,1,2},{3,0,2,1},{3,1,0,2},{3,1,2,0},{3,2,0,1},{3,2,1,0}
};
int DP[1<<16];
bool FOUR[1<<16];
int VIS[10241];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=10240;i++)VIS[i]=0;
	while(scanf("%d",&S[0])==1&&S[0])
	{
		for(int i=1;i<16;i++)scanf("%d",&S[i]);
		for(int i=0;i<=ALL;i++)DP[i]=0,FOUR[i]=false;
		for(int a=0;a<=ALL;a++)
		{
			if(cntbits(a)!=4)continue;
			FOUR[a]=true;
			static int t1[4];
			for(int i=0,j=0;i<16;i++)if(a&(1<<i))t1[j++]=S[i];
			for(int i=0;i<24;i++)VIS[t1[PM[i][0]]+2*t1[PM[i][1]]+3*t1[PM[i][2]]+4*t1[PM[i][3]]]++;
			const int &s=ALL^a;
			assert(cntbits(s)==12);
			for(int b=(s-1)&s;b;b=(b-1)&s)
			{
				if(cntbits(b)!=4||FOUR[b])continue;
				static int t2[4];
				for(int i=0,j=0;i<16;i++)if(b&(1<<i))t2[j++]=S[i];
				for(int i=0;i<24;i++)DP[a+b]+=VIS[t2[PM[i][0]]+2*t2[PM[i][1]]+3*t2[PM[i][2]]+4*t2[PM[i][3]]];
			}
			for(int i=0;i<24;i++)VIS[t1[PM[i][0]]+2*t1[PM[i][1]]+3*t1[PM[i][2]]+4*t1[PM[i][3]]]--;
		}
		int ans=0;
		for(int s=0;s<=ALL;s++)
		{
			if(cntbits(s)!=8||FOUR[ALL^s])continue;
			FOUR[s]=true;
			ans+=DP[s]*DP[ALL^s];
		}
		static int kase=1;
		printf("Case %d: %d\n",kase++,ans);
	}
	return 0;
}
