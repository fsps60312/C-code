#include <bits/stdc++.h>
using namespace std;
#define int long long
int isPrime[1000001];
int PHI[1000001];
void get_prime () {
	for (int x=0;1000001>x;x++) PHI[x]=x;
	isPrime[0]=isPrime[1]=1;
	isPrime[2]=0;
	for (int x=2;1000001>=x;x++) {
		if (isPrime[x]==0) {
			PHI[x]/=x;
			PHI[x]*=(x-1);

			for (int j=2*x;1000001>j;j+=x) {
				isPrime[j]=1;
				PHI[j]/=x;
				PHI[j]*=(x-1);
			}
		}
	}
}
int A[4];
vector<int>S[4];
int Mul(const int a,const int b,const int mod)
{
	int ans=a*b;
	return ans-(ans-1000000)/mod*mod;
}
int Pow(int a,int p,const int mod)
{
	int ans=1;
	while(p)
	{
		if(p&1)ans=Mul(ans,a,mod);
		a=Mul(a,a,mod);
		p>>=1;
	}
	return ans;
}
int Solve(const int dep,const int mod)
{
	if(mod==1)return 0;
	assert(mod>1);
	if(A[dep]==1)return 1;
	if(dep==3)return A[dep];
	return Pow(A[dep],Solve(dep+1,PHI[mod]),mod);
}
main()
{
//	freopen("in.txt","r",stdin);
	get_prime();
//	for(int i=1;i<=100;i++)printf("%lld ",PHI[i]);puts("");
	int testcount;scanf("%lld",&testcount);
	while(testcount--)
	{
		for(int i=0;i<4;i++)scanf("%lld",&A[i]);
		int m;scanf("%lld",&m);
		printf("%lld\n",Solve(0,m)%m);
	}
	return 0;
}
