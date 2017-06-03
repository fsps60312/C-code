#include<cstdio>
#include<algorithm>
using namespace std;
int W,H,N,X[100000],Y[100000];
int main()
{
	scanf("%d%d%d",&W,&H,&N);
	for(int i=0;i<N;i++)scanf("%d%d",&X[i],&Y[i]);
	sort(X,X+N),sort(Y,Y+N);
	int xans=X[(N-1)>>1],yans=Y[(N-1)>>1];
	long long ans=0LL;
	for(int i=0;i<N;i++)ans+=abs(xans-X[i]),ans+=abs(yans-Y[i]);
	printf("%lld\n%d %d\n",ans,xans,yans);
	return 0;
}
