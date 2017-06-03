#include <cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
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
	puts("1000");
	for(int t=1;t<=1000;t++)
	{
		int N=Rand(500,500),M=Rand(250,250);
		printf("%d %d\n",N,M);
		for(int i=0;i<N;i++)printf(" %d",Rand(1,1));puts("");
	}
    return 0;
}
