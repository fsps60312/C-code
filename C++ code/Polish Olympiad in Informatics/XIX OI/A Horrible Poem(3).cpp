#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
int FP[500001];
vector<int>P;
void BuildPrime()
{
	bool *isp=new bool[500001];
	for(int i=2;i<=500000;i++)isp[i]=true;
	for(int i=2;i<=500000;i++)
	{
		if(isp[i])P.push_back(i),FP[i]=i;
		for(int j=0;P[j]*i<=500000;j++)
		{
			isp[P[j]*i]=false;
			FP[P[j]*i]=P[j];
			if(i%P[j]==0)break;
		}
	}
	delete[]isp;
//	for(int i=0;i<100;i++)printf("P[%d]=%d\n",i,P[i]);
}
void Dfs(const vector<pair<int,int> >&fs,const int dep,const int now,vector<int>&ans)
{
	if(dep==-1){ans.push_back(now);return;}
	for(int i=0,f=1;i<=fs[dep].second;i++,f*=fs[dep].first)Dfs(fs,dep-1,now*f,ans);
}
vector<int>GetFactors(int n)
{
	vector<pair<int,int> >fs;
	for(;n>1;n/=FP[n])
	{
		if(fs.empty()||fs.back().first!=FP[n])fs.push_back(make_pair(FP[n],1));
		else fs.back().second++;
	}
	vector<int>ans;
	Dfs(fs,(int)fs.size()-1,1,ans);
	sort(ans.begin(),ans.end());
	return ans;
}
typedef long long LL;
const LL BASE=97,MOD=2147483647;
LL HASH[500001],POW[500001];
bool IsSame(const int a,const int b,const int len)
{
	assert(a<b);
	return ((HASH[a+len]-HASH[a]*POW[len])%MOD+MOD)%MOD==((HASH[b+len]-HASH[b]*POW[len])%MOD+MOD)%MOD;
}
int N;
char S[500001];
int main()
{
//	freopen("in.txt","r",stdin);
	BuildPrime();
	scanf("%d%s",&N,S);
	POW[0]=1LL;
	HASH[0]=0LL;
	for(int i=1;i<=N;i++)POW[i]=(POW[i-1]*BASE)%MOD,HASH[i]=(HASH[i-1]*BASE+(S[i-1]-'a'))%MOD;
	int querycount;scanf("%d",&querycount);
	for(int a,b;querycount--;)
	{
		scanf("%d%d",&a,&b),a--,b--;
		const int len=b-a+1;
		const vector<int>&fs=GetFactors(len);
		int ans=len;
		for(int i=0;i+1<(int)fs.size();i++)if(IsSame(a,a+fs[i],len-fs[i]))
		{
			ans=fs[i];break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
