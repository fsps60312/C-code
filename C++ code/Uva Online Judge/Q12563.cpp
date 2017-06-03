#include<cstdio>
#include<cstdlib>
using namespace std;
int T,N,L;
struct Point
{
	int x,y;
	bool operator>(Point a)
	{
		return x>a.x||(x==a.x&&y>a.y);
	}
};
int DP[180*50];
void getmax(Point &a,Point b){if(b>a)a=b;}
bool getmax(int &a,int b){if(b>a){a=b;return true;}return false;}
int main()
{//678
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d",&N,&L);
		DP[0]=0;
		for(int i=1;i<L;i++)
		{
			DP[i]=-1;
		}
		Point ans=(Point){0,0};
		for(int i=0;i<N;i++)
		{
			int a;scanf("%d",&a);
			for(int i=L-a-1;i>=0;i--)
			{
				if(DP[i]==-1)continue;
				if(getmax(DP[i+a],DP[i]+1));
				{
					getmax(ans,(Point){DP[i+a],i+a});
				}
			}
		}
		printf("Case %d: %d %d\n",kase++,ans.x+1,ans.y+678);
	}
	return 0;
}
