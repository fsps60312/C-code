#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
using namespace std;
typedef long long LL;
const double EPS=1e-9;
const int INF=2147483647;
int N,SEAT;
vector<int>PARTY;
vector<vector<int> >ANS;
vector<int>ORDER;
void Dfs(const int u,vector<int>&now,const int sum)
{
	if(sum*2>SEAT)
	{
		ANS.push_back(now);
		return;
	}
	if(u==N)return;
	if(PARTY[ORDER[u]])
	{
		now.push_back(ORDER[u]);
		Dfs(u+1,now,sum+PARTY[ORDER[u]]);
		now.pop_back();
	}
	Dfs(u+1,now,sum);
}
char Id(const int i)
{
	if(i<26)return 'A'+i;
	return 'a'+(i-26);
}
LL DoDp()
{
	static LL dp[100001];
	for(int i=0;i<=SEAT;i++)dp[i]=0LL;
	dp[0]=1LL;
	LL ans=0LL;
	for(int i=0;i<N;i++)
	{
		for(int j=SEAT;j>=PARTY[ORDER[i]];j--)
		{
			dp[j]+=dp[j-PARTY[ORDER[i]]];
			if((j-PARTY[ORDER[i]])*2<=SEAT&&j*2>SEAT)ans+=dp[j-PARTY[ORDER[i]]];
		}
	}
	return ans;
}
int main()
{
//	freopen("inA.txt","r",stdin);
	for(int total_seat;scanf("%d%d",&N,&total_seat)==2;)
	{
		PARTY.clear();
		for(int i=0,v;i<N;i++)scanf("%d",&v),PARTY.push_back(total_seat*0.01*v+EPS);
		SEAT=0;
		for(int i=0;i<N;i++)SEAT+=PARTY[i];
		ORDER.clear();
		for(int i=0;i<N;i++)ORDER.push_back(i);
		sort(ORDER.begin(),ORDER.end(),[](int a,int b)->bool{return PARTY[a]>PARTY[b];});
		const LL all=DoDp();
		printf("%lld\n",all);
		if(all>10000LL)continue;
		ANS.clear();
		vector<int>now;
		Dfs(0,now,0);
		assert(now.empty());
		map<string,int>output; 
		for(vector<int>&s:ANS)
		{
			int sum=0;
			sort(s.begin(),s.end());
			string name="";
			for(const int v:s)name+=Id(v),sum+=PARTY[v];
			output[name]=sum;
		}
		for(const auto &it:output)printf("%s %d\n",it.first.c_str(),it.second);
	}
	return 0;
}
