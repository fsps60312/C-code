#include<cstdio>
#include<cassert>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
	freopen("progress_pie.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int p,x,y;scanf("%d%d%d",&p,&x,&y);
		swap(x,y);
		x-=50,y-=50;
		static int kase=0;
		printf("Case #%d: %s\n",++kase,atan2(y,x)<p/100.0*2.0*acos(-1.0)&&sqrt(x*x+y*y)<50.0?"black":"white");
	}
	return 0;
}
