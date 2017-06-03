#include<cstdio>
#include<cassert>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
int N;
LL S[24],SUM[25],ANS;
void Dfs(const int dep,const LL &a,const LL &b)
{
	if(1)
	{
		vector<LL>s;
		s.push_back(a),s.push_back(b),s.push_back(SUM[0]-SUM[dep]-a-b);
		sort(s.begin(),s.end());
		if((s[2]-s[0])+(s[2]-s[1])-SUM[dep]>=ANS+ANS)return;
		if(dep==N){getmin(ANS,s[2]-s[0]);return;}
	}
	Dfs(dep+1,a,b);
	Dfs(dep+1,a+S[dep],b);
	Dfs(dep+1,a,b+S[dep]);
}
LL Solve()
{
	ANS=INF/2LL;
	Dfs(0,0LL,0LL);
	return ANS;
}
int main()
{
	scanf(1,"%d",&N);
	for(int i=0;i<N;i++)scanf(1,"%lld",&S[i]);
	sort(S,S+N,greater<LL>());
	SUM[N]=0LL;
	for(int i=N-1;i>=0;i--)SUM[i]=SUM[i+1]+S[i];
	printf("%lld\n",Solve());
	return 0;
}
