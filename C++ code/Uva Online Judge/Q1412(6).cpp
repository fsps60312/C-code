#include<cstdio>
#include<cstdlib>
#include<map>
#include<vector>
#include<string>
#include<queue>
using namespace std;
int S_LIM[8];
double PRICE[100][8];
double DP[100][12870];
int PRE[100][12870];
string Ir[12870];
bool can_buy[12870][8],can_sell[12870][8];
map<string,int> I;
map<int,string> S_NAME;
double FUND;
int D,S_N,S_LN;
char STR[9];
struct Point
{
	int x,y;
};
vector<Point> TO[12870];
void dfs_DP(int dep,int sum)
{
	if(sum>S_LN)return;
	if(dep==S_N)
	{
		STR[dep]=0;
		int sz=I.size();
		I[STR]=sz;
		Ir[sz]=STR;
		for(int i=0;i<S_N;i++)
		{
			if(sum==S_LN||STR[i]-'0'==S_LIM[i])can_buy[sz][i]=false;
			else can_buy[sz][i]=true;
			if(STR[i]-'0'==0)can_sell[sz][i]=false;
			else can_sell[sz][i]=true;
		}
		TO[sz].clear();
		return;
	}
	for(int i=0;i<=S_LIM[dep];i++)
	{
		STR[dep]=i+'0';
		dfs_DP(dep+1,sum+i);
	}
}
inline int buy(int i,int s)
{
	string str=Ir[i];
	str[s]++;
	return I[str];
}
inline int sell(int i,int s)
{
	string str=Ir[i];
	str[s]--;
	return I[str];
}
void dfs_print(int d,int i)
{
	if(d<0)return;
	int &p=PRE[d][i];
	if(p==-1)
	{
		dfs_print(d-1,i);
		printf("HOLD\n");
	}
	else if(p>=S_N)
	{
		dfs_print(d-1,sell(i,p-S_N));
		printf("BUY %s\n",S_NAME[p-S_N].c_str());
	}
	else
	{
		dfs_print(d-1,buy(i,p));
		printf("SELL %s\n",S_NAME[p].c_str());
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=0;
	while(scanf("%lf%d%d%d",&FUND,&D,&S_N,&S_LN)==4)
	{
		I.clear();
		S_NAME.clear();
		for(int i=0;i<S_N;i++)
		{
			int s_lot;
			scanf("%s%d%d",STR,&s_lot,&S_LIM[i]);
			S_NAME[i]=STR;
			for(int j=0;j<D;j++)
			{
				scanf("%lf",&PRICE[j][i]);
				PRICE[j][i]*=s_lot;
			}
		}
		dfs_DP(0,0);
//		for(map<string,int>::iterator it=I.begin();it!=I.end();it++)
//		{
//			printf("%s %d\n",it->first.c_str(),it->second);
//		}
		for(int i=0;i<D;i++)
		{
			for(int j=0;j<I.size();j++)
			{
				DP[i][j]=-1;
			}
		}
		DP[0][0]=FUND;
		PRE[0][0]=-1;
		for(int i=0;i<S_N;i++)
		{
//			printf("PRICE[%d]=%.2lf\n",i,PRICE[0][i]);
			if(FUND>=PRICE[0][i])
			{
				int j=buy(0,i);
				DP[0][j]=FUND-PRICE[0][i];
				PRE[0][j]=S_N+i;
			}
		}
		for(int i=0;i<I.size();i++)
		{
			for(int j=0;j<S_N;j++)
			{
				if(can_buy[i][j])
				{
					TO[i].push_back((Point){buy(i,j),S_N+j});
				}
				if(can_sell[i][j])
				{
					TO[i].push_back((Point){sell(i,j),j});
				}
			}
		}
		for(int d=1;d<D;d++)
		{
			for(int i=0;i<I.size();i++)
			{
				double &dp=DP[d-1][i];
				if(dp<0)continue;
				if(dp>DP[d][i])
				{
					DP[d][i]=dp;
					PRE[d][i]=-1;
				}
				for(int i2=0;i2<TO[i].size();i2++)
				{
					int &j=TO[i][i2].y,&k=TO[i][i2].x;
					if(j>=S_N&&dp>=PRICE[d][j-S_N])
					{
						if(dp-PRICE[d][j-S_N]>DP[d][k])
						{
							DP[d][k]=dp-PRICE[d][j-S_N];
							PRE[d][k]=j;
						}
					}
					else if(j<S_N)
					{
						if(dp+PRICE[d][j]>DP[d][k])
						{
							DP[d][k]=dp+PRICE[d][j];
							PRE[d][k]=j;
						}
					}
				}
			}
		}
//		for(int i=0;i<I.size();i++)if(DP[0][i]>=0)printf("%s %.2lf\n",Ir[i].c_str(),DP[0][i]);
		if(kase++)puts("");
		printf("%.2lf\n",DP[D-1][0]);
		dfs_print(D-1,0);
	}
	return 0;
}
