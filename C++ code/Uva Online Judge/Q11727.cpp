#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		int a[3];scanf("%d%d%d",a,a+1,a+2);
		sort(a,a+3);
		static int kase=1;
		printf("Case %d: %d\n",kase++,a[1]);
	}
	return 0;
}
