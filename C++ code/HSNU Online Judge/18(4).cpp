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
LL HEIGHT[200000],WIDTH[200000];
LL SUMR[200000],HR[200000],SUMP[200001],HP[200001],WP[200001];
bool Solve()
{
	for(int i=0,j=-1;i<RN;i++)
	{
		while(HP[j+1]<HR[i])j++;
//		if(j+1>=CN)for(;;);
		LL h=HR[i]-(j>=0?HP[j]:0L);
		LL w=WP[j+1];
		if((j>=0?SUMP[j]:0L)+w*h<SUMR[i])return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&RN)==1)
	{
		for(int i=0;i<RN;i++)scanf("%lld%lld",&R[i].guard,&R[i].cnt);
		sort(R,R+RN);
		scanf("%d",&CN);
		for(int i=0;i<CN;i++)scanf("%lld%lld",&C[i].guard,&C[i].cnt);
		sort(C,C+CN);
		LL height=0L,sum=0L;
		for(int i=0;i<RN;i++)
		{
			LL &w=R[RN-1-i].guard,&h=R[RN-1-i].cnt;
			HR[i]=(height+=h);
			SUMR[i]=(sum+=w*h);
		}
		LL width=0L;
		sum=0L;
		for(int i=0;i<CN;i++)width+=C[i].cnt;
		for(int i=0;i<CN;i++)
		{
			HP[i]=C[i].guard;
			LL h=C[i].guard-(i-1>=0?C[i-1].guard:0L);
			LL w=WP[i]=width;width-=C[i].cnt;
			SUMP[i]=(sum+=w*h);
		}
		if(HP[CN-1]<HR[RN-1])HP[CN]=HR[RN-1],WP[CN]=0L,SUMP[CN]=SUMP[CN-1],CN++;
		printf("%d\n",Solve());
	}
	return 0;
}
