#include<cstdio>
#include<cassert>
using namespace std;
unsigned long long N,D[64];
int main()
{
	D[0]=1LLU;
	for(int i=1;i<=63;i++)D[i]=D[i-1]*2LLU;
//	for(int i=0;i<64;i++)printf("%llu\n",D[i]);
	long long tmp;
	while(scanf("%lld",&tmp)==1)
	{
		bool sign=(tmp<0LL),print1=false;
		N=(sign?-tmp:tmp);
		for(int i=63;i>=0;i--)
		{
			bool tsign=(i&1);
			if(sign!=tsign){if(print1)printf("0");}
			else
			{
				if((D[i]+1LLU)/2>N){if(print1)printf("0");}
				else
				{
					printf("1");
					print1=true;
					if(D[i]<=N)N-=D[i];
					else N=D[i]-N,sign^=true;
				}
			}
//			printf("\nsign=%d,N=%llu\n",sign,N);
		}
		assert(N==0LL);
		puts("");
	}
	return 0;
}
