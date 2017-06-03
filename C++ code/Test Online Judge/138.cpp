#include<cstdio>
#include<cassert>
using namespace std;
const int MOD=1000007;
bool InsertH(const int column,const int s,int &ans)
{
	assert(column<=2);
	assert(!(s&(1<<column)));
	if(column==2)return false;
	if(s&(1<<(column+1)))return false;
	ans=s;ans|=(1<<(column+1));
	return true;
}
bool InsertV(const int column,const int s,int &ans)
{
	assert(!(s&(1<<column)));
	ans=s;ans|=(1<<column);
	return true;
}
void AddTo(int &a,const int &b){(a+=b)%=MOD;}
int ANS[100001];
int DP[2][1<<3];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<(1<<3);i++)DP[0][i]=0;
	DP[0][0]=1;
	for(int row=0,column=0,d=0;;column++,d^=1)
	{
		if(column==3)
		{
			row++,column=0;
			ANS[row]=DP[d][0];
		}
		if(row>=100000)break;
		for(int i=0;i<(1<<3);i++)DP[d^1][i]=0;
//		printf("(%d,%d)\n",row,column);
		for(int s=0;s<(1<<3);s++)
		{
//			printf("DP[%d][%d]=%d\n",d,s,DP[d][s]);
			if(s&(1<<column))AddTo(DP[d^1][s-(1<<column)],DP[d][s]);
			else
			{
				static int t;
				if(InsertH(column,s,t))AddTo(DP[d^1][t],DP[d][s]);
				if(InsertV(column,s,t))AddTo(DP[d^1][t],DP[d][s]);
			}
		}
	}
	static int casenumber;assert(scanf("%d",&casenumber)==1);
	while(casenumber--)
	{
		static int n;scanf("%d",&n);
		assert(n>=1&&n<=100000);
		printf("%d\n",ANS[n]);
	}
	return 0;
}
