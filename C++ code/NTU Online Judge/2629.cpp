#include<cstdio>
#include<cassert>
using namespace std;
int N;
int Get(const int v)
{
	return (new int[10]{6,2,5,5,4,5,6,3,7,6})[v];
}
int main()
{
	//freopen("alarm.in","r",stdin);
	//freopen("alarm.out","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int h=0;h<24;h++)for(int m=0;m<60;m++)if(Get(h/10)+Get(h%10)+Get(m/10)+Get(m%10)==N)
		{
			printf("%02d:%02d\n",h,m);
			goto index;
		}
		puts("Impossible");
		index:;
	}
	return 0;
}
