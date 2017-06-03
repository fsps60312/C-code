#include<cstdio>
#include<map>
using namespace std;
typedef long long LL;
int T,L;
int A[2000001];
LL N,MOD;
LL Solve()
{
	map<int,LL>s;
	s[0]=1;
	LL ans=0LL;
	for(int i=0,now=0;i<2*L;i++)
	{
		if(i==L&&N==1)return ans;
		if(A[i]==1)now++;
		else now--;
		auto it=s.find(now);
		if(it!=s.end())ans+=s[now],ans%=MOD,it->second++;
		else s[now]=1LL;
	}
	if(N==2LL)return ans;
	//DP[1]=ans;
	//DP[n]=DP[n-1]*2+(rori same linv)
	//(1,0)(0,1)
	//(1,1)(1,1)
	//(2,2)(2,2)
	map<int,LL>ls,rs;
	for(int i=0,now=0;i<2*L;i++)
	{
		if(A[i]==1)now++;
		else now--;
		auto it=ls.find(now);
		if(it==ls.end())ls[now]=1;
		else it->second++;
	}
	for(int i=2*L-1,now=0;i>=0;i--)
	{
		if(A[i]==1)now++;
		else now--;
		auto it=rs.find(now);
		if(it==rs.end())rs[now]=1;
		else it->second++;
	}
	LL same=0LL,diff=0LL;
	for(auto it=ls.begin();it!=ls.end();it++)
	{
		map<int,LL>::iterator result;
		result=rs.find(it->first);
		if(result!=rs.end())same+=result->second,same%=MOD;
		result=rs.find(-(it->first));
		if(result!=rs.end())diff+=result->second,diff%=MOD;
	}
	//n=1:(1,0)
	//n=2:(1,0)(0,1)
	//n=3:(1,1)(1,1)
	//n=4:(2,2)(2,2)
	//n=5:(4,4)(4,4)
	//n=6:(8,8)(8,8)
	ans*=2LL,ans%=MOD;
	ans+=diff,ans%=MOD;
	if(N==3LL)return ans;
	for(LL n=4LL,v=(same+diff)*2LL%MOD;n<=N;n++)
	{
		ans*=2LL,ans%=MOD;
		ans+=v*(n-3LL)%MOD*(n-3LL)%MOD;
		ans%=MOD;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	//0...1
	//0...11...0
	//0...11...01...00...1
	scanf("%d",&T);
	while(T--)
	{
		static char tmp[1000001];
		scanf("%s%lld%lld",tmp,&N,&MOD);
		L=-1;while(tmp[++L]);
		for(int i=0;i<L;i++)A[i]=tmp[i]-'0',A[L+i]=A[i]^1;
		printf("%lld\n",Solve());
	}
	return 0;
}
