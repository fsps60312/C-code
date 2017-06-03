#include<cstdio>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,M,DP[20001];
void getmax(int &a,const int &b){if(b>a)a=b;}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<=M;i++)DP[i]=-INF;
		DP[0]=0;
		for(int i=0;i<N;i++)
		{
			static int damage,coin;
			scanf("%d%d",&damage,&coin);
			if(coin<15)
			{
				for(int i=0;i+coin<=M;i++)if(DP[i]!=-INF)getmax(DP[i+coin],DP[i]+damage);
			}
			else
			{
				vector<int>coi,dam;
				for(int sum=coin,now=coin,da=damage;sum<=M;sum+=(now=now*1.07),da+=damage)coi.push_back(sum),dam.push_back(da);
				for(int i=M-coin;i>=0;i--)
				{
					for(int j=0;j<coi.size()&&i+coi[j]<=M;j++)if(DP[i]!=-INF)getmax(DP[i+coi[j]],DP[i]+dam[j]);
				}
			}
		}
		int ans=0;
		for(int i=0;i<=M;i++)getmax(ans,DP[i]);
		printf("%d\n",ans);
	}
	return 0;
}
