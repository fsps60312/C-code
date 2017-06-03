#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M;
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		int a=N*2,b=M*3;
		for(int i=0;i<min(a,b)/6;i++)
		{
			if(a+2<b+3)a+=2;
			else b+=3;
		}
		printf("%d\n",max(a,b));
	}
	return 0;
}
