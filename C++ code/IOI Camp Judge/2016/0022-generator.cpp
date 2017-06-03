#include <cstdio>
#include<ctime>
#include<cstdlib>
#include<algorithm>
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
//	freopen("in.txt","w",stdout);
	for(t=0;;t++)
	{
		if(t%1000==0)printf("t=%d\n",t);
		int n=Rand(1,514),m=Rand(1,1000);
        for (int i = 0; i < n; i++) a[i]=Rand(1,max(1,m/3));
        for (int i = 0; i <= m; i++) dp[i] = 0;
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= a[i]; j--) {
                dp[j] += dp[j - a[i]];
                if (dp[j] > MOD) dp[j] -= MOD;
            }
        }
        if(dp[m]==MOD)
        {
        	printf("n=%d,m=%d\n",n,m);
        	for(int i=0;i<n;i++)printf("%d ",a[i]);puts("");
        	return 0;
		}
	}
    return 0;
}
