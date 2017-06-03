#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
bool atrange(int v,int l,int r){return v>=l&&v<=r;}
struct Dp
{
	int Min,Max,Sum;
	void init(){Min=2147483647,Max=-2147483647,Sum=0;}
	void update(Dp d,int v)
	{
		if(d.Sum==0)return;
		Sum+=d.Sum;
		getmax(Max,(d.Max<<1)+v);
		getmin(Min,(d.Min<<1)+v);
	}
};
int N,D,K;
Dp DP[65][65];//0s, 1s
bool INTE[64];
vector<int> I[2];
int main()
{
	freopen("in.txt","r",stdin); 
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d%d",&D,&K);
		for(int i=N-1;i>=0;i--)
		{
			INTE[i]=K&1;
			K>>=1;
		}
		I[0].clear(),I[1].clear();
		for(int i=0;i<N;i++)
		{
			I[INTE[i]].push_back(i);
		}
		for(int i=0;i<=I[0].size();i++)
		{
			for(int j=0;j<=I[1].size();j++)
			{
				DP[i][j].init();
			}
		}
		printf("The Integer is: ");for(int i=0;i<N;i++)printf("%d",INTE[i]);printf("\n");
		printf("0's pos:");for(int i=0;i<I[0].size();i++)printf(" %d",I[0][i]);printf("\n");
		printf("1's pos:");for(int i=0;i<I[1].size();i++)printf(" %d",I[1][i]);printf("\n");
		DP[0][0]=(Dp){0,0,1};
		for(int i=1;i<=N;i++)
		{
			printf("\t%d:\n",i);
			for(int j=0;j<=i;j++)//0s
			{
				int n0=j,n1=i-j;
				if(n0>I[0].size())break;
				if(n1>I[1].size())continue;
				int p0=(n0==0?-1:I[0][n0-1]),p1=(n1==0?-1:I[1][n1-1]);
				int p=i-1;
				Dp &dp=DP[n0][n1];
				if(n0>0&&atrange(p0-p,-D,D))
				{
					dp.update(DP[n0-1][n1],0);
					printf("update0 (%d,%d) to {%d,%d,%d}\n",n0,n1,dp.Min,dp.Max,dp.Sum);
				}
				if(n1>0&&atrange(p1-p,-D,D))
				{
					dp.update(DP[n0][n1-1],1);
					printf("update1 (%d,%d) to {%d,%d,%d}\n",n0,n1,dp.Min,dp.Max,dp.Sum);
				}
			}
		}
		Dp &ans=DP[I[0].size()][I[1].size()];
		printf("Case %d: %d %d %d\n",kase++,ans.Sum,ans.Min,ans.Max);
	}
	return 0;
}
