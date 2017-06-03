#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
template<LL P,LL root,int MAXN>
struct NTT{
	void operator()(int n,LL a[],bool inv_ntt=false){
		//tran(n,a,inv_ntt);
		puts("not implemented");
	}
};
const LL P=2013265921,root=31;
const int MAXN=4194304;
NTT<P,root,MAXN>ntt;
void Sq(int n,LL s[])
{
	static LL a[200001];
	for(int i=0;i<n;i++)a[i]=0;
	for(int i=0;i<n;i++)if(s[i])for(int j=0;j<n;j++)if(s[j])a[i+j]+=s[i]*s[j];
	for(int i=0;i<n;i++)s[i]=a[i];
	return;
	ntt(n,s,false);
	for(int i=0;i<n;i++)s[i]*=s[i];
	ntt(n,s,true);
}
int N,S[100000];
LL *CNT=(new LL[100001])+50000;
int main()
{
	freopen("in.txt","r",stdin);
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=-50000;i<=50000;i++)CNT[i]=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&S[i]);
			++CNT[S[i]];
		}
		LL *s=new LL[200001];
		for(int i=0;i<=200000;i++)s[i]=0;
		for(int i=-50000;i<=50000;i++)s[i+50000]=CNT[i];
		Sq(200001,s);
		s+=100000;
		LL ans=0;
		for(int i=-50000;i<=50000;i++)ans+=s[i]*CNT[i];
//		printf("ans=%lld\n",ans);
//		for(int i=-50000;i<=50000;i++)if(i!=0)ans-=CNT[0]*CNT[i]*2;//+0+,0++
//		printf("ans=%lld\n",ans);
//		ans-=CNT[0];//000(aaa)
//		printf("ans=%lld\n",ans);
//		ans-=CNT[0]*(CNT[0]-1)/2*3;//000(aab)
//		printf("ans=%lld\n",ans);
		s-=100000;
		delete[]s;
		printf("%lld\n",ans);
	}
	return 0;
}
