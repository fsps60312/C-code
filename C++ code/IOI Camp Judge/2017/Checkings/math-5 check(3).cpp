#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
void Exgcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0){assert(a==1),x=1,y=0;}
	else
	{
		Exgcd(b,a%b,y,x);//by+(a-a/b*b)x=1,ax+b(y-a/b*x)=1
		(y-=a/b*x)%=MOD;
	}
}
LL Inv(const LL a)
{
	LL x,y;
	Exgcd(a,MOD,x,y);
	return x>=0?x:x+MOD;
}
int F[1000001],P_COUNT[1000001];
LL LEVEL[100001],RELEV[100001];
void Initialize()
{
	for(int i=2;i<=1000000;i++)F[i]=0;
	{
		vector<int>p;
		for(int i=2;i<=1000000;i++)
		{
			if(F[i]==0)F[i]=i,p.push_back(i);
			for(int j=0;p[j]*i<=1000000;j++)
			{
				F[p[j]*i]=p[j];
				if(i%p[j]==0)break;
			}
		}
//		for(int i=2;i<=100;i++)printf("F[%d]=%d\n",i,F[i]);
	}
//	puts("hi");
	for(int i=1;i<=1000000;i++)
	{
		int &ans=P_COUNT[i]=0;
		for(int v=i,pre=0;v>1;v/=F[v])
		{
			if(F[v]!=pre)pre=F[v],++ans;
		}
	}
//	for(int i=2;i<=100;i++)printf("P_COUNT[%d]=%d\n",i,P_COUNT[i]);
	LEVEL[0]=1;
	for(int i=1;i<=100000;i++)LEVEL[i]=LEVEL[i-1]*i%MOD;
	for(int i=0;i<=100000;i++)RELEV[i]=Inv(LEVEL[i]);
}
LL C(const int a,const int b)
{
	if(b>a)return 0;
	return LEVEL[a]*RELEV[b]%MOD*RELEV[a-b]%MOD;
}
vector<int>F_DP0[1000001],F_DP1[1000001];
vector<int>GetFactors(int n,bool power1)
{
	vector<int>&f=(power1?F_DP1[n]:F_DP0[n]);
	if(!f.empty())return f;
	f.push_back(1);
	int v=n;
	if(v>1)for(int pre=F[v],cnt=0;;v/=F[v])
	{
		if(v>1&&F[v]==pre)
		{
			++cnt;
		}
		else
		{
			vector<int>nxt_f;
			for(int i=0,now=1;i<=(power1?1:cnt);i++,now*=pre)
			{
				for(const int f0:f)nxt_f.push_back(f0*now);
			}
			f.swap(nxt_f);
			if(v==1)break;
			pre=F[v],cnt=1;
		}
	}
	assert(v==1);
//	printf("n=%d,f=",n);
//	for(const int v:f)printf(" %d",v);puts("");
	return f;
}
vector<int>CastToFactors(const vector<int>&s,vector<int>*ans)
{
	static vector<bool>vis(1000001,false);
	vector<int>id;
	for(int v:s)
	{
		for(const int f:GetFactors(v,false))
		{
			if(!vis[f])vis[f]=true,id.push_back(f);
//			printf("f=%d\n",f);
//			puts("d");
//			printf("%d\n",(int)ans[f].size());
//			ans[f].push_back(0);
//			printf("%d\n",(int)ans[f].size());
//			ans[f].pop_back();
//			printf("%d\n",(int)ans[f].size());
			ans[f].push_back(v);
//			puts("e");
		}
	}
	for(const int i:id)vis[i]=false;
//	for(int i=0;i<=1000000;i++)assert(!vis[i]);
	return id;
}
vector<int>CastToFactors(const vector<int>&s,vector<int>&ans)
{
	static vector<bool>vis(1000001,false);
	vector<int>id;
	for(int v:s)
	{
		for(const int f:GetFactors(v,true))
		{
			if(!vis[f])vis[f]=true,id.push_back(f);
			++ans[f];
		}
	}
	for(const int i:id)vis[i]=false;
//	for(int i=0;i<=1000000;i++)assert(!vis[i]);
	return id;
}
int N,K;
LL CountCoprimes(const vector<int>&s)
{
	static vector<int>f(1000001,0);
	const auto &id=CastToFactors(s,f);
	LL ans=0;
	for(const int i:id)
	{
		const LL cnt=C(f[i],K);
//		printf("%d: C(%d,%d)\n",p.first,(int)p.second.size(),K);
		(P_COUNT[i]&1?(ans-=cnt):(ans+=cnt))%=MOD;
	}
	for(const int i:id)f[i]=0;
//	for(int i=0;i<=1000000;i++)
//	{
//		if(!f[i].empty())
//		{
//			printf("i=%d\n",i);
//			for(const int v:f[i])printf("%d ",v);puts("");
//		}
//		assert(f[i].empty()&&"hi");
//	}
//	printf("s =");
//	for(const int v:s)printf(" %d",v);printf(", ans=%lld\n",ans);
	return ans>=0?ans:ans+MOD;
}
vector<int>S;
int main()
{
	freopen("data.txt","r",stdin);
	Initialize();
//	int mmxx=0;
//	for(int i=1;i<=1000000;i++)
//	{
//		int a=(int)GetFactors(i).size();
//		if(a>mmxx)mmxx=a;
//	}
//	printf("mx=%d\n",mmxx);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		S.resize(N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		static vector<int>f[1000001];
		const auto &id=CastToFactors(S,f);
		LL ans=0;
		for(const int i:id)
		{
//			printf("f = %d, s =",i);
//			for(const int v:f[i])printf(" %d",v);puts("");
			vector<int>s;
			for(const int v:f[i])s.push_back(v/i);
			(ans+=i*CountCoprimes(s))%=MOD;
		}
		for(const int i:id)f[i].clear();
//		for(int i=0;i<=1000000;i++)assert(f[i].empty());
		printf("%lld\n",ans);
	}
	return 0;
}
