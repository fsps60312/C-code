#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int W,H,N;
LL X[100000],Y[100000];
struct House
{
	LL x,y;
}HOUSE[100000];
LL Get(const LL &x,const LL &y)
{
	LL mx=0LL,ans=0LL;
	for(int i=0;i<N;i++)
	{
		ans+=abs(x-X[i]),ans+=abs(y-Y[i]);
		mx=max(mx,abs(x-HOUSE[i].x)+abs(y-HOUSE[i].y));
	}
	return ans*2LL-mx;
}
int main()
{
	scanf("%d%d%d",&W,&H,&N);
	for(int i=0;i<N;i++)
	{
		LL &x=X[i],&y=Y[i];
		scanf("%lld%lld",&x,&y);
		HOUSE[i].x=x,HOUSE[i].y=y;
	}
	sort(X,X+N),sort(Y,Y+N);
	LL xans=-1LL,yans=-1LL;
	LL ans=INF;
	const int l=max(0,(N-1)/2-1),r=min(N-1,N/2+1);
	for(int i=l;i<=r;i++)
	{
		for(int j=l;j<=r;j++)
		{
			LL ta=Get(X[i],Y[j]);
			if(ta<ans)ans=ta,xans=X[i],yans=Y[j];
		}
	}
	printf("%lld\n%lld %lld\n",ans,xans,yans);
	return 0;
}
