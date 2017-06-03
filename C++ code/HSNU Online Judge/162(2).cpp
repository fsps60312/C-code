#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<cmath>
using namespace std;
#define int long long
typedef long long LL;
void Add(map<LL,int>&s,const LL v,const int cnt)
{
	auto it=s.find(v);
	if(it==s.end())s[v]=cnt;
	else if(!(it->second+=cnt))s.erase(it);
}
LL Gcd(const LL a,const LL b){return b==0LL?a:Gcd(b,a%b);}
int N;
map<LL,int>S;
void Initialize()
{
	map<LL,int>tmp;
	for(int i=0;i<N;i++)
	{
		static LL v;
		scanf("%lld",&v);
		Add(tmp,v,1);
	}
	S.clear();
	while(!tmp.empty())
	{
		auto it=tmp.begin();
		const auto begin=it++;
		for(;;it++)
		{
			if(it==tmp.end())
			{
				Add(S,begin->first,begin->second);
				tmp.erase(begin);
				break;
			}
			const LL g=Gcd(begin->first,it->first);
			if(g!=1LL)
			{
				const int cnt1=begin->second,cnt2=it->second;
				const LL v1=begin->first,v2=it->first;
				Add(tmp,v1/g,cnt1),Add(tmp,v2/g,cnt2),Add(tmp,g,cnt1+cnt2);
				Add(tmp,v1,-cnt1),Add(tmp,v2,-cnt2);
				break;
			}
		}
	}
	map<LL,int>().swap(tmp);
}
vector<LL>P;
void Factorize(LL n,map<LL,int>&f)
{
	f.clear();
	for(int i=0;i<(int)P.size()&&P[i]*P[i]<=n;i++)
	{
		int cnt=0;
		while(n%P[i]==0LL)n/=P[i],cnt++;
		if(cnt)Add(f,P[i],cnt);
	}
	if(n==1LL)return;
	LL v=sqrt(n);
	assert(v*v<=n&&(v+1LL)*(v+1LL)>n);
	if(v*v==n)Add(f,v,2);
	else Add(f,n,1);
}
map<LL,int>F;
void Solve()
{
	F.clear();
	for(const auto it:S)
	{
		static map<LL,int>tmp;tmp.clear();
		Factorize(it.first,tmp);
		for(const auto elem:tmp)
		{
			assert(F.find(elem.first)==F.end());
			F[elem.first]=it.second*elem.second;
		}
	}
}
main()
{
//	freopen("in.txt","r",stdin);
	if(true)
	{
		bool *notp=new bool[1000001];
		for(int i=0;i<=1000000;i++)notp[i]=false;
		P.clear();
		for(int i=2;i<=1000000;i++)if(!notp[i])
		{
			P.push_back(i);
			for(int j=2;i*j<=1000000;j++)notp[i*j]=true;
		}
		delete[]notp;
	}
//	for(int i=0;i<100;i++)printf("%lld\n",P[i]);
	while(scanf("%lld",&N)==1)
	{
		Initialize();
		Solve();
		map<int,vector<LL> >ans;
		for(const auto it:F)ans[it.second].push_back(it.first);
		auto it=ans.end();it--;
		printf("%lld\n",it->first);
		vector<int>big;big.push_back(1);
		for(int cnt=(it->second).size();cnt--;)
		{
			for(int &v:big)v*=2;
			for(int i=0;i<(int)big.size();i++)if(big[i]>=10)
			{
				if(i+1==(int)big.size())big.push_back(0);
				big[i+1]+=big[i]/10;
				big[i]%=10;
			}
		}
		assert(big[0]>1&&big[0]<10),big[0]--;
		for(int i=(int)big.size()-1;i>=0;i--)assert(big[i]>=0&&big[i]<10),putchar('0'+big[i]);puts("");
		break;
	}
	return 0;
}
