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
LL HEIGHT[200000],WIDTH[200000],USED[200000];
#include<stack>
bool Solve()
{
	LL l=0L,r=0L;
	LL &mxw=WIDTH[CN-1];
	for(int i=RN-1,j=CN-1;i>=0;i--)
	{
		int &w=R[i].guard,&cnt=R[i].cnt;
		for(;j>=0&&WIDTH[j]>=w;j--)
		{
			l+=(WIDTH[j]-w)*HEIGHT[j];
			r+=HEIGHT[j];
		}
		if(r<cnt)l-=w*(cnt-r),r=cnt;
		if(l<0L)return false;
		r-=cnt;
		if(i)l+=(w-R[i-1].guard)*r;
	}
	return true;
}
int main()
{
	while(scanf("%d",&RN)==1)
	{
		for(int i=0;i<RN;i++)scanf("%lld%lld",&R[i].guard,&R[i].cnt);
		sort(R,R+RN);
		scanf("%d",&CN);
		for(int i=0;i<CN;i++)scanf("%lld%lld",&C[i].guard,&C[i].cnt);
		sort(C,C+CN);
		LL width=0L;
		for(int i=0;i<CN;i++)
		{
			WIDTH[i]=(width+=C[CN-i].cnt);
			HEIGHT[i]=C[CN-i].guard-(CN-i-1>=0?C[CN-i-1].guard:0L);
			USED[i]=0L;
		}
		printf("%d\n",Solve());
	}
	return 0;
}
