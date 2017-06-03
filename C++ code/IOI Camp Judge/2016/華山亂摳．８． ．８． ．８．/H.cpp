#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
LL Gcd(const LL a,const LL b){return b==0?a:Gcd(b,a%b);}
vector<LL>P;
int N;
LL Solve()
{
	switch(N)
	{
		case 1:return 1;
		case 2:return 2;
		case 3:return 6;
		case 4:return 12;
		default:break;
	}
	if(N&1)return (LL)N*(N-1LL)*(N-2LL);
	if(N%3==0)return max((N-1LL)*(N-2LL)*(N-3LL),N*(N-1LL)*(N-5LL));
	return (LL)N*(N-1LL)*(N-3LL);
	int idx=upper_bound(P.begin(),P.end(),N)-P.begin();
	idx--;
	assert(idx>=2&&P[idx+1]>N);
	assert(Gcd(P[idx],P[idx-1])==1&&Gcd(P[idx],P[idx-2])==1&&Gcd(P[idx-1],P[idx-2])==1);
	return P[idx]*P[idx-1]*P[idx-2];
}
int main()
{
	if(true)
	{
		bool *isp=new bool[2000001];
		for(int i=0;i<=2000000;i++)isp[i]=true;
		for(int i=2;i<=2000000;i++)if(isp[i])
		{
			P.push_back(i);
			for(int j=2;i*j<=2000000;j++)isp[i*j]=false;
		}
		delete[]isp;
		const int n=P.size();
		for(int i=0;i<n;i++)
		{
			LL a=P[i];
			while(a*P[i]<=2000000)P.push_back(a*=P[i]);
		}
		sort(P.begin(),P.end());
//		for(int i=0;i<100;i++)printf("%lld\n",P[i]);
	}
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		printf("%lld\n",Solve());
	}
	return 0;
}
