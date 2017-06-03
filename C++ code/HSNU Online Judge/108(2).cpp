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
//		printf("now=%d\n",now);
		auto it=s.find(now);
		if(it!=s.end())ans+=it->second++,ans%=MOD;
		else s[now]=1LL;
	}
	printf("ans[2]=%lld\n",ans);
	if(N==2LL)return ans;
	if(s[0]==1)s.erase(0);
	else s[0]--;
	LL same=0LL,diff=0LL;
	for(int i=2*L-1,now=0;i>=0;i--)
	{
		if(A[i]==1)now++;
		else now--;
		auto it=s.find(-now);
		if(it!=s.end())same+=it->second;
		it=s.find(now);
		if(it!=s.end())diff+=it->second;
//		printf("now=%d,same=%lld,diff=%lld\n",now,same,diff);
	}
	printf("same=%lld,diff=%lld\n",same,diff);
	//n=2:(1,0)
	//n=3:(1,0)(0,1)
	//n=4:(1,1)(1,1)
	//n=5:(2,2)(2,2)
	//n=6:(4,4)(4,4)
	//n=7:(8,8)(8,8)
	ans*=2LL,ans%=MOD;
	ans+=diff,ans%=MOD;
	printf("ans[3]=%lld\n",ans);
	if(N==3LL)return ans;
	for(LL n=4LL,v=(same+diff)*2LL%MOD;n<=N;n++)
	{
		ans*=2LL,ans%=MOD;
		ans+=v*(n-3LL)%MOD*(n-3LL)%MOD;
		ans%=MOD;
		printf("ans[%lld]=%lld\n",n,ans);
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
//		MOD=2147483647;
		L=-1;while(tmp[++L]);
		for(int i=0;i<L;i++)A[i]=tmp[i]-'0',A[L+i]=A[i]^1;
		printf("%lld\n",Solve());
	}
	return 0;
}
