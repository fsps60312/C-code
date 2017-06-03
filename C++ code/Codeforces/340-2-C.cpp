#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
LL Sq(const LL &v){return v*v;}
int N;
LL X1,Y1,X2,Y2;
LL X[2000],Y[2000];
LL Dist(const LL &x1,const LL &y1,const LL &x2,const LL &y2){return Sq(x1-x2)+Sq(y1-y2);}
LL Solve(const int flower)
{
	const LL r1=Dist(X1,Y1,X[flower],Y[flower]),r2=Dist(X2,Y2,X[flower],Y[flower]);
	for(int i=0;i<N;i++)if(Dist(X1,Y1,X[i],Y[i])>r1&&Dist(X2,Y2,X[i],Y[i])>r2)return INF;
//	printf("flower=%d\n",flower);
	return r1+r2;
}
int main()
{
	while(scanf("%d%lld%lld%lld%lld",&N,&X1,&Y1,&X2,&Y2)==5)
	{
		for(int i=0;i<N;i++)scanf("%lld%lld",&X[i],&Y[i]);
		LL ans=INF;
		for(int i=0;i<N;i++)getmin(ans,Solve(i));
		assert(ans!=INF);
		printf("%lld\n",ans);
	}
	return 0;
}
