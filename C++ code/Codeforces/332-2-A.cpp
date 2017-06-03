#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	int a,b,c;
	while(scanf("%d%d%d",&a,&b,&c)==3)
	{
		int ans=min(min(a+b+c,a+a+b+b),min(a+a+c+c,b+b+c+c));
		printf("%d\n",ans);
	}
	return 0;
}
