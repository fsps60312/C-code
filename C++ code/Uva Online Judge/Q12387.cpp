#include<cstdio>
#include<vector>
#include<bitset>
using namespace std;
typedef long long LL;
const LL ROUNDANGLE=360000LL,MOD=100000007LL;
LL S,P;
bitset<ROUNDANGLE> VIS;
vector<LL> A;
void exgcd(LL a,LL b,LL &g,LL &x,LL &y)
{
	if(b)
	{
		exgcd(b,a%b,g,y,x);
		//(a-a/b*b)x+by==g
		//ax+b(y-a/b*x)==g
		y-=a/b*x;
	}
	else
	{
		g=a;
		x=1LL,y=0LL;
	}
}
LL inv(LL a)
{
	LL x,y,g;
	exgcd(a,MOD,g,x,y);
	return (x%MOD+MOD)%MOD;
}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
LL GetEqual(LL a)
{
	if(gcd(ROUNDANGLE,a)==1LL)return 0LL;
	bitset<ROUNDANGLE> rot;
	rot=VIS>>a;
	if((VIS&rot)!=rot)return 0LL;
	rot=VIS<<(P-a);
	if((VIS&rot)!=rot)return 0LL;
	LL ans=1LL;
	for(LL i=0;i<a;i++)
	{
		if(!VIS[i])continue;
		ans*=S;
		ans%=MOD;
	}
	return ans;
}
int main()
{
//	int ans=0;
////	for(int i=1;i<=360000;i++)if(360000%i==0)ans+=360000/i;//1289431
//	for(int i=1;i<=360000;i++)if(360000%i==0)ans+=360000;//1289431
//	printf("%d\n",ans);
	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld",&S,&P)==2&&!(S==-1LL&&P==-1LL))
	{
		VIS.reset();
		A.clear();
		for(LL i=0LL,v;i<P;i++)
		{
			scanf("%lld",&v);
			A.push_back(v);
			VIS[v]=1;
		}
		LL sum=0LL,cnt=0LL;
		for(LL i=1LL,v;i<=ROUNDANGLE;i++)
		{
			v=GetEqual(i);
			if(!v)continue;
			printf("v=%lld\n",v);
			sum+=v,sum%=MOD,cnt++;
		}
		printf("%lld %lld\n",sum,cnt);
		printf("%lld\n",sum*inv(cnt)%MOD);
	}
	return 0;
}
