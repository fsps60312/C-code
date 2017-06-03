#include<cstdio>
//#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000000000LL;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
/*
0
|
|
|
1
||
|
|
2
|
||
|
3
|
|
||
4
||
||
|
5
||
|
||
6
|
||
||
7
|||
||
|
8
|
||
|||
*/
LL DP[2001][9];
LL Get(const int len,const int type)
{
	if(len<0)return 0LL;
	LL &dp=DP[len][type];
	if(dp!=-1LL)return dp;
	switch(type)
	{
		case 0:dp=Get(len-1,0)+Get(len-1,2)+Get(len-1,1)+Get(len-1,5)+Get(len-1,3)+Get(len-1,6)+Get(len-1,4);break;
		case 1:dp=Get(len-2,0)+Get(len-2,6);break;
		case 2:dp=Get(len-2,0)+Get(len-2,5);break;
		case 3:dp=Get(len-2,0)+Get(len-2,4);break;
		case 4:dp=Get(len-2,0)+Get(len-1,1)+Get(len-1,7);break;
		case 5:dp=Get(len-2,0);break;
		case 6:dp=Get(len-2,0)+Get(len-1,8)+Get(len-1,3);break;
		case 7:dp=Get(len-2,1);break;
		case 8:dp=Get(len-2,3);break;
		default:assert(0);return -1LL;
	}
	return dp%=MOD;
}
int main()
{
	for(int i=0;i<=2000;i++)for(int j=0;j<9;j++)DP[i][j]=-1LL;
	DP[0][0]=1LL;
	for(int i=1;i<9;i++)DP[0][i]=DP[1][i]=0LL;
	DP[2][7]=DP[2][8]=0LL;
	for(int n;;)
	{
		assert(scanf("%d",&n)==1);
		if(n==0){assert(scanf("%d",&n)!=1);break;}
		static int kase=1;
		printf("Case %d: %lld\n",kase++,Get(n,0));
	}
	return 0;
}
