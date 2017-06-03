#include<cstdio>
#include<cassert>
#include<string>
#include<set>
#include<algorithm>
using namespace std;
const int INF=2147483647;
template<class... END>int ScanfLine(const char *c,END... end)
{
	static char buffer[1<<20];
	fgets(buffer,INF,stdin);
	return sscanf(buffer,c,end...);
}
set<int>LOC[128];
int Lcs(const string &a,const string &b)
{
	for(int c=33;c<=127;c++)LOC[c].clear();
	for(int i=0;i<(int)b.size();i++)LOC[(int)b[i]].insert(i);
	static int dp[20000];
	int ans=0;
	for(int i=0;i<(int)a.size();i++)
	{
//		printf("ans=%d\n",ans);
		set<int>&loc=LOC[(int)a[i]];
		for(auto it=loc.upper_bound(ans==0?-1:dp[ans-1]);;)
		{
			if(it!=loc.end())
			{
				const int j=(int)(upper_bound(dp,dp+ans,*it)-dp);
				if(j<ans)LOC[(int)b[dp[j]]].insert(dp[j]);
				else ++ans;
				dp[j]=*it;
				if(it==loc.begin()){loc.erase(it);break;}
				else loc.erase(it--);
			}
			else
			{
				if(it==loc.begin())break;
				else --it;
			}
		}
	}
//	puts("pass");
	return ans;
}
int H,W;
char S[20][25];
string Input()
{
	int n,x,y;
	static char path[20001];
	ScanfLine("%d%d%d",&n,&x,&y),--x,--y;
	ScanfLine("%s",path);
	string s;s.push_back(S[x][y]);
	for(int i=0;i<n;i++)
	{
		const int c=path[i];
		switch(c)
		{
			case'N':--x;break;
			case'E':++y;break;
			case'W':--y;break;
			case'S':++x;break;
			default:assert(0);break;
		}
		s.push_back(S[x][y]);
	}
	return s;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;ScanfLine("%d",&testcount);
//	puts("a");
	while(testcount--)
	{
		ScanfLine("%d%d",&H,&W);
		for(int i=0;i<H;i++)fgets(S[i],INF,stdin);
		const string &a=Input(),&b=Input();
//	puts("b");
		const int ans=Lcs(a,b);
//	puts("c");
		static int kase=0;
		printf("Case %d: %d %d\n",++kase,(int)a.size()-ans,(int)b.size()-ans);
	}
	return 0;
}
