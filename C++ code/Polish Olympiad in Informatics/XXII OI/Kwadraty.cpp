#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
int main()
{
	for(LL n=1;;n++)
	{
		if(n*(n+1)*(2*n+1)/6>(n+1)*(n+1)){printf("n=%lld\n",n);break;}
	}
	return 0;
}
