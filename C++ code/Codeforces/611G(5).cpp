#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
LL Pow(LL a,LL p)
{
	LL ans=1;
	for(;p;p>>=1,(a*=a)%=MOD)if(p&1)(ans*=a)%=MOD;
	return ans;
}
LL ASUM[1000000],BSUM[1000000],X[1000000],Y[1000000],XSUM[1000000],YSUM[1000000];
LL AreaSum(const int l1,const int l2,const int r)
{
//	for(int i=l1;i<=l2;i++)(ans+=(ASUM[r]-ASUM[i])+(X[r]*Y[i]-X[i]*Y[r]))%=MOD;
	assert(l1>=1);
	return ((l2-l1+1)*(ASUM[r]%MOD)%MOD-(BSUM[l2]-BSUM[l1-1]))+(X[r]*(YSUM[l2]-YSUM[l1-1])%MOD-(XSUM[l2]-XSUM[l1-1])*Y[r]%MOD);
}
unsigned long long _ASUM[1000000],_X[1000000],_Y[1000000];
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,x,y;i<N;i++)scanf("%d%d",&x,&y),X[i]=x,Y[i]=y,_X[i]=x,_Y[i]=y;
		for(int i=0;i<N;i++)X[i+N]=X[i],Y[i+N]=Y[i],_X[i+N]=_X[i],_Y[i+N]=_Y[i];
		reverse(X,X+N*2),reverse(Y,Y+N*2),reverse(_X,_X+N*2),reverse(_Y,_Y+N*2);
		ASUM[0]=0,_ASUM[0]=0;
		for(int i=1;i<N*2;i++)ASUM[i]=(X[i-1]*Y[i]-X[i]*Y[i-1])%MOD,_ASUM[i]=_X[i-1]*_Y[i]-_X[i]*_Y[i-1];
		for(int i=1;i<N*2;i++)(ASUM[i]+=ASUM[i-1])%=MOD,_ASUM[i]+=_ASUM[i-1];
		BSUM[0]=XSUM[0]=YSUM[0]=0;
		for(int i=1;i<N*2;i++)BSUM[i]=(BSUM[i-1]+ASUM[i])%MOD,XSUM[i]=(XSUM[i-1]+X[i])%MOD,YSUM[i]=(YSUM[i-1]+Y[i])%MOD;
		const unsigned long long total_area=_ASUM[N];
		LL ans=0;
		for(int i=N,j=2;i<N*2;i++)
		{
			while(((_ASUM[i]-_ASUM[j])+(_X[i]*_Y[j]-_X[j]*_Y[i]))*2>total_area)++j;
			const int small=(((_ASUM[i]-_ASUM[j])+(_X[i]*_Y[j]-_X[j]*_Y[i]))*2==total_area?j+1:j);
			const int large=j-1;
			(ans+=AreaSum(i-N+2,large,i))%=MOD;
			(ans-=AreaSum(small,i-2,i))%=MOD;
		}
		printf("%d\n",(int)((ans+MOD)%MOD));
	}
	return 0;
}
