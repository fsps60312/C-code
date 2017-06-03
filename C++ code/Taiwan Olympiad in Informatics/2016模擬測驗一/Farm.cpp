#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Farm
{
	int x1,y1,x2,y2;
}F[100000];
int W,H,N;
LL ANS;
int main()
{
//	freopen("inB.txt","r",stdin);
	while(scanf("%d%d",&W,&H)==2)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%d%d%d%d",&F[i].x1,&F[i].y1,&F[i].x2,&F[i].y2);
			F[i].x1++,F[i].y1++;
		}
		ANS=0;
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)
		{
			if(F[i].x2>=F[j].x1&&F[i].x1<=F[j].x2&&F[i].y2>=F[j].y1&&F[i].y1<=F[j].y2)ANS++;
		}
		printf("%lld\n",ANS);
	}
	return 0;
}
