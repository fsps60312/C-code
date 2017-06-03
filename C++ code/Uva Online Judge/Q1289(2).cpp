#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N;
struct Pair
{
	int x,y;
	Pair(){}
	Pair(const int &x,const int &y):x(x),y(y){}
	bool operator<(const Pair &p)const{return x!=p.x?x<p.x:y<p.y;}
	bool operator==(const Pair &p)const{return x==p.x&&y==p.y;}
};
vector<Pair>ALL;
int DP[2500][50],EXIST[2500][50],SZ;
vector<int>CNT[2500];
int Solve()
{
	static int kase=0;kase++;
	SZ=0;
	for(int i=0;i<ALL.size();)
	{
		Pair &p=ALL[i];
		CNT[SZ].clear();
		for(;i<ALL.size()&&ALL[i].x==p.x;i++)
		{
			CNT[SZ].push_back(ALL[i].y);
			EXIST[SZ][ALL[i].y]=kase;
		}
		SZ++;
	}
	for(int i=0;i<CNT[0].size();i++)DP[0][i]=CNT[0].size();
	for(int i=1;i<SZ;i++)
	{
		for(int j=0;j<CNT[i].size();j++)
		{
			int &a=CNT[i][j];
			int &dp=DP[i][j]=INF;
			for(int k=0;k<CNT[i-1].size();k++)
			{
				int &b=CNT[i-1][k];
				if(EXIST[i][b]==kase&&(b!=a||CNT[i].size()==1))dp=min(dp,DP[i-1][k]-1);
				else dp=min(dp,DP[i-1][k]);
			}
			dp+=CNT[i].size();
		}
	}
	int ans=INF;
	for(int i=0;i<CNT[SZ-1].size();i++)ans=min(ans,DP[SZ-1][i]);
	return (ans-1)*2-(N-1);
}
int main()
{
//	freopen("inn.txt","r",stdin);
	for(int i=0;i<2500;i++)for(int j=0;j<50;j++)EXIST[i][j]=0;
	while(scanf("%d",&N)==1)
	{
		ALL.clear();
		for(int i=0,h;i<N;i++)
		{
			scanf("%d",&h);
			for(int v;h--;){scanf("%d",&v);ALL.push_back(Pair(v,i));}
		}
		sort(ALL.begin(),ALL.end());
//		for(int i=0;i<ALL.size();i++)printf("(%d,%d)\n",ALL[i].x,ALL[i].y);
//		printf("%d\n",Pair(26,0)==Pair(26,1));
		ALL.resize(unique(ALL.begin(),ALL.end())-ALL.begin());
		int ans=Solve();
		static int kase=1;
		printf("Case %d: %d\n",kase++,ans);
	}
	return 0;
}
