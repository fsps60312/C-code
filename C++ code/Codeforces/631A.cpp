#include<cstdio>
#include<cassert>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		int a=0,b=0;
		for(int i=0,v;i<N;i++)scanf("%d",&v),a|=v;
		for(int i=0,v;i<N;i++)scanf("%d",&v),b|=v;
		printf("%lld\n",(long long)a+b);
	}
	return 0;
}
