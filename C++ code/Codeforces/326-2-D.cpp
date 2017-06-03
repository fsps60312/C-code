#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
LL N,L,K,A[1000000];
LL DP[1000000];
map<LL,LL>CNT,IDX;
vector<LL>V;
struct Node
{
	LL v,idx;
	Node(){}
	Node(LL v,LL idx):v(v),idx(idx){}
	bool operator<(Node n)const{return v<n.v;}
}NODE[1000000];
void Add(LL &a,const LL &b){a%=MOD;a+=b%MOD;a%=MOD;}
void Mul(LL &a,const LL &b){a%=MOD;a*=b%MOD;a%=MOD;}
LL Mulv(const LL &a,const LL &b){LL ans=a%MOD;ans*=b%MOD;return ans%MOD;}
LL Exgcd(const LL &a,const LL &b,LL &x,LL &y)
{
	if(b==0LL){x=1LL,y=0LL;return;}
	Exgcd(b,a%b,y,x);
	//(a-a/b*b)x+by=g
	//ax+b(y-a/b*x)=g
	y-=a/b*x;
}
LL C(const LL &a,const LL &b)
{
	if(b>a)return 0LL;
	if(a==b)return 1LL;
	if(b<(a+1LL)/2LL)return C(a,a-b);
	LL ans=1LL;
	for(LL i=b+1;i<=a;i++)
	{
		ans*=i;
		ans/=i-b;
	}
	return ans;
}
int main()
{
	scanf("%I64d%I64d%I64d",&N,&L,&K);
	for(int i=0;i<N;i++)scanf("%I64d",&A[i]);
	for(int i=0;i<N;i++)NODE[i]=Node(A[i],i);
	sort(NODE,NODE+N);
	for(int i=0;i<N;i++)
	{
		if(CNT.find(A[i])==CNT.end())CNT[A[i]]=1LL;
		else CNT[A[i]]++;
	}
	for(int i=0;i<N;i++)V.push_back(A[i]);
	sort(V.begin(),V.end());
	V.resize(unique(V.begin(),V.end())-V.begin());
	for(int i=0;i<V.size();i++)
	{
		IDX[V[i]]=i;
		DP[i]=CNT[V[i]];
	}
	LL ans=0LL;
	Add(ans,L);
	for(int k=2;k<=K&&k<=(L+N-1LL)/N;k++)
	{
		vector<LL>vec;
		for(int i=0;i<L%N;i++)vec.push_back(A[i]);
		sort(vec.begin(),vec.end());
		LL sum=0LL;
		for(int i=0,j=0;i<V.size();i++)
		{
			Add(sum,DP[i]);
			for(;j<vec.size()&&vec[j]==V[i];j++)Add(ans,Mulv(sum,C(L/N,k-1)));
			DP[i]=Mulv(sum,CNT[V[i]]);
			Add(ans,Mulv(DP[i],C(L/N,k)));
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
