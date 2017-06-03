#include<cstdio>
#include<cassert>
using namespace std;
int N,S[1000000];
int BasicSks(const int n)
{
	int l,r;
	for(l=0;!(n&(1<<l));l++);
	for(r=30;!(n&(1<<r));r--);
	if(l==r)return 1;
	int ans=0;
	if(!(n&(1<<(l+1))))++ans;
	if(!(n&(1<<(r-1))))++ans;
	return ans;
}
int Sks(const int n)
{
	int ans=0;
	int d=0;
	while((1<<(d+1))<=n)d++;
	if(d==0)return 1;
	ans+=(1<<d)-(d-1);
	if(n&(1<<(d-1)))ans+=(1<<(d-1))-1;
	else ans+=n&((1<<(d-1))-1);
//	printf("ans=%d\n",ans);
	for(int i=d-2,v=0;i>=0;i--)
	{
		if((n&((1<<(i+2))-1))>=(1<<i))ans+=v+1;
		else ans+=v;
		v=(v<<1)+((n>>(i+1))&1);
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int n=1,ans=0;n<=10000000;n++)
	{
		ans+=BasicSks(n);
//		printf("n=%d,ans=%d\n",n,ans);
//		printf("%d\t%d\t%d\n",n,ans,Sks(n));
		assert(ans==Sks(n));
	}
	printf("pass");
	return 0;
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		int n=0;
		for(int i=0;i<N;i++)for(int j=0;j<S[i];j++)n=(n<<1)+((i&1)^1);
		printf("n=%d\n",n);
	}
	return 0;
}
