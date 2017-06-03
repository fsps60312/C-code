#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
unsigned int Rand()
{
	static unsigned int seed=rand();
	seed=seed*0xdefaced+185849;
	return seed+=seed>>20;
}
int Rand(int a,int b)
{
	return a+(int)(Rand()%(b-a+1));
}
const int N = 514;
const int M = 1000;
const int MOD = 1e9 + 7;
int t, n, m, a[N], dp[M + 1];
int main() {
	srand(time(NULL));
	freopen("in.txt","w",stdout);
	int cnt=0;
	puts("100000");
	for(LL i=pow(9223372036854775807LL,1.0/3.0)+1LL;cnt<100000;i+=Rand(1,10000))//000000LL)
	{
//		printf("%lld %lld\n",i,i*i*i);
		if(i*i*i>1000000000000000000LL)
		{
			printf("%lld %lld\n",i,1000000000000000000LL);
			cnt++;
		}
	}
    return 0;
}
