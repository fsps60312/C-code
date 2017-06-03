#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
int IsValid(const int *s,const int n)
{
	int dis=n;
	map<int,int>cnt;
	for(int i=0;i<n;i++)
	{
		if(s[i]<=n)
		{
			const int td=(s[i]-i+n)%n;
			if(dis==n)dis=td;
			else if(dis!=td)return -1;
		}
		else if(++cnt[s[i]]>1)return -1;
	}
	return dis;
}
int N,S[100000];
#include<utility>
#include<algorithm>
vector<int>Solve1()
{
	const int dis=IsValid(S,N)%N;
	assert(0<=dis&&dis<N);
	vector<pair<int,int> >tmp;
	for(int i=0;i<N;i++)if(S[i]>N)tmp.push_back(make_pair(S[i],i)),S[i]=(i+dis+N-1)%N+1;
	sort(tmp.begin(),tmp.end());
	int cur=N+1;
	vector<int>ans;
	for(const auto &p:tmp)
	{
		for(;cur<=p.first;cur++)
		{
			ans.push_back(S[p.second]);
			S[p.second]=cur;
		}
	}
	return ans;
}
typedef long long LL;
const LL MOD=1e9+9;
LL Pow(LL a,LL p)
{
	LL ans=1LL;
	for(;p;p>>=1)
	{
		if(p&1LL)(ans*=a)%=MOD;
		(a*=a)%=MOD;
	}
	return ans;
}
LL Solve2()
{
	const int dis=IsValid(S,N);
	if(dis==-1)return 0LL;
	LL ans=(dis==N?N:1LL);
	vector<int>tmp;
	for(int i=0;i<N;i++)if(S[i]>N)tmp.push_back(S[i]);
	sort(tmp.begin(),tmp.end());
	int cur=N+1;
	for(int i=0;i<(int)tmp.size();i++)
	{
		(ans*=Pow((int)tmp.size()-i,(tmp[i]-cur+1)-1))%=MOD;
		cur=tmp[i]+1;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int type;scanf("%d",&type)==1;)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		if(1<=type&&type<=3)printf("%d\n",IsValid(S,N)!=-1?1:0);
		else if(4<=type&&type<=6)
		{
			const vector<int>&ans=Solve1();
			printf("%d",(int)ans.size());
			for(const int v:ans)printf(" %d",v);
			puts("");
		}
		else if(7<=type&&type<=10)printf("%lld\n",Solve2());
		else assert(0);
	}
	return 0;
}
