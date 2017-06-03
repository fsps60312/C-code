#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
struct QueryType
{
	int L,R;
	LL *ANS;
	QueryType(){}
	QueryType(const int _L,const int _R,LL *_ANS):L(_L),R(_R),ANS(_ANS){}
};
bool operator<(const QueryType &a,const QueryType &b){return a.R<b.R;}
struct Bit
{
	int N;
	LL S[200000*8];
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=1;}
	void Mul(int i,const LL v){for(++i;i<=N;i+=i&(-i))(S[i]*=v)%=MOD;}
	LL Query(int i){LL ans=1;for(++i;i;i-=i&(-i))(ans*=S[i])%=MOD;return ans;}
}BIT;
void Exgcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0){assert(a==1);x=1,y=0;}
	else
	{
		Exgcd(b,a%b,y,x);
		(y-=a/b*x)%=MOD;
	}
}
LL Inv(const LL v)
{
	assert(0<v&&v<MOD);
	LL x,y;
	Exgcd(v,MOD,x,y);
	return x>=0?x:x+MOD;
}
LL /*INV[1000001],*/FACTOR[1000001];
void BuildFactors()
{
	vector<int>p;
	for(int i=2;i<=1000000;i++)FACTOR[i]=i;
	for(int i=2;i<=1000000;i++)
	{
		if(FACTOR[i]==i)p.push_back(i);
		for(int j=0;p[j]*i<=1000000;j++)
		{
			FACTOR[p[j]*i]=p[j];
			if(i%p[j]==0)break;
		}
	}
}
int N,LOC[200001];
LL PI[200001];
vector<LL>S;
vector<int>PRE;
LL ANS[600000];
int main()
{
//	freopen("in.txt","r",stdin);
//	for(int i=1;i<=1000000;i++)INV[i]=Inv(i);
	BuildFactors();
	while(scanf("%d",&N)==1)
	{
//		puts("a");
		S.resize(1);
		LOC[0]=0;
		PI[0]=1;
		for(int i=1;i<=N;i++)
		{
			LL v;
			scanf("%lld",&v);
			PI[i]=PI[i-1]*v%MOD;
			while(v>1)
			{
				const LL f=FACTOR[v];
				S.push_back(f*Inv(f-1)%MOD);
				while(v%f==0)v/=f;
			}
			LOC[i]=(int)S.size()-1;
		}
		N=(int)S.size();
		PRE.resize(N);
		{
			map<LL,int>pre;
			for(int i=1;i<N;i++)PRE[i]=pre[S[i]],pre[S[i]]=i;
		}
		int querycount;scanf("%d",&querycount);
		vector<QueryType>queries;
		for(int i=0;i<querycount*3;i++)ANS[i]=-1;
		for(int i=0,l,r;i<querycount;i++)
		{
			scanf("%d%d",&l,&r);
			ANS[i*3]=PI[r]*Inv(PI[l-1])%MOD;
			queries.push_back(QueryType(LOC[l-1],LOC[r],&ANS[i*3+1]));
			queries.push_back(QueryType(LOC[l-1],LOC[l-1],&ANS[i*3+2]));
		}
		sort(queries.begin(),queries.end());
		BIT.Clear(N);
		{
			int cur=0;
			for(QueryType q:queries)
			{
				while(cur<q.R)
				{
					++cur;
					BIT.Mul(PRE[cur],S[cur]);
				}
				*q.ANS=BIT.Query(q.L);
			}
		}
		for(int i=0;i<querycount;i++)printf("%lld\n",ANS[i*3]*Inv(ANS[i*3+1]*Inv(ANS[i*3+2])%MOD)%MOD);
		for(int i=0;i<querycount*3;i++)assert(ANS[i]!=-1);
	}
	return 0;
}
