#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const double EPS=1e-7;
double LEVEL[10000001];
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	LEVEL[0]=log(1.0);
	for(int i=1;i<=10000000;i++)LEVEL[i]=LEVEL[i-1]+log(i);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		int t1=0,t2=0;
		for(int i=0,a,b,c,d;i<N;i++)
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			const double v1=LEVEL[a]-LEVEL[b]-LEVEL[a-b],v2=LEVEL[c]-LEVEL[d]-LEVEL[c-d];
//			if(!(a==c&&(b==d||b+d==a)))
//			printf("%.15f %.15f\n",v1,v2);
			if(abs(v1-v2)>EPS)++(v1<v2?t1:t2);
		}
		printf("%d %d\n",t1,t2);
	}
	return 0;
}
