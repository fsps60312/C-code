#include<cstdio>
#include<vector>
#include<map>
using namespace std;
int N;
map<map<int,int>,double>DP;
double GetDP(const map<int,int>&s)
{
	{const auto &it=DP.find(s);if(it!=DP.end())return it->second;}
	if(s.empty())return DP[s]=0.0;
	double ans=0.0;
	double remain=1.0;
	for(auto it=s.begin();it!=s.end();it++)
	{
		map<int,int>nxt=s;
		if(it->second==1)nxt.erase(it->first);
		else --nxt[it->first];
		const double p=0.01*it->first*it->second;
		ans+=p*(GetDP(nxt)+1.0);
		remain-=p;
	}
//	printf("remain=%.9f\n",remain);
	//s=remain*(1+s)+ans
	//(1.0-remain)*s=ans+remain
	return DP[s]=(ans+remain)/(1.0-remain);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		map<int,int>s;
		for(int i=0,v;i<N;i++)scanf("%d",&v),++s[v];
		printf("%.9f\n",GetDP(s));
	}
	return 0;
}
