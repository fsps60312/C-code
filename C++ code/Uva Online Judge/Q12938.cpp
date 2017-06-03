#include<cstdio>
#include<set>
using namespace std;
int T,N;
set<int>ALL;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=32;i<=99;i++)ALL.insert(i*i);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			int ans=0;
			for(int i=1;i<=9;i++)
			{
				if(i==N/1000)continue;
				if(ALL.find(i*1000+N%1000)!=ALL.end())ans++;
			}
			int d=N/100%10;
			for(int i=0;i<=9;i++)
			{
				if(i==d)continue;
				if(ALL.find(N+(i-d)*100)!=ALL.end())ans++;
			}
			d=N/10%10;
			for(int i=0;i<=9;i++)
			{
				if(i==d)continue;
				if(ALL.find(N+(i-d)*10)!=ALL.end())ans++;
			}
			d=N%10;
			for(int i=0;i<=9;i++)
			{
				if(i==d)continue;
				if(ALL.find(N+(i-d))!=ALL.end())ans++;
			}
			static int kase=1;
			printf("Case %d: %d\n",kase++,ans);
		}
	}
	return 0;
}
