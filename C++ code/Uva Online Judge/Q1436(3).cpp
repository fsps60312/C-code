#include<cstdio>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
int T,N;
LL MOD;
int SZ[500000];
vector<int>CH[500000];
vector<int>P;
vector<int>FV[500000];
vector<int>FC[500000];
int BuildSZ(const int u)
{
	int &ans=SZ[u]=1;
	for(int i=0;i<CH[u].size();i++)ans+=BuildSZ(CH[u][i]);
	return ans;
}
void GetF(int n)
{
	vector<int>&fv=FV[n],&fc=FC[n];
	for(int i=0;P[i]*P[i]<=n;i++)
	{
		int cnt=0;
		while(n%P[i]==0LL)n/=P[i],cnt++;
		if(cnt>0)fv.push_back(P[i]),fc.push_back(cnt);
	}
	if(n>1LL)fv.push_back(n),fc.push_back(1);
}
void Mul(map<int,int>&s,const int n,const int sign)
{
	vector<int>&fv=FV[n],&fc=FC[n];
	for(int i=0;i<fv.size();i++)s[fv[i]]+=fc[i]*sign;
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
	map<int,int>s;
	for(int i=2;i<SZ[u];i++)Mul(s,i,1);
	for(int i=0;i<CH[u].size();i++)for(int j=2;j<=SZ[CH[u][i]];j++)Mul(s,j,-1);
	for(const auto &it:s)(ans*=Pow(it.first,it.second))%=MOD;
	return ans;
}
int main()
{
	P.push_back(2),P.push_back(3);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0);
		if(P[i]*P[i]>500000)break;
	}
	for(int i=2;i<500000;i++)GetF(i);
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
