#include<cstdio>
#include<cstdlib>
#include<vector>
#define ULL unsigned long long
using namespace std;
void getmax(ULL &a,ULL b){if(b>a)a=b;}
void getmin(ULL &a,ULL b){if(b<a)a=b;}
struct Dp
{
	ULL Min,Max,Sum;
	void init(){Min=(1ULL<<63)+((1ULL<<63)-1),Max=0,Sum=0;}
	void update(Dp d,int v)
	{
		if(d.Sum==0)return;
		Sum+=d.Sum;
		getmax(Max,(d.Max<<1)+v);
		getmin(Min,(d.Min<<1)+v);
	}
};
int N,D;
ULL K;
Dp DP[65][65];//0s, 1s
bool INTE[64];
vector<int> I[2];
int main()
{
//	freopen("in.txt","r",stdin); 
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d%llu",&D,&K);
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
//		printf("The Integer is: ");for(int i=0;i<N;i++)printf("%d",INTE[i]);printf("\n");
//		printf("0's pos:");for(int i=0;i<I[0].size();i++)printf(" %d",I[0][i]);printf("\n");
//		printf("1's pos:");for(int i=0;i<I[1].size();i++)printf(" %d",I[1][i]);printf("\n");
		DP[0][0]=(Dp){0,0,1};
		for(int i=0;i<N;i++)
		{
//			printf("\t%d:\n",i);
			for(int j=0;j<=i;j++)//0s
			{
				int i0=j,i1=i-j;
				Dp &dp=DP[i0][i1];
				if(i0<I[0].size())
				{
					if(i1==I[1].size()||I[1][i1]+D>=I[0][i0])//can trans 0(next 1 can move to 0's back)
					{
						DP[i0+1][i1].update(dp,0);
						Dp &td=DP[i0+1][i1];
//						printf("update0 (%d,%d) to {%d,%d,%d}\n",i0+1,i1,td.Min,td.Max,td.Sum);
					}
				}
				if(i1<I[1].size())
				{
					if(i0==I[0].size()||I[0][i0]+D>=I[1][i1])//can trans 1
					{
						DP[i0][i1+1].update(dp,1);
						Dp &td=DP[i0][i1+1];
//						printf("update1 (%d,%d) to {%d,%d,%d}\n",i0,i1+1,td.Min,td.Max,td.Sum);
					}
				}
			}
		}
		Dp &ans=DP[I[0].size()][I[1].size()];
		printf("Case %d: %llu %llu %llu\n",kase++,ans.Sum,ans.Min,ans.Max);
	}
	return 0;
}
