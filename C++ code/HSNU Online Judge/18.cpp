#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
int RN,CN;
struct Pair
{
	LL guard,cnt;
	bool operator<(const Pair &p)const{return guard<p.guard;}
}R[200000],C[200000];
LL SUM[200000],MXC[200000];
int Solve()
{
	LL sum=0L;
	for(int i=0;i<CN;i++)
	{
		int l=0,r=RN-1,mid;
		while(l<r)
		{
			mid=(l+r)/2;
			if(SUM[mid]>=sum)r=mid;
			else l=mid+1;
		}
		if(SUM[mid]<sum)return 0;
		if(C[i].guard>MXC[l])return 0;
		sum+=C[i].guard*C[i].cnt;
	}
	return 1;
}
int main()
{
	while(scanf("%d",&RN)==1)
	{
		for(int i=0;i<RN;i++)scanf("%lld%lld",&R[i].guard,&R[i].cnt);
		sort(R,R+RN);
		LL mxc=0L;
		for(int i=RN-1,r=0;r<RN;r++,i--)
		{
			LL up=R[i].guard,down=i?R[i-1].guard:0L;
			printf("R(guard=%lld,cnt=%lld)\n",R[i].guard,R[i].cnt);
			SUM[r]=(r?SUM[r-1]:0L)+(mxc+=R[i].cnt)*(up-down);
			MXC[r]=mxc;
			printf("(max=%lld,sum=%lld)\n",MXC[r],SUM[r]);
		}
		scanf("%d",&CN);
		for(int i=0;i<CN;i++)scanf("%lld%lld",&C[i].guard,&C[i].cnt);
		sort(C,C+CN);
		printf("%d\n",Solve());
	}
	return 0;
}
