#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int Gcd(const int a,const int b){return b==0?a:Gcd(b,a%b);}
int GcdSum(const int l)
{
	int ans=0;
	for(int i=0;i<l;i++)ans+=Gcd(i,l);
	return ans;
}
int N,M;
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		int ans=0;
		for(int l=1;l<=min(N,M);l++)
		{
//			int ta=l*l*l-(l-1)*l*l+(l-1)*l*(2*l-1)/3-2*l*l+2*GcdSum(l);
			int ta=(l-1)*l*(2*l-1)/3-l*l+2*GcdSum(l);
			ans+=ta*(N-l+1)*(M-l+1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
