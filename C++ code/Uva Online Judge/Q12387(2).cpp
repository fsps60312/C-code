#include<cstdio>
#include<vector>
#include<bitset>
using namespace std;
typedef long long LL;
const LL ROUNDANGLE=360000LL,MOD=100000007LL,HASHBASE=8284649LL,HASHMOD=2147483647LL;
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
struct Hash
{
	LL v;
	Hash inv()
	{
		LL x,y,g;
		exgcd(v,HASHMOD,g,x,y);
		return Hash((x%HASHMOD+HASHMOD)%HASHMOD);
	}
	Hash(){}
	Hash(const LL v){this->v=(v%HASHMOD+HASHMOD)%HASHMOD;}
	Hash operator+(Hash &h)const{return Hash(v+h.v);}
	Hash operator-(Hash &h)const{return Hash(v-h.v);}
	void operator+=(Hash &h){(*this)=(*this)+h;}
	Hash operator*(Hash &h)const{return Hash(v*h.v);}
	void operator*=(Hash &h){(*this)=(*this)*h;}
	void operator*=(const LL &h){(*this)=Hash(h)*(*this);}
	Hash operator/(Hash &h){return h.inv()*(*this);}
	bool operator!=(Hash &h){return v!=h.v;}
}HASH[ROUNDANGLE],POW[ROUNDANGLE];
LL S,P,EQUAL[ROUNDANGLE+1LL];
bitset<ROUNDANGLE> VIS;
vector<LL> A;
LL inv(LL a)
{
	LL x,y,g;
	exgcd(a,MOD,g,x,y);
	return (x%MOD+MOD)%MOD;
}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
Hash GetHash(LL l,LL r)
{
	Hash hl=l?HASH[l-1]:Hash(0LL);
	Hash hr=HASH[r];
	return (hr-hl)/POW[l];
}
LL GetEqual(LL a)
{
	LL g=gcd(a,ROUNDANGLE);
	LL &e=EQUAL[a];
	if(e!=-1LL)return e;
	LL n=ROUNDANGLE/g;
	Hash cmp=GetHash(0LL,g-1LL);
	for(int i=1;i<n;i++)if(GetHash(i*g,(i+1)*g-1LL)!=cmp)return e=0LL;
	e=1LL;
	for(LL i=0;i<g;i++)
	{
		if(!VIS[i])continue;
		e*=S;
		e%=MOD;
	}
	return e;
}
int main()
{
//	int ans=0;
////	for(int i=1;i<=360000;i++)if(360000%i==0)ans+=360000/i;//1289431
//	for(int i=1;i<=360000;i++)if(360000%i==0)ans+=360000;//1289431
//	printf("%d\n",ans);
//	freopen("in.txt","r",stdin);
	POW[0]=1LL;
	for(int i=1;i<ROUNDANGLE;i++)POW[i]=Hash(HASHBASE)*POW[i-1];
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
		Hash now=0LL;
		for(LL i=0LL;i<ROUNDANGLE;i++)
		{
			if(VIS[i])now+=POW[i];
			HASH[i]=now;
			EQUAL[i+1LL]=-1LL;
		}
		LL sum=0LL,cnt=0LL;
		for(LL i=1LL,v;i<=ROUNDANGLE;i++)
		{
			v=GetEqual(i);
			if(!v)continue;
//			printf("angle=%lld,v=%lld\n",i,v);
			sum+=v,sum%=MOD,cnt++;
		}
		printf("%lld\n",sum*inv(cnt)%MOD);
	}
	return 0;
}
