#include<cstdio>
#include<cassert>
#include<string>
#include<algorithm>
using namespace std;
const int INF=2147483647;
template<class... END>int ScanfLine(const char *c,END... end)
{
	static char buffer[1<<20];
	fgets(buffer,INF,stdin);
	return sscanf(buffer,c,end...);
}
vector<int>LOC[128];
int Lcs(const string &a,const string &b)
{
	for(int c=33;c<=127;c++)LOC[c].clear();
	for(int i=0;i<(int)b.size();i++)LOC[b[i]].push_back(i);
	static int dp[20000],id[20000];
	int ans=0;
	for(int i=0;i<(int)a.size();i++)
	{
		const vector<int>loc=LOC[a[i]];
		for(int j=(int)(upper_bound(loc.begin(),loc.end(),ans==0:-1:dp[ans-1])-loc.begin());j>=0;j--)
		{
			
		}
		assert(0);
	}
	assert(0);
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
	freopen("in.txt","r",stdin);
	int testcount;ScanfLine("%d",&testcount);
	while(testcount--)
	{
		ScanfLine("%d%d",&H,&W);
		for(int i=0;i<H;i++)fgets(S[i],INF,stdin);
		const string &a=Input(),&b=Input();
		const int ans=Lcs(a,b);
		static int kase=0;
		printf("Case %d: %d %d\n",++kase,(int)a.size()-ans,(int)b.size()-ans);
	}
	return 0;
}
