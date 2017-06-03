#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int N;
LL ANS,X1,X2,Y1,Y2;
void Update(const LL &x1,const LL &x2,const LL &y1,const LL &y2)
{
	if(max(X1,x1)<=min(X2,x2)&&max(Y1,y1)<=min(Y2,y2))
	{
		X1=max(X1,x1),X2=min(X2,x2),Y1=max(Y1,y1),Y2=min(Y2,y2);
	}
	else
	{
		const LL dis=max(max(X1,x1)-min(X2,x2),max(Y1,y1)-min(Y2,y2));
		X1-=dis,X2+=dis,Y1-=dis,Y2+=dis;
		ANS+=dis;
		Update(x1,x2,y1,y2);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		ANS=0;
		X1=Y1=-INF,X2=Y2=INF;
		for(int i=0;i<N;i++)
		{
			static LL x,y,p;
			scanf("%lld%lld%lld",&x,&y,&p);
			Update(x-p,x+p,y-p,y+p);
		}
		printf("%lld\n",ANS);
	}
	return 0;
}
