#include<cstdio>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
int T,N;
LL MOD,SZ[500000];
vector<int>CH[500000];
vector<LL>P;
LL BuildSZ(const int u)
{
	LL &ans=SZ[u]=1LL;
	for(int i=0;i<CH[u].size();i++)ans+=BuildSZ(CH[u][i]);
	return ans;
}
void Mul(map<LL,int>&s,LL n,const int sign)
{
	for(int i=0;P[i]*P[i]<=n;i++)
	{
		int cnt=0;
		while(n%P[i]==0LL)n/=P[i],cnt++;
		if(cnt>0)s[P[i]]+=cnt*sign;
	}
	if(n>1LL)s[n]+=sign;
}
LL Pow(LL a,int b)
{
	LL ans=1LL;
	while(b)
	{
		if(b&1)(ans*=a)%=MOD;
		(a*=a)%=MOD;
		b>>=1;
	}
	return ans;
}
LL Dfs(const int u)
{
	LL ans=1LL;
	for(int i=0;i<CH[u].size();i++)(ans*=Dfs(CH[u][i]))%=MOD;
	map<LL,int>s;
	for(LL i=1LL;i<SZ[u];i++)Mul(s,i,1);
	for(int i=0;i<CH[u].size();i++)for(LL j=1LL;j<=SZ[CH[u][i]];j++)Mul(s,j,-1);
	for(const auto &it:s)(ans*=Pow(it.first,it.second))%=MOD;
	return ans;
}
int main()
{
	P.push_back(2LL),P.push_back(3LL);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2LL;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j]!=0LL;j++);
		}while(P[i]%P[j]==0LL);
		if(P[i]*P[i]>500000LL)break;
	}
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%lld",&N,&MOD);
		for(int i=0;i<N;i++)CH[i].clear();
		for(int i=1,p;i<N;i++)scanf("%d",&p),CH[--p].push_back(i);
		BuildSZ(0);
		LL ans=Dfs(0);
		printf("%lld\n",ans);
	}
	return 0;
}
