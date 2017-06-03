#include<cstdio>
#include<map>
using namespace std;
typedef long long LL;
int T,L;
int A[2000001];
LL N,MOD;
LL Mod(const LL v){return (v%MOD+MOD)%MOD;}
LL Pow(LL a,LL b)
{
	LL ans=1LL;
	while(b!=0LL)
	{
		if((b&1LL)==1LL)ans*=a,ans%=MOD;
		a*=a,a%=MOD;
		b>>=1;
	}
	return ans;
}
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
		if(it!=s.end())ans+=it->second++,ans%=MOD;
		else s[now]=1LL;
	}
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
	}
	ans*=2LL,ans%=MOD;
	ans+=diff,ans%=MOD;
	if(N==3LL)return ans;
	//a[0]=ans
	//a[n]=a[n-1]*2+v*2^(2n-2)=2(a[n-1]+v*2^(2n-3))
	//a[n]-v*2^(2n-1)=2(a[n-1]-v*2^(2n-3))
	//b[n]=a[n]-v*2^(2n-1)
	//b[n]=2*b[n-1]=b[1]*2^(n-1)
	//
	LL v=(same+diff)*2LL%MOD;
	ans*=2LL,ans%=MOD;
	ans+=v,ans%=MOD;
	if(N==4LL)return ans;
	LL b1=Mod(ans-v*2LL);
	b1*=Pow(2LL,N-4LL),b1%=MOD;
	return Mod(b1+v*Pow(2,2*(N-3LL)-1)%MOD);
}
int main()
{
//	freopen("in.txt","r",stdin);
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
