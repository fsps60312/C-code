#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
typedef long long LL;
bool TooLarge(const LL n,const int road,const int bound)
{
//	printf("(n=%lld,road=%d,bound=%d)\n",n,road,bound);
	if(n-1LL>road)return true;
	LL r=road-(n-1LL);
	int now=n-1;
//	if(now<=bound)return false;
	for(LL i=1LL;r>0LL;i++)
	{
		r-=i;
		if(i==1LL)now-=2;
		else --now;
		if(now<=bound)return false;
	}
	return now>bound;
}
int K,N,R,S[100001];
LL SUM[100001];
int Solve(const int critical)
{
	int ans=0;
//	printf("critical=%d\n",critical);
	for(int i=0;i<N;)
	{
		int l=i+1,r=N;
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(TooLarge(SUM[mid]-SUM[i],R,critical))r=mid-1;
			else l=mid;
		}
		if(TooLarge(SUM[r]-SUM[i],R,critical))return INF;
//		printf("(%d,%d)\n",i,r);
		i=r,++ans;
	}
	return ans;
}
LL GetMN()
{
	LL l=2LL,r=1e5;
	while(l<r)
	{
		const LL mid=(l+r)/2;
		if(mid*(mid-1LL)/2>=R)r=mid;
		else l=mid+1LL;
	}
	return r;
}
LL MN;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&K,&N,&R)==3)
	{
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),SUM[i]=SUM[i-1]+S[i];
		int l=0,r=R+1;
		//(MN)*(MN-1)/2>=R
		MN=GetMN();
//		printf("MN=%lld\n",MN);
		int cnt=0;
		for(int i=0;;)
		{
			int r=i+1;
			while(r<=N&&SUM[r]-SUM[i]<MN)++r;
			if(r>N)break;
			i=r;
			++cnt;
		}
//		printf("cnt=%d\n",cnt);
		if(cnt>=K)
		{
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(Solve(mid)<=K)r=mid;
				else l=mid+1;
			}
		}
		else l=r=R+1;
		if(r==R+1)puts("No Solution");
		else printf("%d\n",r);
	}
	return 0;
}
