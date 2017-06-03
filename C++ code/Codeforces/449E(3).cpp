#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int PHI[1000001];
void BuildPHI()
{
	for(int i=1;i<=1000000;i++)PHI[i]=i;
	for(int i=2;i<=1000000;i++)if(PHI[i]==i)
	{
		for(int j=1;i*j<=1000000;j++)(PHI[i*j]/=i)*=i-1;
	}
}
vector<int>P;
void BuildP()
{
	bool *isp=new bool[1101];
	for(int i=2;i<=1100;i++)isp[i]=true;
	for(int i=2;i<=1100;i++)if(isp[i])
	{
		P.push_back(i);
		for(int j=2;i*j<=1100;j++)isp[i*j]=false;
	}
}
void Dfs(const int now,const int dep,const vector<pair<int,int> >&f,vector<int>&ans)
{
	if(dep==-1){ans.push_back(now);return;}
	for(int i=0,m=1;i<=f[dep].second;i++,m*=f[dep].first)Dfs(now*m,dep-1,f,ans); 
}
void BuildF(int n,vector<int>&ans)
{
	vector<pair<int,int> >f;
	for(int i=0;P[i]*P[i]<=n;i++)
	{
		int cnt=0;
		while(n%P[i]==0)n/=P[i],cnt++;
		f.push_back(make_pair(P[i],cnt));
	}
	if(n>1)f.push_back(make_pair(n,1));
	Dfs(1,(int)f.size()-1,f,ans);
}
LL GcdSum(const LL &n)
{
	vector<int>f;
	BuildF((int)n,f);
//	printf("%lld:",n);
//	for(const int v:f)printf(" %d",v);//puts("");
	LL ans=0LL;
	for(const int v:f)(ans+=(LL)v*PHI[n/v])%=MOD;//,printf(" %d*%d",v,PHI[n/v]);puts("");
	//printf("ans=%lld\n",ans+n);
	return ans;
}
LL Solve(const LL &len)
{
	LL ans=(len-1LL)*len;
	if(ans%3LL==0LL)ans=ans/3LL%MOD*(2LL*len-1LL)%MOD;
	else ans=ans%MOD*((2LL*len-1LL)/3LL)%MOD;
	(ans-=len*len)%=MOD;
	(ans+=2LL*GcdSum(len))%=MOD;
	return (ans%MOD+MOD)%MOD;
	return ((len-1LL)*len*(2LL*len-1LL)/3LL-len*len+2LL*GcdSum(len))%MOD;
}
LL N,M;
LL SUM[3][1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	BuildPHI();
	BuildP();
	for(int i=0;i<3;i++)SUM[i][0]=0LL;
	for(LL i=1LL;i<=1000000LL;i++)
	{
//		if(i%10000LL==0LL)printf("i=%lld\n",i);
		SUM[0][i]=(SUM[0][i-1]+Solve(i))%MOD;
		SUM[1][i]=(SUM[1][i-1]+i*Solve(i))%MOD;
		SUM[2][i]=(SUM[2][i-1]+i*i%MOD*Solve(i))%MOD;
	}
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%I64d%I64d",&N,&M);
//		for(LL l=1LL;l<=min(N,M);l++)
//		{
//			int ta=(l-1)*l*(2*l-1)/3-l*l+2LL*GcdSum(l);
//			ans+=ta*(N-l+1)*(M-l+1);
//			N*M-N*l+N-M*l+l*l-l+M-l+1
//			N*M+N+M+1-N*l-M*l-l-l+l*l
//		}
		const LL n=min(N,M);
		printf("%I64d\n",(N*M%MOD+N+M+1LL)*SUM[0][n]-(N+M+2LL)*SUM[1][n]+SUM[2][n]);
	}
	return 0;
}
