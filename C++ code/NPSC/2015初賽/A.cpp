#include<cstdio>
#include<queue>
using namespace std;
const int POW3=19682;//(2<<0)+(2<<2)+(2<<4)+(2<<6)+(2<<8)+(2<<10)+(2<<12)+(2<<14)+(2<<16);
const int INF=2147483647;
int N,S[50][9],LIMIT[50];
int DP[51][POW3+1];
int Nxt(int s,int now)
{
	now--;
	int ans=0;
	for(int i=0,d=1;i<9;i++,d*=3)
	{
		int ds=s/d%3,dn=now/d%3;
		if(dn>ds)dn=ds;
		ans+=dn*d;
	}
	return ans;
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%d",&LIMIT[i]);
			for(int j=0;j<9;j++)
			{
				static char tmp[10];
				scanf("%s",tmp);
				if(tmp[0]=='x')S[i][j]=-1;
				else sscanf(tmp,"%d",&S[i][j]);
			}
		}
		for(int s=0;s<=POW3;s++)DP[0][s]=-INF;
		DP[0][0]=0;
		int cnt=0;
		for(int i=1;i<=N;i++)
		{
			for(int s=0;s<=POW3;s++)if(DP[i-1][s]!=-INF)
			{
				for(int a=POW3-s;;a=Nxt(s,a))
				{
					cnt++;
					//do sth.
					if(a==0)break;
				}
			}
			printf("cnt=%d\n",cnt);
		}
	}
	return 0;
}
