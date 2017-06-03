#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL b){if(b<a)a=b;}
struct Matrix
{
	LL s[2][2];
};
LL Mul(const LL a,const LL b,const LL mod)
{
	if(b==0LL)return 0LL;
	const LL tmp=Mul(a,b>>1,mod);
	LL ans=(tmp+tmp)%mod;
	if(b&1LL)(ans+=a)%=mod;
	return ans;
}
Matrix Mul(const Matrix &a,const Matrix &b,const LL mod)
{
	Matrix ans;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)
	{
		LL &v=ans.s[i][j]=0;
		for(int k=0;k<2;k++)(v+=Mul(a.s[i][k],b.s[k][j],mod))%=mod;
	}
	return ans;
}
LL Get(LL p,const LL mod)
{
	Matrix a;
	a.s[0][0]=0LL;
	a.s[0][1]=a.s[1][1]=a.s[1][0]=1LL;
	Matrix ans;
	ans.s[0][0]=ans.s[1][1]=1LL;
	ans.s[1][0]=ans.s[0][1]=0LL;
	for(;p;p>>=1)
	{
		if(p&1LL)ans=Mul(ans,a,mod);
		a=Mul(a,a,mod);
	}
	return ans.s[1][0];
}
int GetDigit(LL v,const int p)
{
	for(int i=0;i<p;i++)v/=10LL;
	return v%10LL;
}
LL F;
LL Dfs(const int dep,const LL cycle,const LL id)
{
//	printf("(%d,%lld,%lld)\n",dep,cycle,id);
	LL mod=1LL;
	for(int i=0;i<=dep;i++)mod*=10LL;
	map<pair<LL,LL>,LL>vis;
	LL ans=INF;
	for(int i=0;;i++)
	{
		const pair<LL,LL>&p=make_pair(Get(cycle*i+id,mod),Get(cycle*i+id+1LL,mod));
		if(vis.find(p)!=vis.end())
		{
			const LL &nxtcyc=(i*cycle+id)-vis[p];
			for(const auto it:vis)
			{
				if(dep>0)assert(GetDigit(it.first.first,dep-1)==GetDigit(F,dep-1));
				if(GetDigit(it.first.first,dep)==GetDigit(F,dep))
				{
					if(dep==12)getmin(ans,it.second);
					else getmin(ans,Dfs(dep+1,nxtcyc,it.second));
				}
			}
			break;
		}
		else vis[p]=i*cycle+id;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;scanf("%lld",&F)==1;)
	{
		const LL ans=Dfs(0,1,0);
		printf("%lld\n",ans==INF?-1LL:ans);
	}
	return 0;
}
