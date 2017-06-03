#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Point
{
	LL X,Y;
	int ID;
};
bool operator<(const Point &a,const Point &b){return a.X!=b.X?a.X<b.X:a.Y<b.Y;}
int N;
Point P[200000];
LL Cross(const LL x1,const LL y1,const LL x2,const LL y2){return x1*y2-x2*y1;}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%lld%lld",&P[i].X,&P[i].Y);
			P[i].ID=i+1;
		}
		sort(P,P+N);
		for(int i=2;;i++)if(Cross(P[1].X-P[0].X,P[1].Y-P[0].Y,P[i].X-P[0].X,P[i].Y-P[0].Y)!=0)
		{
			printf("%d %d %d\n",P[0].ID,P[1].ID,P[i].ID);
			break;
		}
	}
	return 0;
}
