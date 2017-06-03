#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
LL N,D,E;
vector<LL>P;
bool IsPrime(const LL &a)
{
	int l=0,r=P.size()-1;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(P[mid]<a)l=mid+1;
		else r=mid;
	}
	return P[l]==a;
}
LL Gcd(const LL &a,const LL &b){return b==0LL?a:Gcd(b,a%b);}
int main()
{
	P.push_back(2LL),P.push_back(3LL);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2LL;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0LL);
		if(P[i]>=1000000LL)break;
	}
	while(scanf("%lld%lld%lld",&N,&D,&E)==3&&!(N==0LL&&D==0LL&&E==0LL))
	{
		LL v=D*E-1LL;
		LL p,q;
		for(int i=0;;i++)if(v%(P[i]-1LL)==0LL)
		{
			p=P[i];
			if(N%p!=0LL)continue;
			q=N/p;
//			printf("(%lld,%lld)\n",p,q);
			if(IsPrime(q)&&Gcd(E,(p-1LL)*(q-1LL))==1LL)break;
		}
		static int kase=1;
		printf("Case #%d: %lld %lld\n",kase++,p,q);
	}
	return 0;
}
